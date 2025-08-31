#include <iostream>

class Core{
    public:
    virtual void store_config(){
        std::cout << "In Core::store_config" << std::endl;
    }
    virtual void store_config(bool sync){
        std::cout << "In Core::store_config(bool)" << std::endl;
        Core::store_config();
    }
};

class Auth: public Core{
    public:
    virtual void store_config() override{
        std::cout << "In Auth::store_config" << std::endl;
        store_config(true);
    }
    virtual void store_config(bool sync) override{
        std::cout << "In Auth::store_config(bool)" << std::endl;
    }
};

class Time: public Core{
    public:
    virtual void store_config() override{
        std::cout << "In Time::store_config" << std::endl;
    }
};

int test_inheritance_main()
{
    Auth auth;
    Time time;
    
    Core &core = auth;
    core.store_config();
    core.store_config(true);

    Core &core1 = time;
    core1.store_config();
    core1.store_config(true);
    
    return 0;
}