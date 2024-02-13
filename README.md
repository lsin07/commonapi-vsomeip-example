# CommonAPI vsomeip Example
This repository is an implementation of the tutorial document  
https://github.com/COVESA/vsomeip/wiki/vsomeip-in-10-minutes

Check out the documentation above for more information.

## Prerequisites

Required Features:
- CMake
- Expat
- Java 8 Runtime Environment
- Boost library
- DBus library

In Debian/Ubuntu, you can install those features with:  
~~~bash
sudo apt install -y cmake cmake-qt-gui libexpat-dev expat default-jre libdbus-1-dev libboost-all-dev
~~~

## Clone Repos

~~~bash
git clone https://github.com/lsin07/commonapi-vsomeip-example.git --recurse-submodules
~~~

You need to add `--recurse-submodules` option in order to import all required CommonAPI repositories.  
Or, you can type `git submodule init` and `git submodule update` to get all missing submodules if the repository was cloned without recurse option.

## Build
- Build CommonAPI Libraries ― This may take a while.
~~~bash
./build_lib.sh
~~~

- Build Source Code
~~~bash
./build.sh
~~~

## Configuration
Configuration files for server and client application are at `/configs` directory.

You need to match `"unicast"` address with the address of your machine before running the applications.

## Run
- Run Server
~~~bash
LD_LIBRARY_PATH=install_folder/lib/:$PWD/build/ VSOMEIP_CONFIGURATION=configs/config_server.json ./build/service-example
~~~

- Run Client
~~~bash
LD_LIBRARY_PATH=install_folder/lib/:$PWD/build/ VSOMEIP_CONFIGURATION=configs/config_client.json ./build/client-example
~~~