# CommonAPI vsomeip Example

## Prerequisites

Required Features:
- C/C++ Compiler
- CMake
- Java Runtime Environment
- Boost C++ Library

In Debian/Ubuntu, you can install those features with:  
~~~bash
sudo apt install -y build-essential cmake default-jre libboost-all-dev
~~~

## Clone Repos

~~~bash
git clone https://github.com/lsin07/commonapi-vsomeip-example.git --recurse-submodules
~~~

You need to add `--recurse-submodules` option in order to import all required CommonAPI repositories.  
Or, you can type `git submodule init` and `git submodule update` to get all missing submodules if the repository was cloned without recurse option.

## Build Library
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
./build_lib.sh
~~~

## Code Generation
NOTE: The code generators used in this section are [capicxx-core-tools](https://github.com/COVESA/capicxx-core-tools/) 
and [capicxx-someip-tools](https://github.com/COVESA/capicxx-someip-tools) ver. 3.2.15.  
For further informations, visit https://covesa.github.io/capicxx-core-tools/.

Install code generators:  
(You must have the package `zip` installed on your machine. If not, install it with `sudo apt install zip` before running the script.)
~~~bash
cd cgen/
./get_cgen.sh
~~~

On the **project** directory (Ex. Proj_HelloWorldExample/), run:
```bash
../cgen/commonapi_core_generator/commonapi-core-generator-linux-x86_64 -sk ./fidl/HelloWorld.fidl
../cgen/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64 ./fidl/HelloWorld.fdepl
```
Select the code generator properly according to your system.  
For example, run `commonapi-core-generator-windows-x86_64.exe` instead of `commonapi-core-generator-linux-x86_64` if you're on x86-64 Windows system.

## Configuration
Configuration files for server and client application are at `configs` folder under each project directory.

You need to match `"unicast"` address with the address of your machine before running the applications.

## Build
Make sure you are on the **project root** directory.
```bash
mkdir build
cd build
cmake ..
make
```

## Run

- Run Server
```bash
export LD_LIBRARY_PATH=`pwd`/../../lib:$LD_LIBRARY_PATH VSOMEIP_CONFIGURATION=../configs/config_service.json
./HelloWorldService
```

- Run Client
```bash
export LD_LIBRARY_PATH=`pwd`/../../lib:$LD_LIBRARY_PATH VSOMEIP_CONFIGURATION=../configs/config_client.json
./HelloWorldClient
