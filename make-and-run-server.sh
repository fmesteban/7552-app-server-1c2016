#!/usr/bin/env bash
./compile-server.sh $1
compilationResult=$?

if [ $compilationResult -ne 0 ]
then
    exit 1
fi

chmod a+rwx -R AppServer/build && ./AppServer/build/AppServer 8000
