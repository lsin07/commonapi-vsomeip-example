// SpeedControlStubImpl.cpp
#include "SpeedControlStubImpl.hpp"

SpeedControlStubImpl::SpeedControlStubImpl() { }
SpeedControlStubImpl::~SpeedControlStubImpl() { }

using namespace v1::Ace::Someip;

/* # Warning
 * @brief Fire warning event every 1 seconds.
 * @return No return.
 */
void SpeedControlStubImpl::Warning() {
    SpeedControl::WarningInfo warning;
    uint32_t curr_speed;
    std::string warningtext;

    while (true) {
        curr_speed = SpeedControlStubDefault::getSpeedAttribute();  // get current speed
        if (curr_speed > 50) {
            warning = SpeedControl::WarningInfo::OVERSPEEDWARNING;  // if current speed > 50, fire overspeed warning event
            warningtext = "OVERSPEEDWARNING";
        }
        else {
            warning = SpeedControl::WarningInfo::NOWARNING;         // if no warning condition is set, fire nowarning event
            warningtext = "NOWARNING";
        }
        std::cout << "[T] warning broadcasted: " << warningtext << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));       // wait 1 second
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
    uint32_t new_speed = 0;
    if (speed >= _brakeValue) new_speed = speed - _brakeValue;    // calculate desired speed
    std::cout << "[R] Brake request accepted -- reducing speed to: " << new_speed << std::endl;
    SpeedControlStubDefault::setSpeedAttribute(new_speed);    // set speed value to new speed
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
    _reply(SpeedControl::ErrorCode::NOERROR);    // return error code
};