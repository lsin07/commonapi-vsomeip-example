// SpeedControlClient.cpp
#include <iostream>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/Ace/Someip/SpeedControlProxy.hpp>

using namespace v1_0::Ace::Someip;

int main()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    
    std::string domain = "local";
    std::string instance = "Ace.Someip.SpeedControl";
    std::string connection = "SpeedControlClient";

    std::shared_ptr<SpeedControlProxy<>> myProxy = runtime->buildProxy <SpeedControlProxy> (domain, instance, connection);

    while (!myProxy->isAvailable()) {
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    std::cout << "Service available." << std::endl;

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
        std::cout << "Recieved Warning: " << warningMessage << std::endl;
    });

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}