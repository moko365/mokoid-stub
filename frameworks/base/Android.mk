LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# the library
LOCAL_SRC_FILES := \
            $(call all-subdir-java-files)
LOCAL_MODULE_TAGS := eng
LOCAL_MODULE := mokoid

# AIDL
LOCAL_SRC_FILES += \
	core/java/mokoid/hardware/ILedService.aidl

include $(BUILD_JAVA_LIBRARY)


# The JNI component
include $(CLEAR_VARS)
include $(call all-makefiles-under,$(LOCAL_PATH))
