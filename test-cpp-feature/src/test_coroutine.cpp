#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>

struct Awaitable {
    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<> waiting_coroutine) {
        std::cout << "Called awaitable suspend\n";
        // Schedule the coroutine to be resumed later
        std::thread([waiting_coroutine]() {
            std::cout << "Simulating suspend in awaitable\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Awaitable suspend done and coroutine to resume\n";
            waiting_coroutine.resume();
        }).detach();
    }
    void await_resume() {
        std::cout << "Resumed after waiting\n";
    }
};

struct Coroutine {
    struct promise_type {
        Coroutine get_return_object() {
            return Coroutine{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle;
    Coroutine(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Coroutine() { handle.destroy(); }

    void resume() { 
        if (handle) handle.resume(); 
    }
};

Coroutine exampleCoroutine() {
    std::cout << "Start coroutine\n";
    co_await Awaitable();
    std::cout << "End coroutine\n";
}

int test_coroutine_main() {
    std::cout << "Before exampleCoroutine()\n";
    auto coro = exampleCoroutine();
    std::cout << "After exampleCoroutine()\n";

    std::cout << "Before Coroutine resume()\n";
    coro.resume();
    std::cout << "After Coroutine resume()\n";
    
    std::cout << "Before main thread sleep\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Afetr main thread sleep\n";

    return 0;
}