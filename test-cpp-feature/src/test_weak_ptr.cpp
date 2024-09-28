#include <iostream>
#include <memory>

class PrinterWeak{
    std::weak_ptr<int> m_ptr{};
public:
    void setValue(std::weak_ptr<int> ptr){
        m_ptr = ptr;
    }

    void Print(){
        
        if(m_ptr.expired()){
            std::cout << "underlying resource is released" << std::endl;
            return;
        } 

        auto sp = m_ptr.lock();
        std::cout << "value is " << *sp << std::endl; // resource access via shared ptr only 
        std::cout << "SP reference count " << sp.use_count() << std::endl;
        std::cout << "WP reference count " << m_ptr.use_count() << std::endl;   //weak ptr pointing to shared ptr only
    }
};

int test_weak_ptr_main(){
    PrinterWeak prn;
    int num{};
    std::cin >> num;

    std::shared_ptr<int> ptr{new int{num}}; //ref count 1
    prn.setValue(ptr); //ref count 1

    if(*ptr > 10){
        ptr = nullptr; //ref count 1 and memory is released
    }

    prn.Print();

    return 0;
}