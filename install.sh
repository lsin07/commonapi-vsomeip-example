#!/bin/bash

display_error() {
    echo "Build process stopped."
}
trap 'display_error; exit 1' ERR
set -e

PARALLEL_JOBS=${1:-1}
BUILD_DIR=build
LIB_DIR=../../lib
CAPI_CORE_PATH=capicxx-core-runtime
CAPI_SOMEIP_PATH=capicxx-someip-runtime
VSOMEIP_PATH=vsomeip
CMAKE_OPTIONS="-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$LIB_DIR"
CMAKE_BUILD_OPTIONS="--parallel $PARALLEL_JOBS"

if ! [[ "$PARALLEL_JOBS" =~ ^[0-9]+$ ]]; then
    echo "error: parallel_jobs must be numbers"
    exit 1
fi

# prerequisites
# sudo apt update
# sudo apt upgrade -y
# sudo apt install -y cmake cmake-qt-gui libexpat-dev expat default-jre libdbus-1-dev libboost-all-dev

cmake $CMAKE_OPTIONS -S $CAPI_CORE_PATH -B $BUILD_DIR/$CAPI_CORE_PATH
cmake $CMAKE_OPTIONS -S $VSOMEIP_PATH -B $BUILD_DIR/$VSOMEIP_PATH
cmake -DUSE_INSTALLED_COMMONAPI=OFF $CMAKE_OPTIONS -S $CAPI_SOMEIP_PATH -B $BUILD_DIR/$CAPI_SOMEIP_PATH

cmake --build $BUILD_DIR/$CAPI_CORE_PATH $CMAKE_BUILD_OPTIONS
cmake --build $BUILD_DIR/$VSOMEIP_PATH $CMAKE_BUILD_OPTIONS
cmake --build $BUILD_DIR/$CAPI_SOMEIP_PATH $CMAKE_BUILD_OPTIONS

# download cgen
if [ ! -d "cgen" ]; then
    mkdir cgen/
fi
if [ ! -d "cgen/commonapi_core_generator" ]; then
    wget https://github.com/COVESA/capicxx-core-tools/releases/download/3.2.15/commonapi_core_generator.zip -O cgen/commonapi_core_generator.zip
    unzip cgen/commonapi_core_generator.zip -d cgen/commonapi_core_generator
    rm cgen/commonapi_core_generator.zip
else
    echo "commonapi_core_generator already exists."
fi
if [ ! -d "cgen/commonapi_someip_generator" ]; then
    wget https://github.com/COVESA/capicxx-someip-tools/releases/download/3.2.15/commonapi_someip_generator.zip -O cgen/commonapi_someip_generator.zip
    unzip cgen/commonapi_someip_generator.zip -d cgen/commonapi_someip_generator
    rm cgen/commonapi_someip_generator.zip
else
    echo "commonapi_someip_generator already exists."
fi

# clean
rm -rf build/

echo "Done."
