#!/bin/bash

display_error() {
    echo "Something went wrong, try again."
}
trap 'display_error; exit 1' ERR
set -e

# prerequisites
# sudo apt update
# sudo apt upgrade -y
# sudo apt install -y cmake cmake-qt-gui libexpat-dev expat default-jre libdbus-1-dev libboost-all-dev

# build CommonAPI
cd capicxx-core-runtime
mkdir -p build
cd build
cmake ..
make

# build vsomeip
cd ../../vsomeip
mkdir -p build
cd build
cmake ..
make

# build commonapi someip rt
cd ../../capicxx-someip-runtime
mkdir -p build
cd build
cmake -DUSE_INSTALLED_COMMONAPI=OFF ..
make

# copy libraries into common library directory
cd ../..
mkdir -p lib
cp capicxx-core-runtime/build/lib* lib/
cp vsomeip/build/lib* lib/
cp capicxx-someip-runtime/build/lib* lib/

echo "Build Process Finished Successfully."