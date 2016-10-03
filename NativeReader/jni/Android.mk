LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NativeReader
LOCAL_SRC_FILES := NativeReader.cpp
# for logging
LOCAL_LDLIBS    += -llog
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := NativeRenderer
LOCAL_SRC_FILES := NativeRenderer.cpp
# for logging
LOCAL_LDLIBS    += -llog
include $(BUILD_SHARED_LIBRARY)
