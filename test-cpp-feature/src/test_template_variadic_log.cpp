#include <iostream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <source_location> // The header for std::source_location
#include <cstdio> // For printf

// The core logging function now takes a std::source_location object
template<typename... Args>
void log_with_location(
                       const std::source_location location,
                       const char* format,
                       Args &&... args
                    ) {
    // Print source location information
    std::cout << "[" << location.file_name() << ":" << location.line()
              << " in " << location.function_name() << "] ";

    // Use printf for formatting
    std::printf(format, std::forward<Args>(args)...);
    std::printf("\n");
}


// A macro to simplify usage and leverage the default argument
#define log(format, ...) log_with_location(std::source_location::current(), format, ##__VA_ARGS__)

// Optional: You can provide a wrapper function to make it even cleaner but problem is source location
// is not pointing to where log(..) is called and always line 35
//template<typename... Args>
//void log(const char* format, Args&&... args) {
//    log_with_location(std::source_location::current(), format, std::forward<Args>(args)...);
//}

void some_function(int value) {
    log("The value is: %d", value);
}

int test_template_variadic_log_main() {
    std::string name = "C++20";
    log("Hello, %s!", name.c_str());
    some_function(42);
    return 0;
}
