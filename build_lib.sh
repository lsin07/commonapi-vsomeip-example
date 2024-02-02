#!/bin/bash

display_error() {
    echo "Something went wrong, try again."
}
trap 'display_error; exit 1' ERR
set -e

# prerequisites
sudo apt update
sudo apt upgrade -y
sudo apt install -y cmake cmake-qt-gui libexpat-dev expat default-jre libdbus-1-dev libboost-all-dev

# build CommonAPI Runtime Library
cd capicxx-core-runtime/
cmake -Bbuild -DCMAKE_INSTALL_PREFIX=../install_folder .
cmake --build build/ --target install
cd ..

# DBus patch
wget -N https://dbus.freedesktop.org/releases/dbus/dbus-1.12.16.tar.gz
tar -xvf dbus-1.12.16.tar.gz
for patch in capicxx-dbus-runtime/src/dbus-patches/*.patch
do
    patch -d dbus-1.12.16/ -p1 <"$patch"
done

# build libdbus
env -C dbus-1.12.16 ./configure --prefix=$(realpath install_folder)
make -C dbus-1.12.16/dbus/ install
make -C dbus-1.12.16/ install-pkgconfigDATA

# build CommonAPI DBus runtime library
export PKG_CONFIG_PATH="`pwd`/dbus-1.12.16"
cd capicxx-dbus-runtime/
cmake -Bbuild -DCMAKE_INSTALL_PREFIX=../install_folder -DCMAKE_PREFIX_PATH=../install_folder -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON -DUSE_INSTALLED_DBUS=OFF -DDBus1_DIR=../dbus-1.12.16/cmake .
cmake --build build --target install
cd ..

# build vsomeip
cd vsomeip
cmake -Bbuild -DCMAKE_INSTALL_PREFIX=../install_folder -DENABLE_SIGNAL_HANDLING=1 -DDIAGNOSIS_ADDRESS=0x10 .
cmake --build build --target install
cd ..

# build commonapi some/ip runtime library
cd capicxx-someip-runtime
cmake -Bbuild -DCMAKE_INSTALL_PREFIX=../install_folder -DCMAKE_PREFIX_PATH=../install_folder -DUSE_INSTALLED_COMMONAPI=OFF .
cmake --build build --target install

echo "Build Process Finished Successfully."