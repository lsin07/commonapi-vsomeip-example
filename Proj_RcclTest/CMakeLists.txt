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
add_executable(RcclTestClient
    src/RcclTestClient.cpp
    src-gen/v1/rccltest/RcclTestSomeIPProxy.cpp
    src-gen/v1/rccltest/RcclTestSomeIPDeployment.cpp
)
target_link_libraries(RcclTestClient CommonAPI CommonAPI-SomeIP vsomeip3)