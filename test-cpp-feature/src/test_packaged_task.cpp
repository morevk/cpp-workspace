#if 1
#include <iostream>
#include <string>
#include <future>
#include <thread>

int f(int number)
{
    return number * number;
}

int test_packaged_task_main()
{
    std::packaged_task<int(int)> task(&f);
    //std::future<int> task_result = task.get_future();
    //std::thread task_thread(std::move(task),5);
    std::thread task_thread(std::ref(task),5);
    
    //task(6);  // runtime error: packaged task can not be called two times
    
    std::cout << "Back in main(), task result = " << task.get_future().get() << std::endl;

    std::flush(std::cout);
    task_thread.join();
    
    return 0;
}
#endif