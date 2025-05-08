#!/bin/bash

display_error() {
    echo "Build process stopped due to error(s)."
}
trap 'display_error; exit 1' ERR
set -e

PARALLEL_JOBS=${1:-1}
BUILD_DIR=build
INSTALL_FOLDER=./install_folder
CAPI_CORE_PATH=capicxx-core-runtime
CAPI_SOMEIP_PATH=capicxx-someip-runtime
VSOMEIP_PATH=vsomeip
CMAKE_OPTIONS="-DCMAKE_INSTALL_PREFIX=$INSTALL_FOLDER"
CMAKE_BUILD_OPTIONS="--target install --parallel $PARALLEL_JOBS"

if ! [[ "$PARALLEL_JOBS" =~ ^[0-9]+$ ]]; then
    echo "error: parallel_jobs must be numbers"
    exit 1
fi

# prerequisites
# sudo apt update
# sudo apt upgrade -y
# sudo apt install -y cmake cmake-qt-gui libexpat-dev expat default-jre libdbus-1-dev libboost-all-dev

cmake -B$BUILD_DIR/$CAPI_CORE_PATH $CMAKE_OPTIONS $CAPI_CORE_PATH
cmake -B$BUILD_DIR/$VSOMEIP_PATH $CMAKE_OPTIONS -DENABLE_SIGNAL_HANDLING=1 -DDIAGNOSIS_ADDRESS=0x10 $VSOMEIP_PATH
cmake -B$BUILD_DIR/$CAPI_SOMEIP_PATH $CMAKE_OPTIONS -DCMAKE_PREFIX_PATH=$INSTALL_FOLDER -DUSE_INSTALLED_COMMONAPI=OFF $CAPI_SOMEIP_PATH

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
# rm -rf build/

echo "Done."
