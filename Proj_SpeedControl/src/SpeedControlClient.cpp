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
    bool overspeedWarningReceived = false;

    myProxy->getWarningEvent().subscribe([&](const SpeedControl::WarningInfo& warning) {
        std::string warningmsg = "[R] Recieved Warning: ";
        switch (warning) {
            case SpeedControl::WarningInfo::NOWARNING:
                break;
            case SpeedControl::WarningInfo::OVERSPEEDWARNING:
                std::cout << warningmsg << "OVERSPEEDWARNING" << std::endl;
                overspeedWarningReceived = true;
                break;
            case SpeedControl::WarningInfo::LOWFUELWARNING:
                std::cout << warningmsg << "LOWFUELWARNING" << std::endl;
                break;
            case SpeedControl::WarningInfo::ICEWARNING:
                std::cout << warningmsg << "ICEWARNING" << std::endl;
                break;
            default:
                std::cout << "[R] ERROR - Unknown Warning!" << std::endl;
                break;
        }
    });

    /*
    --- 5. Set subscription to speed attribute change event ---
        This subscriber will act identically with the warning event subsriber.
        The event will be fired by the attribute notifier whenever the attribute value has changed,
        which means this listener function will be called only when the speed value has changed.
    */
    myProxy->getSpeedAttribute().getChangedEvent().subscribe([](const uint32_t& speed) {
        std::cout << "[R] Current Speed: " << speed << std::endl;
    });

    // set required parameter variables
    uint32_t brakeValue = 20;
    uint32_t accValue = 10;
    SpeedControl::ErrorCode errorCode;
    CommonAPI::CallStatus callStatus;

    // --- 6. main loop ---
    while (true) {

        if (!overspeedWarningReceived){
        // --- 6-1. Call method 'Accelerate' ---
        // This method increases the speed by '_accelerateValue'. More infos are at 'SpeedControlStubImpl.cpp'.
            myProxy->Accelerate(accValue, callStatus, errorCode);
            if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                std::cerr << "Remote call failed!\n";
                return -1;
            }
        // check if the return of the method is NOERROR.
            if (errorCode == SpeedControl::ErrorCode::NOERROR)
                std::cout << "[T] Accelerate request sent successfully with value " << accValue << std::endl;
            else std::cout << "[T] Accelerate request sent with invalid value!" << std::endl;
        }

        else{
        // --- 6-2. Call method 'Brake' ---
        // This method decreases the speed by '_brakeValue'. More infos are at 'SpeedControlStubImpl.cpp'.
            myProxy->Brake(brakeValue, callStatus);
            if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                std::cerr << "Remote call failed!\n";
                return -1;
            }
            std::cout << "[T] Brake request sent with value " << brakeValue << std::endl;
            overspeedWarningReceived = false;
        } 
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
