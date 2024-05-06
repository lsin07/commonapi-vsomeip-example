// SpeedControlClient.cpp
#include <iostream>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/Ace/Someip/SpeedControlProxy.hpp>

using namespace v1_0::Ace::Someip;

int main()
{
    // --- 1. Get a pointer to the runtime object ---
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    
    /*
     --- 2. Initialize a Proxy --- 
        Proxy is required to be able to communicate with a specific service.
    */
    std::string domain = "local";
    std::string instance = "Ace.Someip.SpeedControl";
    std::string connection = "SpeedControlClient";
    std::shared_ptr<SpeedControlProxy<>> myProxy = runtime->buildProxy <SpeedControlProxy> (domain, instance, connection);

    // --- 3. Wait for the service to be available ---
    std::cout << "Waiting for service to become available..." << std::endl;
    while (!myProxy->isAvailable()) {
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    std::cout << "Service available." << std::endl;

    /*  
    --- 4. Set subscription to the warning event ---
        Provide a listener as a parameter of 'subscribe()' function.
        The listener is a function which describes the action of the client when the event has triggered.
        In other words, the lambda function defined below will be executed only when the warning message
        has recieved.
    */
    myProxy->getWarningEvent().subscribe([&](const SpeedControl::WarningInfo& warning) {
        std::string warningMessage;
        switch (warning) {
            case SpeedControl::WarningInfo::NOWARNING:
                warningMessage = "No warning";
                break;
            case SpeedControl::WarningInfo::OVERSPEEDWARNING:
                warningMessage = "Speed exceeds limit!";
                break;
            case SpeedControl::WarningInfo::LOWFUELWARNING:
                warningMessage = "Low fuel!";
                break;
            case SpeedControl::WarningInfo::ICEWARNING:
                warningMessage = "Icy conditions!";
                break;
            default:
                warningMessage = "Unknown warning";
                break;
        }
        std::cout << "[R] Recieved Warning: " << warningMessage << std::endl;
    });

    // set required parameter variables
    uint32_t brakeValue = 1;
    uint32_t speed;
    uint32_t acc = 2;
    SpeedControl::ErrorCode errorCode;
    CommonAPI::CallStatus callStatus;

    // --- 5. main loop ---
    while (true) {

        // --- 5-1. Call getter to get the value of 'Speed' attribute ---
        myProxy->getSpeedAttribute().getValue(callStatus, speed);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            std::cerr << "Remote call failed!\n";
            return -1;
        }
        std::cout << "[R] Current Speed: " << speed << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // --- 5-2. Call method 'Accelerate' ---
        // This method increases the speed by '_accelerateValue'. More infos are at 'SpeedControlStubImpl.cpp'.
        myProxy->Accelerate(acc, callStatus, errorCode);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            std::cerr << "Remote call failed!\n";
            return -1;
        }
        // check if the return of the method is NOERROR.
        if (errorCode == SpeedControl::ErrorCode::NOERROR)
            std::cout << "[T] Accelerate request sent successfully with value " << acc << std::endl;
        else std::cout << "[T] Accelerate request sent with invalid value!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // --- 5-3. Call method 'Brake' ---
        // This method decreases the speed by '_brakeValue'. More infos are at 'SpeedControlStubImpl.cpp'.
        myProxy->Brake(brakeValue, callStatus);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            std::cerr << "Remote call failed!\n";
            return -1;
        }
        std::cout << "[T] Brake request sent with value " << brakeValue << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
