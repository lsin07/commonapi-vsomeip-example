#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/rccltest/RcclTestProxy.hpp>

using namespace v1_0::rccltest;

int main()
{
    std::shared_ptr <CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::string domain = "local";
    std::string instance = "RcclTest";                  // Proxy instance name must be identical with InstanceID in HelloWorld.fdepl
    std::string connection = "RcclTestListener";    // Connection name must be identical with the value of the key "routing" in config file
    std::shared_ptr <RcclTestProxy<>> myProxy = runtime->buildProxy<RcclTestProxy>(domain, instance, connection);

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable()) {
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    std::cout << "Available ..." << std::endl;

    CommonAPI::CallStatus callStatus;

    myProxy->getHelloEvent().subscribe([&](const std::string message) {
        std::cout << "got meesage: " << message << std::endl;
    });

    while (true) {
        // std::cout << "Wating for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(30)); 
    }
}