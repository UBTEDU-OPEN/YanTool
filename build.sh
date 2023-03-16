#!/bin/bash

if [ $# -eq 0 ]; then
    echo "add parameter: -j4 install"
    exit 1
fi

str=$1
if [ ${str:0:2} == '-j' ]; then
    catkin_make -DCMAKE_INSTALL_PREFIX=/opt/yantool/ $*
else
    catkin_make -DCMAKE_INSTALL_PREFIX=/opt/yantool/ -DCATKIN_WHITELIST_PACKAGES=$*
fi
