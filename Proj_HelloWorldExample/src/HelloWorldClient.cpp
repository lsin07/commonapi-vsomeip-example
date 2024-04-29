// HelloWorldClient.cpp
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/HelloWorldProxy.hpp>

using namespace v1_0::commonapi;

int main() {
    // Runtime Instance 가져오기
    std::shared_ptr <CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    // Proxy 생성 - 위치: "local", 이름: "test"
    std::string domain = "local";
    std::string instance = "test";                  // Proxy instance name must be identical with InstanceID in HelloWorld.fdepl
    std::string connection = "client-sample";       // Connection name must be identical with the value of the key "routing" in config file
    std::shared_ptr <HelloWorldProxy<>> myProxy = runtime->buildProxy<HelloWorldProxy>(domain, instance, connection);

    // Checking availability (Proxy) : 생성을 기다림 
    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable()) {
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    std::cout << "Available ..." << std::endl;

    // 메서드 호출 상태 나타내는 Enum type 변수 선언
    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    const std::string name = "World";
    while (true) {
        // CommonAPI의 Proxy 인스턴스인 myProxy로 sayHello 메서드 호출
        myProxy->sayHello(name, callStatus, returnMessage);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            std::cerr << "Remote call failed!\n";
            return -1;
        }
        // 반환 메시지 출력
        std::cout << "Got message: '" << returnMessage << "'\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}