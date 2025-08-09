#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

// A fixed-size thread-safe queue implementation
template <typename T>
class BoundedQueue {
public:
    explicit BoundedQueue(size_t capacity) : capacity_(capacity) {}

    bool push(const T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        // Wait until queue has space or we're shutting down
        not_full_.wait(lock, [this] { return queue_.size() < capacity_ || shutdown_; });
        
        if (shutdown_) {
            return false;
        }
        
        queue_.push(item);
        not_empty_.notify_one();
        return true;
    }

    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        // Wait until queue has items or we're shutting down
        not_empty_.wait(lock, [this] { return !queue_.empty() || shutdown_; });
        
        if (queue_.empty() && shutdown_) {
            return false;
        }
        
        item = queue_.front();
        queue_.pop();
        not_full_.notify_one();
        return true;
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    void shutdown() {
        std::lock_guard<std::mutex> lock(mutex_);
        shutdown_ = true;
        not_empty_.notify_all();
        not_full_.notify_all();
    }

private:
    std::queue<T> queue_;
    const size_t capacity_;
    mutable std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    bool shutdown_ = false;
};

// Base thread class with rate limiting
class RateControlledThread {
public:
    RateControlledThread(double rate_per_second) : 
        rate_per_second_(rate_per_second),
        running_(false) {
        if (rate_per_second_ > 0) {
            interval_ns_ = static_cast<int64_t>(1000000000.0 / rate_per_second_);
        }
    }

    virtual ~RateControlledThread() {
        stop();
    }

    void start() {
        running_ = true;
        thread_ = std::thread(&RateControlledThread::run, this);
    }

    void stop() {
        running_ = false;
        if (thread_.joinable()) {
            thread_.join();
        }
    }

    bool isRunning() const {
        return running_;
    }

protected:
    virtual void process() = 0;

    void sleep_for_rate_control() {
        if (rate_per_second_ <= 0) {
            return; // No rate limiting
        }

        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(
            now - last_execution_).count();
        
        if (elapsed < interval_ns_) {
            auto sleep_time = std::chrono::nanoseconds(interval_ns_ - elapsed);
            std::this_thread::sleep_for(sleep_time);
        }
        
        last_execution_ = std::chrono::high_resolution_clock::now();
    }

private:
    void run() {
        last_execution_ = std::chrono::high_resolution_clock::now();
        
        while (running_) {
            process();
            sleep_for_rate_control();
        }
    }

    double rate_per_second_;
    int64_t interval_ns_ = 0;
    std::atomic<bool> running_;
    std::thread thread_;
    std::chrono::high_resolution_clock::time_point last_execution_;
};

// Producer class
template <typename T>
class Producer : public RateControlledThread {
public:
    Producer(BoundedQueue<T>& queue, double rate_per_second) :
        RateControlledThread(rate_per_second),
        queue_(queue),
        items_produced_(0) {}

    size_t getItemsProduced() const {
        return items_produced_;
    }

    // Override to customize what gets produced
    virtual T produceItem() {
        return static_cast<T>(items_produced_);
    }

protected:
    void process() override {
        T item = produceItem();
        if (queue_.push(item)) {
            items_produced_++;
            std::cout << "Produced: " << item << " (Total: " << items_produced_ << ")" << std::endl;
        }
    }

private:
    BoundedQueue<T>& queue_;
    std::atomic<size_t> items_produced_;
};

// Consumer class
template <typename T>
class Consumer : public RateControlledThread {
public:
    Consumer(BoundedQueue<T>& queue, double rate_per_second) :
        RateControlledThread(rate_per_second),
        queue_(queue),
        items_consumed_(0) {}

    size_t getItemsConsumed() const {
        return items_consumed_;
    }

    // Override to customize how items are processed
    virtual void consumeItem(const T& item) {
        std::cout << "Consumed: " << item << " (Total: " << items_consumed_ << ")" << std::endl;
    }

protected:
    void process() override {
        T item;
        if (queue_.pop(item)) {
            consumeItem(item);
            items_consumed_++;
        }
    }

private:
    BoundedQueue<T>& queue_;
    std::atomic<size_t> items_consumed_;
};

// Example usage
int main() {
    // Create a bounded queue with capacity of 10 items
    BoundedQueue<int> queue(30);
    
    // Create a producer that generates 5 items per second
    Producer<int> producer(queue, 5.0);
    
    // Create a consumer that processes 2 items per second
    Consumer<int> consumer(queue, 2.0);
    
    // Start the threads
    producer.start();
    consumer.start();
    
    // Run for 10 seconds
    std::this_thread::sleep_for(std::chrono::seconds(20));
    
    // Stop the threads
    producer.stop();
    queue.shutdown();
    consumer.stop();
    
    // Print statistics
    std::cout << "Total items produced: " << producer.getItemsProduced() << std::endl;
    std::cout << "Total items consumed: " << consumer.getItemsConsumed() << std::endl;
    std::cout << "Items left in queue: " << queue.size() << std::endl;
    
    return 0;
}