#! /usr/bin/env sh

if [ "$1" != . ]
then
    target=/tmp/mersenne-twister-$(date +%s)
    git clone https://github.com/tfpf/mersenne-twister.git $target
    cd $target
fi
case $(uname 2>/dev/null) in
    MINGW* | MSYS*) make install;;
    Linux) sudo make install;;
esac
