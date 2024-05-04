// SpeedControlStubImpl.cpp
#include "SpeedControlStubImpl.hpp"

SpeedControlStubImpl::SpeedControlStubImpl() { }
SpeedControlStubImpl::~SpeedControlStubImpl() { }

using namespace v1::Ace::Someip;

void SpeedControlStubImpl::Warning() {
    SpeedControl::WarningInfo warning = SpeedControl::WarningInfo::LOWFUELWARNING;
    while (true) {
        fireWarningEvent(warning);
        std::cout << "warning broadcasted: LOWFUELWARNING" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); 
    }
};

void SpeedControlStubImpl::Brake(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _brakeValue) {
    std::cout << "Brake requested with value: " << _brakeValue << std::endl;
};