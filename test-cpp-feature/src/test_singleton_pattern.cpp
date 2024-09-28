#include <iostream>
#include <mutex>

class Singleton{
public:
    static Singleton& GetInstance(){
        std::lock_guard<std::mutex> lock(mutex_);

        if(ptr_ == nullptr)
            ptr_ = new Singleton();
        return *ptr_;
    }
    
    void SetCount(int i){
        count_ = i;
    }

    int GetCount() const{
        return count_;
    }
private:
    static Singleton* ptr_;
    static std::mutex mutex_;
    int count_{};

    Singleton(){
        std::cout << "in constructor" << std::endl;
    }

    ~Singleton(){   //never be called
        std::cout << "in destructor" << std::endl;
    }

    Singleton(const Singleton&) = delete;
};

Singleton* Singleton::ptr_{nullptr};
std::mutex Singleton::mutex_;

int test_singleton_pattern(){

    //Singleton ob;   //NG
    //Singleton ob1{*new Singleton()};    //NG
    std::cout << Singleton::GetInstance().GetCount() << std::endl;
    Singleton::GetInstance().SetCount(20);
    std::cout << Singleton::GetInstance().GetCount() << std::endl;

    return 0;
}