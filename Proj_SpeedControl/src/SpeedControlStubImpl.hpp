// SpeedControlStubImpl.hpp
#ifndef SPEEDCONTROLSTUBIMPL_H_
#define SPEEDCONTROLSTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/Ace/Someip/SpeedControlStubDefault.hpp>

class SpeedControlStubImpl: public v1_0::Ace::Someip::SpeedControlStubDefault
{
    public:
        SpeedControlStubImpl();
        virtual ~SpeedControlStubImpl();
        virtual void Warning();
        virtual void Brake(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _brakeValue);
};

#endif
