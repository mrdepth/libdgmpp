mkdir -p java/com/dgmpp/jdgmpp
mkdir -p java/jni
mkdir -p java/jni/ThirdParty

swig -c++ -java -package com.dgmpp.jdgmpp -outdir java/com/dgmpp/jdgmpp -o java/jni/dgmpp_wrap.cxx dgmpp.i
cp ../dgmpp/*.cpp java/jni/
cp ../dgmpp/*.h java/jni/
cp ../dgmpp/ThirdParty/*.* java/jni/ThirdParty

cp Android.mk java/jni/Android.mk
cp Application.mk java/jni/Application.mk

/Users/shimanski/Downloads/android-ndk-r10e/ndk-build -C java/jni