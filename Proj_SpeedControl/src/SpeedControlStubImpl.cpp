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
}
