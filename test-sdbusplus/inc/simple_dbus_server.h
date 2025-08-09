#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>
#include <sdbusplus/asio/connection.hpp>
#include <sdbusplus/asio/object_server.hpp>

#include <iostream>
#include <memory>
#include <string>

class SimpleServer
{
public:
    SimpleServer(boost::asio::io_context& ioc);
private:
    void registerProperties();
    void registerMethods();
    
    std::shared_ptr<sdbusplus::asio::connection> bus_;
    std::unique_ptr<sdbusplus::asio::object_server> objServer_;
    std::shared_ptr<sdbusplus::asio::dbus_interface> interface_;
    int32_t counter_ = 0;
};