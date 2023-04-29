#! /usr/bin/env bash

target=/tmp/mersenne-twister-$(date +%s)
git clone https://github.com/tfpf/mersenne-twister.git $target
cd $target
sudo make install
