# CommonAPI vsomeip Example
This repository is an implementation of the tutorial document  
https://github.com/COVESA/vsomeip/wiki/vsomeip-in-10-minutes

## Clone Repos

~~~bash
git clone https://github.com/lsin07/commonapi-vsomeip-example.git --recurse-submodules
~~~

You need to add `--recurse-submodules` option to import all required CommonAPI repositories.  
Or, you can type `git submodule init` and `git submodule update` to get all missing submodules if the reopsitory was cloned without recurse option.

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

TBA

## Run
- Run Server
~~~bash
LD_LIBRARY_PATH=install_folder/lib/:$PWD/build/ VSOMEIP_CONFIGURATION=configs/config_server.json ./build/service-example
~~~

- Run Client
~~~bash
LD_LIBRARY_PATH=install_folder/lib/:$PWD/build/ VSOMEIP_CONFIGURATION=configs/config_client.json ./build/client-example
~~~