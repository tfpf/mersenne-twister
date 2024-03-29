#! /usr/bin/env sh

if [ "$0" = sh ]
then
    target=/tmp/mersenne-twister-$(date +%s)
    git clone https://github.com/tfpf/mersenne-twister.git $target
    cd $target
fi
case $(uname 2>/dev/null) in
    MINGW* | MSYS*) make --jobs=4 "$@" install;;
    Linux | Darwin) sudo make --jobs=4 "$@" install;;
esac
