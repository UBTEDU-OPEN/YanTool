#!/bin/bash

PASSWORD="raspberry"
TARGET_IP=10.10.66.188
TARGET_SOURCE_DIR=/home/pi/User_data/Yantool

if [ ! -d ./temp ]; then
    mkdir temp
fi

git status | grep deleted | awk '{print $2}' | xargs sshpass -p ${PASSWORD} ssh pi@${TARGET_IP} "cd ${TARGET_SOURCE_DIR}; rm "

git status | grep src/ | awk '{print $2}' | xargs sshpass -p ${PASSWORD} ssh pi@${TARGET_IP} "cd ${TARGET_SOURCE_DIR}; sudo rm "
git status | grep src/ | awk '{print $2}' | xargs cp --parent -p -t ./temp

git status | grep "new file" | awk '{print $3}' | xargs cp --parent -p -t ./temp

git status | grep renamed | awk '{print $2}' | xargs sshpass -p ${PASSWORD} ssh pi@${TARGET_IP} "cd ${TARGET_SOURCE_DIR}; rm "
git status | grep renamed | awk '{print $4}' | xargs cp --parent -p -t ./temp

sshpass -p ${PASSWORD} scp -rp ./temp/* pi@${TARGET_IP}:${TARGET_SOURCE_DIR}

rm -r ./temp/
