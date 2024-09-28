#include <iostream>
#include <memory>

class Printer{
    std::shared_ptr<int> m_ptr{};
public:
    void setValue(std::shared_ptr<int> ptr){
        m_ptr = ptr;
    }

    void Print(){
        std::cout << "reference count " << m_ptr.use_count() << std::endl;
        std::cout << "value is " << *m_ptr << std::endl; 
    }
};

int test_shared_ptr_main(){
    Printer prn;
    int num{};
    std::cin >> num;

    std::shared_ptr<int> ptr{new int{num}}; //ref count 1
    prn.setValue(ptr); //ref count 2

    if(*ptr > 10){
        ptr = nullptr; //ref count 1 but memory is not released
    }

    prn.Print();

    return 0;
}