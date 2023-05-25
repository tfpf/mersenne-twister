#! /usr/bin/env sh

set -e

target=$(realpath $(dirname $0))
for item in $target/*
do
    [ ! -d $item ] && continue
    cd $item
    [ -f Makefile ] && make -s
    (
        ./tests || printf "All $(basename $item) tests did not pass!\n" >&2
    ) &
done
wait
