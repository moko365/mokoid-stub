LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# the library
LOCAL_SRC_FILES := \
            $(call all-subdir-java-files)
LOCAL_MODULE_TAGS := eng
LOCAL_MODULE := hello

include $(BUILD_JAVA_LIBRARY)
