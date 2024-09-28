#include <iostream>
#include <mutex>

class Subject;

class IObservable{
    public:
    virtual ~IObservable(){

    }
    virtual void OnUpdate(const Subject& sub) const = 0;
};

class Subject final{
    public:
    void Subscribe(IObservable& ob_to_add){
        for(auto& observer: observers_){
            if(observer == nullptr) {
                observer = &ob_to_add;
                break;
            }            
        }
    }
    void notify() const {
        for(auto observer : observers_) {
            if(observer != nullptr) {
                observer->OnUpdate(*this);
            }
        }
    }
    void SetCount(int i){
        count_ = i;

        notify();
    }

    int GetCount() const{
        return count_;
    }

    private:
    uint32_t count_{};
    static constexpr uint32_t MAX_OBSERVERS{5};
    IObservable* observers_[MAX_OBSERVERS]{};

};

class Observer final:public IObservable
{
private:
    /* data */
public:
    Observer(/* args */){
    }

    ~Observer(){
    }

    void OnUpdate(const Subject& sub) const override {

        std::cout << "In observer update: " << sub.GetCount() << std::endl;
    }
};


int test_observer_pattern(){

    Subject sub;

    Observer ob1;

    sub.Subscribe(ob1);
    sub.SetCount(50);

    return 0;
}