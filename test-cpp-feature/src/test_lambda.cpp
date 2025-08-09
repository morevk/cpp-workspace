#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class LambdaCaptureDemo {
private:
    int multiplier_ = 2;
    
public:
    void demonstrateCaptures() {
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        int threshold = 3;
        
        std::cout << "=== Capture by Value [=] ===" << std::endl;
        std::for_each(numbers.begin(), numbers.end(), [=](int n) {
            if (n > threshold) {
                std::cout << n << " * " << multiplier_ << " = " << (n * multiplier_) << std::endl;
            }
        });
        
        std::cout << "\n=== Capture by Reference [&] ===" << std::endl;
        int sum = 0;
        std::for_each(numbers.begin(), numbers.end(), [&](int n) {
            sum += n; // Modifying external variable
        });
        std::cout << "Sum: " << sum << std::endl;
        
        std::cout << "\n=== Mixed Capture [=, &sum] ===" << std::endl;
        sum = 0; // Reset
        std::for_each(numbers.begin(), numbers.end(), [=, &sum](int n) {
            if (n > threshold) {
                sum += (n * multiplier_); // sum by reference, others by value
            }
        });
        std::cout << "Filtered sum: " << sum << std::endl;
        
        std::cout << "\n=== This Capture [this] ===" << std::endl;
        auto processor = [this](int n) -> int {
            return n * multiplier_; // Access member variable
        };
        
        std::transform(numbers.begin(), numbers.end(), numbers.begin(), processor);
        std::cout << "Transformed numbers: ";
        for (int n : numbers) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }

    auto test_lambda_by_return_with_capture_value() {
        int number = 42;
        
        // Lambda function that returns a value
        std::function<int()> lambda = [=]() -> int {
            return number; // Access local variable
        };

        return lambda;
    }

    auto test_lambda_by_return_with_capture_ref() {
        int number = 42;
        
        // Lambda function that returns a value
        std::function<int()> lambda = [&]() -> int {
            return number; // Access local variable
        };

        return lambda;
    }
};

int test_lambda_main() {
    LambdaCaptureDemo demo;
    demo.demonstrateCaptures();

    try {
        std::cout << "\n=== Lambda(capture value) by return ===" << std::endl;
        auto lambda = demo.test_lambda_by_return_with_capture_value();
        std::cout << "returned value : " << lambda() << std::endl;

        std::cout << "\n=== Lambda(capture ref) by return ===" << std::endl;
        lambda = demo.test_lambda_by_return_with_capture_ref();
        std::cout << "returned value : " << lambda() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}