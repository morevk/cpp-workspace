#include <iostream>
#include <memory>

void DynamicArrayUsingRawPtr() {
    int *p{ new int[5]{1,2,3,4,5} };

    p[0] *= 10;

    std::cout << "DynamicArrayUsingRawPtr=> " << p[0] << std::endl;

    delete[] p;
}

void DynamicArrayUsingUniquePtr() {
    std::unique_ptr<int[]> p{ new int[5]{1,2,3,4,5} };

    p[0] *= 10;

    std::cout << "DynamicArrayUsingUniquePtr=> " << p[0] << std::endl;
}

void DynamicArrayUsingSharedPtr() {
    std::shared_ptr<int[]> p{ new int[5]{1,2,3,4,5} };

    p[0] *= 10;

    std::cout << "DynamicArrayUsingSharedPtr=> " << p[0] << std::endl;
}

struct Deleter {

    void operator()(int *p) {
        std::cout << "Deleter called" << std::endl;
        delete[] p;
    }
};

void DynamicArrayUsingUniquePtrWithCustomDeletor() {
    std::unique_ptr<int[], Deleter> p{ new int[5]{1,2,3,4,5}, Deleter{} };

    p[0] *= 10;

    std::cout << "DynamicArrayUsingUniquePtrWithCustomDeletor=> " << p[0] << std::endl;
}

int test_dynamic_array_main(){
   
    DynamicArrayUsingRawPtr();

    DynamicArrayUsingUniquePtr();
    DynamicArrayUsingSharedPtr();

    DynamicArrayUsingUniquePtrWithCustomDeletor();
    return 0;
}