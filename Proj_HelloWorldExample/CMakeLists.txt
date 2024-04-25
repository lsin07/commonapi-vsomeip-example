cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

# ~/src/commonapi-vsomeip-example/

include_directories(
    src-gen
    ${CMAKE_CURRENT_SOURCE_DIR}/../capicxx-core-runtime/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../capicxx-someip-runtime/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vsomeip/interface
)
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)

# 클라이언트 어플리케이션 빌드
add_executable(HelloWorldClient
    src/HelloWorldClient.cpp
    src-gen/v1/commonapi/HelloWorldSomeIPProxy.cpp
    src-gen/v1/commonapi/HelloWorldSomeIPDeployment.cpp
)
target_link_libraries(HelloWorldClient CommonAPI CommonAPI-SomeIP vsomeip3)

# 서비스 어플리케이션 빌드
# vsomeip 포함하여 로우 레벨 통신 처리
add_executable(HelloWorldService
    src/HelloWorldService.cpp
    src/HelloWorldStubImpl.cpp
    src-gen/v1/commonapi/HelloWorldSomeIPStubAdapter.cpp
    #src-gen/v1/commonapi/HelloWorldStubDefault.cpp
    src-gen/v1/commonapi/HelloWorldSomeIPDeployment.cpp
)
target_link_libraries(HelloWorldService CommonAPI CommonAPI-SomeIP vsomeip3)