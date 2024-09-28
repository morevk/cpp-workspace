#if 1
#include <iostream>
#include <string>
#include <future>
#include <thread>

void do_work(std::promise<int> &p)
{
    std::cout << "do_work(), start" << '\n';
    std::this_thread::sleep_for(std::chrono::microseconds(2000));
    p.set_value(100);
    std::cout << "do_work(), end" << '\n';
}

int test_promise_future_main()
{
    std::promise<int> p;

    std::thread t(do_work,std::ref(p));

    std::cout << "Before get_future()" << '\n';

    int result = p.get_future().get();

    std::cout << "Back in main(), result = " << result << '\n';

    t.join();

    return 0;
}
#endif