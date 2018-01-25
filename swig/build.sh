ROOT=${PROJECT_DIR}/../java-wrapper/
rm -rf ${ROOT}
mkdir -p ${ROOT}/jni/
mkdir -p ${ROOT}/src/com/dgmpp

swig -c++ -java -package com.dgmpp -I${PROJECT_DIR}/../src/ -outdir ${ROOT}/src/com/dgmpp -o ${ROOT}/jni/dgmpp_wrap.cxx ${PROJECT_DIR}/../swig/dgmpp.i

