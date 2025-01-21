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

cmake -S capicxx-core-runtime/ -B capicxx-core-runtime/build/
cmake --build capicxx-core-runtime/build/

cmake -S vsomeip/ -B vsomeip/build/
cmake --build vsomeip/build/

cmake -DUSE_INSTALLED_COMMONAPI=OFF -S capicxx-someip-runtime/ -B capicxx-someip-runtime/build/
cmake --build capicxx-someip-runtime/build/

# copy libraries into common library directory
mkdir -p lib
cp capicxx-core-runtime/build/lib* lib/
cp vsomeip/build/lib* lib/
cp capicxx-someip-runtime/build/lib* lib/

echo "Build Process Finished Successfully."