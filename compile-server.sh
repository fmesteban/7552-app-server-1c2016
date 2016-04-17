#!/usr/bin/env bash
echo "Setting up rocksdb."
sudo cp ../rocksdb/librocksdb.a AppServer/src/third_party/rocksdb/
sudo cp -R ../rocksdb/include AppServer/src/third_party/rocksdb/


echo "Cleaning and making"
rm -rf AppServer/build/*
cd AppServer/build
cmake ../src/
make
result=$?
cd ../
chmod +rwx -R build
exit $result
