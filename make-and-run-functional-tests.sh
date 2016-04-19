#!/usr/bin/env bash
ls -R
./compile-server.sh $1
compilationResult=$?

if [ $compilationResult -ne 0 ]
then
    exit 1
fi

python -m unittest discover -s AppServer/src/functional_tests
