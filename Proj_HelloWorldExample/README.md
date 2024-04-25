# HelloWorldExample

## Build
```bash
mkdir build
cd build
cmake ..
make
```

## Configuration
Configuration files for server and client application are at `configs` folder under each project directory.

You need to match `"unicast"` address with the address of your machine before running the applications.

## Run

- Run Server
```bash
export LD_LIBRARY_PATH=`pwd`/../../lib:$LD_LIBRARY_PATH VSOMEIP_CONFIGURATION=../configs/config_server.json
./HelloWorldService
```

- Run Client
```bash
export LD_LIBRARY_PATH=`pwd`/../../lib:$LD_LIBRARY_PATH VSOMEIP_CONFIGURATION=../configs/config_client.json
./HelloWorldClient