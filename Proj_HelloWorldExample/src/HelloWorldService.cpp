// HelloWorldServer.cpp
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "HelloWorldStubImpl.hpp"

using namespace std;

int main() {
    // get() 통해 runtime 인스턴스 획득
    std::shared_ptr <CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "test";                  // Proxy instance name must be identical with InstanceID in HelloWorld.fdepl
    std::string connection = "HelloWorldService";   // Connection name must be identical with the value of the key "routing" in config file

    // HelloWorld 서비스의 Stub 클래스 인스턴스 생성
    std::shared_ptr <HelloWorldStubImpl> myService = std::make_shared<HelloWorldStubImpl>();
    // registerService() 통해 runtime에 서비스 등록
    // 위치: local, 이름: test, 처리: myServie(Stub)
    runtime->registerService(domain, instance, myService, connection);
    std::cout << "Successfully Registered Service!" << std::endl;
    
    // 서비스가 클라이언트 호출을 기다림
    while (true) {
        std::cout << "Wating for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(30)); 
    }

    return 0;

}