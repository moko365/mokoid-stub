LOCAL_PATH:= $(call my-dir)

#### build ledserver
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	mokoid_ledserver.cpp 

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libcutils \
	libledservice

LOCAL_C_INCLUDES :=  \
	vendor/mokoid/libledservice

LOCAL_MODULE_TAGS := eng

LOCAL_MODULE:= ledserver

include $(BUILD_EXECUTABLE)
