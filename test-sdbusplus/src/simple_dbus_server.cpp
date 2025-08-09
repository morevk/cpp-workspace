#include <simple_dbus_server.h>

#include <iostream>
#include <memory>
#include <string>

SimpleServer::SimpleServer(boost::asio::io_context& ioc) : 
    bus_(std::make_shared<sdbusplus::asio::connection>(ioc)),
    objServer_(std::make_unique<sdbusplus::asio::object_server>(bus_))
{
    // Request a well-known service name
    bus_->request_name("com.example.SimpleService");
    
    // Create a D-Bus interface
    interface_ = objServer_->add_interface("/com/example/SimpleObject",
                                            "com.example.SimpleInterface");
    
    // Register properties
    registerProperties();
    
    // Register methods
    registerMethods();
    
    // Initialize the interface (makes it available on D-Bus)
    interface_->initialize();
    
    std::cout << "Server started on com.example.SimpleService\n";
}


void SimpleServer::registerProperties()
{
    // Read-write property with validation
    interface_->register_property(
        "Counter", counter_,
        //sdbusplus::asio::PropertyPermission::readWrite,
        [this](const int32_t& newValue, int32_t& property) {
            if (newValue < 0) {
                std::cout << "Rejecting negative counter value: " << newValue << "\n";
                return false;
            }
            property = newValue;
            counter_ = newValue;
            std::cout << "Counter updated to: " << newValue << "\n";
            return true;
        });

    // Read-only property with custom getter
    interface_->register_property(
        "Status", std::string("Ready"),
        //sdbusplus::asio::PropertyPermission::readOnly,
        [this](const std::string& newValue, std::string& property) {
            std::cout << "Rejecting as set can not be performed on read only " << newValue << " " << property << "\n";
            return false;
        }, // no setter for read-only
        [this](const std::string& property) {
            std::string status = counter_ > 10 ? "High" : "Normal";
            return property + status;
        });
}

void SimpleServer::registerMethods()
{
    // Simple method that increments counter
    interface_->register_method("Increment", 
        [this]() -> int32_t {
            ++counter_;
            std::cout << "Increment called, counter now: " << counter_ << "\n";
            
            // Emit property changed signal
            interface_->signal_property("Counter");
            
            return counter_;
        });

    // Method with parameters and return value
    interface_->register_method("Add",
        [this](int32_t a, int32_t b) -> int32_t {
            int32_t result = a + b;
            std::cout << "Add(" << a << ", " << b << ") = " << result << "\n";
            return result;
        });

    // Method that returns multiple values
    interface_->register_method("GetInfo",
        [this]() -> std::tuple<int32_t, std::string> {
            std::string status = counter_ > 10 ? "High" : "Normal";
            std::cout << "GetInfo called\n";
            return std::make_tuple(counter_, status);
        });

    // Method that emits a signal
    interface_->register_method("Reset",
        [this]() -> void {
            int32_t oldValue = counter_;
            counter_ = 0;
            std::cout << "Reset called, counter was: " << oldValue << "\n";
            
            // Emit custom signal
            auto signal = interface_->new_signal("CounterReset");
            signal.append(oldValue);
            signal.signal_send();
            
            // Emit property changed
            interface_->signal_property("Counter");
        });
}