#!/bin/bash

display_error() {
    echo "Build process stopped due to error(s)."
}
trap 'display_error; exit 1' ERR
set -e

# source generation
CGEN_DIR=../cgen
SRC_GEN_DIR=src-gen

$CGEN_DIR/commonapi_core_generator/commonapi-core-generator-linux-x86_64 -d $SRC_GEN_DIR/core -sk ./fidl/HelloWorld.fidl
$CGEN_DIR/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64 -d $SRC_GEN_DIR/someip ./fidl/HelloWorld.fdepl

# build
cmake -Bbuild -DCMAKE_PREFIX_PATH=$(realpath ../install_folder) -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON .
cmake --build build
