#!/bin/bash

# Hulk Kernel Build Script
#
# Don't use this File without Permissions of Developers below.
# You can use it if you give the right Credits at the bottom of this File.
# To do this type Credits: and below the name of the Developers of this Script.
#
# Copyright (C) 2013 - 2015 Hybridmax (hybridmax95@gmail.com)
# Copyright (C) 2010 - 2015 thehacker911 (maikdiebenkorn@gmail.com)
# Copyright (C) 2014 - 2015 Tkkg1994 (grifo.luca1995@gmail.com)
#

# Build Information & Path
BUILD_USER="$USER"
DATE="`date +"%d-%m-%Y"`"
TIME="`date +"%T"`"
KERNEL_DIR=$PWD
KERNEL_NAME=Hulk-Kernel
OUTPUT=$KERNEL_DIR/output_hulk_$DATE
MODULES=$OUTPUT/modules
ZIMAGE=arch/arm/boot/zImage
TOOLCHAIN=/home/walter79/Android/toolchains/arm-cortex_a15-linux-gnueabihf-linaro_4.9.3-2015.03/bin/arm-eabi-
BUILD_JOB_NUMBER=`grep processor /proc/cpuinfo|wc -l`

# Colors
COLOR_BLACK="\033[0;30m"
COLOR_RED="\033[0;31m"
COLOR_GREEN="\033[1;32m"
COLOR_YELLOW="\033[1;33m"
COLOR_BLUE="\033[1;34m"
COLOR_PURPLE="\033[1;35m"
COLOR_CYAN="\033[1;36m"
COLOR_NEUTRAL="\033[0m"

# Fonts
BOLD=`tput bold`
NORMAL=`tput sgr0`

# DEFCONFIG Files
USER_DEFCONFIG="jf_defconfig"
VARIANT_DEFCONFIG="jactive_eur_defconfig"
SELINUX_DEFCONFIG="selinux_defconfig"

{
        echo -e $COLOR_RED$BOLD"=================================================="$COLOR_NEUTRAL
        echo -e $COLOR_RED$BOLD"$BUILD_USER is starting to Build $KERNEL_NAME"$COLOR_NEUTRAL
        echo -e $COLOR_RED$BOLD"CPU CORES= $BUILD_JOB_NUMBER"$COLOR_NEUTRAL
        echo -e $COLOR_RED$BOLD"STARTING BUILD on $DATE at $TIME"$COLOR_NEUTRAL
        echo -e $COLOR_RED$BOLD"=================================================="$COLOR_NEUTRAL
        sleep 3
        echo
        echo
        echo -e $COLOR_RED$BOLD"=================================================="$COLOR_NEUTRAL
	echo -e $COLOR_RED$BOLD"Cleaning Source before Building...    "$COLOR_NEUTRAL
        echo -e $COLOR_RED$BOLD"=================================================="$COLOR_NEUTRAL
        echo
        sleep 1

        rm -r $KERNEL_DIR/output_hulk_*
	make mrproper
        export USE_SEC_FIPS_MODE=true
        export CROSS_COMPILE=$TOOLCHAIN
	make VARIANT_DEFCONFIG=$VARIANT_DEFCONFIG $USER_DEFCONFIG SELINUX_DEFCONFIG=$SELINUX_DEFCONFIG
        export KCONFIG_NOTIMESTAMP=true
        export ARCH=arm
        make -j$BUILD_JOB_NUMBER

        
        if [ -f $ZIMAGE ];
        then
            echo -e $COLOR_RED$BOLD"$BUILD_USER your Build was successfull!"$COLOR_NEUTRAL
            echo
        else
            echo -e $COLOR_RED$BOLD"$BUILD_USER your Build is failed!"$COLOR_NEUTRAL
            echo
        fi

        echo -e $COLOR_RED$BOLD"Copying zImage and Modules to Output folder"$COLOR_NEUTRAL

        mkdir $OUTPUT

        mkdir $MODULES

        cp -r $ZIMAGE $OUTPUT

        find . -name "*.ko" -exec cp -r {} $MODULES/ \;
}

