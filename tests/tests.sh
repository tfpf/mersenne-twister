#! /usr/bin/env sh

set -e

target=$(realpath $(dirname $0))

cd $target/C
make -s
./tests

cd $target/C++
make -s
./tests

cd $target/Python
./tests.py

printf "All tests passed!\n"
