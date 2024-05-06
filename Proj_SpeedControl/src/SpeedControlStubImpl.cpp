// SpeedControlStubImpl.cpp
#include "SpeedControlStubImpl.hpp"

SpeedControlStubImpl::SpeedControlStubImpl() { }
SpeedControlStubImpl::~SpeedControlStubImpl() { }

using namespace v1::Ace::Someip;

/* # Warning
 * @brief Fire warning event every 5 seconds.
 * @return No return.
 */
void SpeedControlStubImpl::Warning() {
    SpeedControl::WarningInfo warning = SpeedControl::WarningInfo::LOWFUELWARNING;    // set warning info
    
    // broadcast current warning every 5 seconds indefinitely
    while (true) {
        fireWarningEvent(warning);
        std::cout << "[T] warning broadcasted: LOWFUELWARNING" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
};

/* # Brake
 * @brief reduce speed by `_brakevalue`.
 * @param _brakevalue
 * @param callStatus
 * @return No return.
 */
void SpeedControlStubImpl::Brake(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _brakeValue) {
    uint32_t speed = SpeedControlStubDefault::getSpeedAttribute();   // get current speed
    uint32_t new_speed = speed - _brakeValue;    // calculate desired speed
    std::cout << "[R] Brake request accepted -- reducing speed to: " << new_speed << std::endl;
    SpeedControlStubDefault::setSpeedAttribute(new_speed);    // set speed value to new speed
    fireSpeedAttributeChanged(new_speed);    // notify speed change
};

/* # Accelerate
 * @brief increase speed by `_accelerateValue`.
 * @param _accelerateValue
 * @param callStatus
 * @param _reply
 * @return ErrorCode
 */
void SpeedControlStubImpl::Accelerate(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _accelerateValue, AccelerateReply_t _reply) {
    uint32_t speed = SpeedControlStubDefault::getSpeedAttribute();   // get current speed
    uint32_t new_speed = _accelerateValue + speed;    // calculate desired speed
    std::cout << "[R] Accelerate request accepted -- accelerating to: " << new_speed << std::endl;
    SpeedControlStubDefault::setSpeedAttribute(new_speed);    // set speed value to new speed
    fireSpeedAttributeChanged(new_speed);    // notify speed change
    _reply(SpeedControl::ErrorCode::NOERROR);    // return error code
};