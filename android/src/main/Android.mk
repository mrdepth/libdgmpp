LOCAL_PATH := $(call my-dir)/../../..

include $(CLEAR_VARS)

LOCAL_MODULE := dgmpp
LOCAL_CPP_EXTENSION := .cxx .cpp .cc .hpp

LOCAL_CPP_FEATURES := exceptions rtti

LOCAL_CPPFLAGS := -fpermissive -DNDEBUG
LOCAL_LDLIBS += -latomic

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/src \
$(LOCAL_PATH)/src/SDE \

LOCAL_SRC_FILES := \
$(wildcard $(LOCAL_PATH)/src/*.cpp) \
java-wrapper/jni/dgmpp_wrap.cxx \


include $(BUILD_SHARED_LIBRARY)
