#include <iostream>
#include <string>

struct Employee {
    int id;
    std::string name;
};

template <typename T, typename... Args>
T createObject(Args&&... args) {
    return T(std::forward<Args>(args)...);
}
int test_template_factory_method_main() {
    // Example usage of the createObject function
    // Create an integer object with the value 5
    // Create a string object with the value "vishal"
    int p = createObject<int>(5);
    std::string s = createObject<std::string>("vishal");

    std::cout << "Int: " << p << ", String: " << s << std::endl;

    // Create Employee objects using the factory method
    // Note: The Employee constructor should match the arguments provided
    // Here we assume Employee has a constructor that takes an int and a string
    // If Employee has a different constructor, adjust the arguments accordingly
    // Example Employee constructor: Employee(int id, const std::string& name)
    Employee emp1{1, "Alice"};
    Employee emp2 = createObject<Employee>(2, "Bob");

    std::cout << "Employee 1: ID = " << emp1.id << ", Name = " << emp1.name << std::endl;
    std::cout << "Employee 2: ID = " << emp2.id << ", Name = " << emp2.name << std::endl;

    return 0;
}