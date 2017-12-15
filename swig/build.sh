ROOT=${PROJECT_DIR}/java-wrapper/
rm -rf ${ROOT}
mkdir -p ${ROOT}/jni/
mkdir -p ${ROOT}/com/dgmpp/jdgmpp

swig -c++ -java -package com.dgmpp.jdgmpp -outdir ${ROOT}/com/dgmpp/jdgmpp -o ${ROOT}/jni/dgmpp_wrap.cxx ${PROJECT_DIR}/swig/dgmpp.i
