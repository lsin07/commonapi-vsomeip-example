#!/bin/bash

COMMONAPI_CONFIG=commonapi4someip.ini
LD_LIBRARY_PATH=../install_folder/lib:$PWD/build/

if [ "$1" = "--external" ]; then
    CONFIG=configs/config_client.json
    CURRENT_IP=$(hostname -I | awk '{print $1}')

    if [ -z "$CURRENT_IP" ]; then
        echo "Unable to get IP address."
        exit 1
    fi

    if command -v jq &> /dev/null; then
        jq ".unicast = \"$CURRENT_IP\"" $CONFIG > tmp.json && mv tmp.json $CONFIG
    else
        # if jq is not installed.
        sed -i "s/\"unicast\" : \"[^\"]*\"/\"unicast\" : \"$CURRENT_IP\"/" $CONFIG
    fi

    COMMONAPI_CONFIG=commonapi4someip.ini LD_LIBRARY_PATH=../install_folder/lib:$PWD/build/ VSOMEIP_CONFIGURATION=$CONFIG build/HelloWorldClient
else
    COMMONAPI_CONFIG=commonapi4someip.ini LD_LIBRARY_PATH=../install_folder/lib:$PWD/build/ build/HelloWorldClient
fi
