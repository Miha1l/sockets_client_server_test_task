#!/bin/bash

build() {
    CMAKE_DIR=$1
    BUILD_DIR=$2

    cmake -S $CMAKE_DIR -B $BUILD_DIR
    cmake --build $BUILD_DIR
}

if [[ $1 == "client" ]]
then
    build ./client ./client/build
elif [[ $1 == "server" ]]
then
    build ./server ./server/build
else
    build ./client ./client/build
    build ./server ./server/build
fi