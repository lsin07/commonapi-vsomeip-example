# CommonAPI vsomeip Example

This repository is an automation of CommonAPI SOME-IP Tutorial (https://github.com/COVESA/capicxx-someip-tools/wiki/CommonAPI-C---SomeIP-in-10-minutes),
with one additional example project.

## Prerequisites

Required Features:
- C/C++ Compiler
- CMake
- Java Runtime Environment
- Boost C++ Library
- `wget`, `zip` package (to download and unzip code generators)

In Debian/Ubuntu, you can install those features with:  
~~~bash
sudo apt install -y wget zip build-essential cmake default-jre libboost-all-dev
~~~

## Clone Repos

~~~bash
git clone https://github.com/lsin07/commonapi-vsomeip-example.git --recurse-submodules
~~~

You need to add `--recurse-submodules` option in order to import all required CommonAPI repositories.  
Or, you can type `git submodule init` and `git submodule update` to get all missing submodules if the repository was cloned without recurse option.

## Install
<details>
<summary><b>(open/close) for developers using gcc12 or higher</b></summary>

If you are using gcc12 or above, you need to adjust some build configurations.

1. Add a line `#include <string>` to the header file `capicxx-core-runtime/include/CommonAPI/Types.hpp`.
2. Add a line `SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=stringop-overflow")` to the file `vsomeip/CMakeLists.txt` to supress overflow error.

Refer to the *<a href="https://github.com/COVESA/capicxx-core-runtime/issues/47">issue #47</a> of COVESA/capicxx-core-runtime* and *<a href="https://github.com/COVESA/vsomeip/issues/527">issue #527</a> of COVESA/vsomeip* for further informations.
</details>

Build CommonAPI Libraries ― This may take few minutes.
~~~bash
cd commonapi-vsomeip-example
./install.sh
~~~

This will build and install required libraries on `./install_folder`,
and download and unzip code generators on `./cgen`.

## Code Generation
> [!NOTE]
> The code generators used in this section are [capicxx-core-tools](https://github.com/COVESA/capicxx-core-tools/) 
> and [capicxx-someip-tools](https://github.com/COVESA/capicxx-someip-tools) ver. 3.2.15.  
> For further informations, visit https://covesa.github.io/capicxx-core-tools/.

First, move to one of project directory. Here, we'll move into Hello World project foler.

```bash
cd Proj_HelloWorldExample/
../cgen/commonapi_core_generator/commonapi-core-generator-linux-x86_64 -d src-gen/core -sk ./fidl/HelloWorld.fidl
../cgen/commonapi_someip_generator/commonapi-someip-generator-linux-x86 -d src-gen/someip ./fidl/HelloWorld.fdepl
```

Select the code generator properly according to your system.

## Configuration
TBA
<!-- Configuration files for server and client application are at `configs` folder under each project directory.

You need to match `"unicast"` address with the address of your machine before running the applications. -->

## Build

Make sure you are on the **project root** directory.
```bash
cmake -Bbuild -DCMAKE_PREFIX_PATH=$(realpath ../install_folder) -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON .
cmake --build build
```

## Run

- Run Server
```bash
COMMONAPI_CONFIG=commonapi4someip.ini LD_LIBRARY_PATH=../install_folder/lib:$PWD/build/ build/HelloWorldService
```

- Run Client
```bash
COMMONAPI_CONFIG=commonapi4someip.ini LD_LIBRARY_PATH=../install_folder/lib:$PWD/build/  build/HelloWorldClient
```
