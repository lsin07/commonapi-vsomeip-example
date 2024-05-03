// SpeedControlStubImpl.hpp
#ifndef SPEEDCONTROLSTUBIMPL_H
#define SPEEDCONTROLSTUBIMPL_H

#include <CommonAPI/CommonAPI.hpp>
#include <v1/Ace/Someip/SpeedControlStubDefault.hpp>

class SpeedControlStubImpl: public v1_0::Ace::Someip::SpeedControlStubDefault
{
    public:
        SpeedControlStubImpl();
        virtual ~SpeedControlStubImpl();
        virtual void Warning();
};

#endif
