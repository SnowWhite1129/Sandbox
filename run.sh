#!/bin/bash
make
g++ test.cpp -o sandbox
LD_PRELOAD=./sandbox.so ./sandbox
