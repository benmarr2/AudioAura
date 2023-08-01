#!/bin/bash

# usage: ./build.sh [debug|release]

build_type=${1:-debug}

if [[ $build_type == "debug" ]]
then
    cmake_build_type="Debug"
else
    cmake_build_type="Release"
fi

cd build
cmake -DCMAKE_BUILD_TYPE=$cmake_build_type ..

if [[ $build_type == "debug" ]]
then
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=YES ..
    ln -sf compile_commands.json ../compile_commands.json
fi

make

./AudioAura
