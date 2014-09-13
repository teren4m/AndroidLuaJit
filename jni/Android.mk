
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := luajit
LOCAL_SRC_FILES := libluajit.a

include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)

# имя модуля, который будет вызываться в Java при помощи System.loadLibrary()
LOCAL_MODULE    := dofile

# Add all source file names to be included in lib separated by a whitespace
LOCAL_SRC_FILES := dofile.c

# статические библиотеки, уже скомпиленные за нас
LOCAL_STATIC_LIBRARIES := cpufeatures 

LOCAL_STATIC_LIBRARIES := luajit

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)

# 
$(call import-module,cpufeatures)
