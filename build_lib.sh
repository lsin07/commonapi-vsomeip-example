#!/bin/bash

display_error() {
    echo "Something went wrong, try again."
}
trap 'display_error; exit 1' ERR
set -e

PARALLEL_JOBS=${1:-1}

if ! [[ "$1" =~ ^[0-9]+$ ]]; then
  echo "error: parallel_jobs must be numbers"
  exit 1
fi

# prerequisites
# sudo apt update
# sudo apt upgrade -y
# sudo apt install -y cmake cmake-qt-gui libexpat-dev expat default-jre libdbus-1-dev libboost-all-dev

cmake -S capicxx-core-runtime/ -B build/capicxx-core-runtime/
cmake --build build/capicxx-core-runtime/ --parallel "$PARALLEL_JOBS"

cmake -S vsomeip/ -B build/vsomeip
cmake --build build/vsomeip --parallel "$PARALLEL_JOBS"

cmake -DUSE_INSTALLED_COMMONAPI=OFF -S capicxx-someip-runtime/ -B build/capicxx-someip-runtime/
cmake --build build/capicxx-someip-runtime/ --parallel "$PARALLEL_JOBS"

# copy libraries into common library directory
mkdir -p lib
cp build/capicxx-core-runtime/lib* lib/
cp build/vsomeip/lib* lib/
cp build/capicxx-someip-runtime/lib* lib/

echo "Build Process Finished Successfully."