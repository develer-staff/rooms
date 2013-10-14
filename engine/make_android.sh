#!/bin/bash

# This simple script takes care of building the engine library
# for Android
#
# If you are using Qt >= 5.2.0 then you don't need this script, 
# you can just type qmake && make in order to compile the library for Android
#
# Edit the variables below to suit your configuration

# Qmake for Android location
QMAKE=/opt/Qt/5.1.1/android_x86/bin/qmake

# Android API version
VERSION=14

# Android SDK location
SDK_LOCATION=/opt/android-sdk-linux

# Android NDK location
NDK_LOCATION=/opt/android-ndk-r9

# Android gcc version
GCC_VERSION=4.6

ANDROID_NDK_PLATFORM=android-$VERSION \
    ANDROID_HOME=$SDK_LOCATION \
    ANDROID_NDK_ROOT=$NDK_LOCATION \
    ANDROID_NDK_TOOLCHAIN_VERSION=$GCC_VERSION \
    $QMAKE -r -spec android-g++ || exit 1

/usr/bin/make
