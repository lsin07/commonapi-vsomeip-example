// SpeedControlService.cpp

#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "SpeedControlStubImpl.hpp"

int main() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "Ace.Someip.SpeedControl";
    std::string connection = "SpeedControlService";

    std::shared_ptr<SpeedControlStubImpl> myService = std::make_shared<SpeedControlStubImpl>();
    runtime->registerService(domain, instance, myService, connection);
    std::cout << "Service Registered Successfully." << std::endl;

    myService->Warning();
    
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
