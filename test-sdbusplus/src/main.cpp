#include <simple_dbus_server.h>

int main()
{
    boost::asio::io_context ioc;
    boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);

    signals.async_wait([&ioc](const boost::system::error_code&, const int&) {
        std::cout << "\nShutting down server...\n";
        ioc.stop();
    });

    try {
        SimpleServer server(ioc);
        std::cout << "Server running. Press Ctrl+C to stop.\n";
        ioc.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}