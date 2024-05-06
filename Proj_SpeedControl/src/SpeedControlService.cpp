// SpeedControlService.cpp
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "SpeedControlStubImpl.hpp"

int main() 
{
    // --- 1. Get a pointer to the runtime object ---
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();


    // --- 2. Instantiate the stub implementation as a service and register it. ---
    std::string domain = "local";
    std::string instance = "Ace.Someip.SpeedControl";
    std::string connection = "SpeedControlService";

    std::shared_ptr<SpeedControlStubImpl> myService = std::make_shared<SpeedControlStubImpl>();
    runtime->registerService(domain, instance, myService, connection);
    std::cout << "Service Registered Successfully." << std::endl;

    // --- 3. Initiate Warning event generator of the service ---
    myService->Warning();
    
    /*
    --- 4. Main loop. Do nothing. ---
        There is nothing to do here because every method implementations are defined at
        'SpeedControlStubImpl.cpp'. Just for making sure that the service app is up.
    */
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
