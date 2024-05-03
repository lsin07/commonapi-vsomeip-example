// SpeedControlStubImpl.cpp
#include "SpeedControlStubImpl.hpp"

SpeedControlStubImpl::SpeedControlStubImpl() { }
SpeedControlStubImpl::~SpeedControlStubImpl() { }

using namespace v1::Ace::Someip;

void SpeedControlStubImpl::Warning() {
    SpeedControl::WarningInfo warning = SpeedControl::WarningInfo::OVERSPEEDWARNING;
    while (true) {
        fireWarningEvent(warning);
        std::cout << "warning broadcasted: OVERSPEEDWARNING" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); 
    }
};

void SpeedControlStubImpl::Brake(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _breakValue) {
    std::cout << "Brake requested with value: " << _breakValue << std::endl;
};