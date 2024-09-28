#include <iostream>
#include <mutex>
#include <future>

class Subject;

class ICommand{
    public:
    virtual ~ICommand(){

    }
    virtual void Execute() const = 0;
};

class ICommandStateReciever{
    public:
    virtual ~ICommandStateReciever(){

    }
    virtual void PreExecute() const = 0;
    virtual void PostExecute() const = 0;
};

class CommandExecuter final{

    public:
    static int ExecuteCommand(ICommand &command, ICommandStateReciever* reciever){
        if(reciever != nullptr){
            reciever->PreExecute();
        }

        command.Execute();

        if(reciever != nullptr){
            reciever->PostExecute();
        }

        return 0;
    }
    static std::future<int> DispatchCommand(ICommand &command, ICommandStateReciever* reciever){
        return std::async([&command, &reciever]{return CommandExecuter::ExecuteCommand(command, reciever);});
    }
};

class SimpleCommand:public ICommand{
    public:
    void Execute() const{
        std::cout << "SimpleCommand execution: " << std::endl;
    }
};

class Reciever:public ICommandStateReciever{

    public:
    void PreExecute() const {
        std::cout << "Reciever PreExecute: " << std::endl;
    }
    void PostExecute() const {
        std::cout << "Reciever PostExecute: " << std::endl;
    };
};



int test_command_pattern(){

    SimpleCommand cmd;

    Reciever rcv;

    CommandExecuter::ExecuteCommand(cmd,&rcv);
    CommandExecuter::ExecuteCommand(cmd,nullptr);
    
    std::future<int> fut = CommandExecuter::DispatchCommand(cmd, &rcv);

    std::cout << "doing something in main" << std::endl;

    std::cout << "get commmand result: "<< fut.get() << std::endl;

    // ICommand& icmd = cmd;
    // ICommandStateReciever& ircv = rcv;
    // std::async([&icmd, &ircv]{CommandExecuter::ExecuteCommand(icmd, &ircv);}).get();

    return 0;
}