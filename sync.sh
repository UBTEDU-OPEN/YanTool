#!/bin/bash

PASSWORD="raspberry"
SOURCE_DIR=~/raspi-rootfs/opt/yantool
TARGET_IP=10.10.31.94
TARGET_DIR=/opt/

sudo rsync -avz -e ssh $SOURCE_DIR pi@${TARGET_IP}:${TARGET_DIR}

sudo rsync -avz -e ssh ~/raspi-rootfs/home/pi/Desktop/yantool.desktop  pi@${TARGET_IP}:/home/pi/Desktop/
