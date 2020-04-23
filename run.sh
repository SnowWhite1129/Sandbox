#!/bin/bash
make
g++ test.cpp -o sandbox
#LD_PRELOAD=./sandbox.so ./sandbox -- chmod 0644 file
./sandbox -- ls -l
