// SpeedControlStubImpl.hpp
#ifndef SPEEDCONTROLSTUBIMPL_H_
#define SPEEDCONTROLSTUBIMPL_H_

#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/Ace/Someip/SpeedControlStubDefault.hpp>

using namespace v1_0::Ace::Someip;

class SpeedControlStubImpl: public SpeedControlStubDefault
{
    public:
        SpeedControlStubImpl();
        virtual ~SpeedControlStubImpl();
        virtual void Warning();
        virtual void Brake(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _brakeValue);
        virtual void Accelerate(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _accelerateValue, AccelerateReply_t _reply);
};

#endif
