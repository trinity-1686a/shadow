#!/bin/bash

## This script downloads OpenSSL and Libevent2, build them, and installs them
## to ~/.shadow. This must be done to use the Scallion plugin, since we need
## to pass special flags so that linking to Tor and running in Shadow both
## work properly.

D=`pwd`
mkdir -p build
cd build

wget http://www.openssl.org/source/openssl-1.0.1.tar.gz
tar xvzf openssl-1.0.1.tar.gz
cd openssl-1.0.1/

## use ONE of the following:

## for debugging and profiling (you probably want to enable -g and -pg independently)
#./config --prefix=${HOME}/.shadow no-shared threads -fPIC -g -pg -DPURIFY -Bsymbolic

## for normal use
./config --prefix=${HOME}/.shadow no-shared threads -fPIC

make
make install

cd ../

wget https://github.com/downloads/libevent/libevent/libevent-2.0.18-stable.tar.gz
tar xvzf libevent-2.0.18-stable.tar.gz
cd libevent-2.0.18-stable/

## use ONE of the following:

## for debugging and profiling (you probably want to enable -g and -pg independently)
#./configure --prefix=${HOME}/.shadow --enable-shared=no CFLAGS="-fPIC -I${HOME}/.shadow -g -pg" LDFLAGS="-L${HOME}/.shadow" CPPFLAGS="-DUSE_DEBUG"

## for normal use
./configure --prefix=${HOME}/.shadow --enable-shared=no CFLAGS="-fPIC -I${HOME}/.shadow" LDFLAGS="-L${HOME}/.shadow"

make
make install

cd ${D}

