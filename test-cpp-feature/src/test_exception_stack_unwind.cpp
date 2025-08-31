#include <iostream>

class TestObject {
    int x;
public:
	TestObject(int i):x(i) { std::cout << "TestObject():Acquire resources -> " << x << std::endl; }
	~TestObject() { std::cout << "~TestObject():Release resources -> " << x << std::endl; }
};

int test_exception_stack_unwind_main() {
    std::cout << "=== Test Exception Handling ===" << std::endl;
    
    TestObject t1{1}; // RAII: Resource Acquisition Is Initialization
    
    try {
        TestObject t2{2}; // RAII: Resource Acquisition Is Initialization
        std::cout << "Processing with TestObject" << std::endl;
        // Simulate some processing that might throw an exception
        throw std::runtime_error("An error occurred during processing");
        TestObject t3{3}; // RAII: Resource Acquisition Is Initialization -> no constructor & destructor calls if exception thrown
    }
    catch (const std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
        TestObject t4{4}; // RAII: Resource Acquisition Is Initialization
    }

    return 0;
}