cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

# To depress undefined error, may not a proper solution.
add_definitions(-DUNDEFINED_EVENTGROUP_ID=0xFFFF)

include_directories(
    src-gen
    ${CMAKE_CURRENT_SOURCE_DIR}/../capicxx-core-runtime/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../capicxx-someip-runtime/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vsomeip/interface
)
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)

add_executable(SpeedControlClient
    src/SpeedControlClient.cpp
    src-gen/v1/Ace/Someip/SpeedControlSomeIPProxy.cpp
    src-gen/v1/Ace/Someip/SpeedControlSomeIPDeployment.cpp
)
target_link_libraries(SpeedControlClient CommonAPI CommonAPI-SomeIP vsomeip3)

add_executable(SpeedControlService
    src/SpeedControlService.cpp
    src/SpeedControlStubImpl.cpp
    src-gen/v1/Ace/Someip/SpeedControlSomeIPStubAdapter.cpp
    #src-gen/v1/Ace/Someip/SpeedControlStubDefault.cpp
    src-gen/v1/Ace/Someip/SpeedControlSomeIPDeployment.cpp
)
target_link_libraries(SpeedControlService CommonAPI CommonAPI-SomeIP vsomeip3)