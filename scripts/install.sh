#!/bin/bash

if [ $USER != 'root' ]; then
    echo "not root user. please swith to root and try again."
    exit 1
fi

cd ..
./build.sh -j3 install
cd -
cp -af yantool_start.sh /opt/yantool/
cp -af -r images /opt/yantool/
cp -af yantool.desktop /home/pi/Desktop/

echo "install ok."
