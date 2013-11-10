#define LOG_TAG "MokoidPlatform"
#include "utils/Log.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <jni.h>
#include <mokoid/led.h>

struct led_control_device_t *sLedDevice = NULL;

static jboolean
mokoid_init(JNIEnv *env, jclass clazz)
{
    led_module_t* module;

    LOGI("LedService JNI: mokoid_init() is invoked.");

    if (hw_get_module(LED_HARDWARE_MODULE_ID, (const hw_module_t**)&module) == 0) {
        LOGI("LedService JNI: LED Stub found.");
        if (led_control_open(&module->common, &sLedDevice) == 0) {
    	    LOGI("LedService JNI: Got Stub operations.");
            return 0;
        }
    }

    LOGE("LedService JNI: Get Stub operations failed.");
    return -1;
}

static jboolean mokoid_setDeviceName(JNIEnv* env, jobject thiz, jstring name)
{
    const char *buf;

    if (sLedDevice == NULL) {
        LOGI("LedService JNI: sLedDevice was not fetched correctly.");
        return -1;
    } else {
        return 0;
    }
    return 0;
}

static jboolean mokoid_setOn(JNIEnv* env, jobject thiz, jint led)
{
    LOGI("LedService JNI: mokoid_setOn() is invoked.");

    if (sLedDevice == NULL) {
        LOGI("LedService JNI: sLedDevice was not fetched correctly.");
        return -1;
    } else {
        return sLedDevice->set_on(sLedDevice, led);
    }

    return 0;
}

static jboolean mokoid_setOff(JNIEnv* env, jobject thiz, jint led)
{
    LOGI("LedService JNI: mokoid_setOff() is invoked.");

    if (sLedDevice == NULL) {
        LOGI("LedService JNI: sLedDevice was not fetched correctly.");
        return -1;
    } else {
        return sLedDevice->set_off(sLedDevice, led);
    }

    return 0;
}

static const JNINativeMethod gMethods[] = {
    {"_init",	  	"()Z",
			(void*)mokoid_init},
    { "_set_on",          "(I)Z",
                        (void*)mokoid_setOn },//    { "_set_on",          "(IF)Z",
                                               //(void*)mokoid_setOn },
    { "_set_off",          "(I)Z",
                        (void*)mokoid_setOff },
    { "_set_device_name",          "(Ljava/lang/String;)Z",
                        (void*)mokoid_setDeviceName },
};

int registerMethods(JNIEnv* env) {
    static const char* const kClassName =
        "com/mokoid/server/LedService";
    jclass clazz;

    /* look up the class */
    clazz = env->FindClass(kClassName);
    if (clazz == NULL) {
        LOGE("Can't find class %s\n", kClassName);
        return -1;
    }

    /* register all the methods */
    if (env->RegisterNatives(clazz, gMethods,
            sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK)
    {
        LOGE("Failed registering methods for %s\n", kClassName);
        return -1;
    }

    /* fill out the rest of the ID cache */
    return 0;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("ERROR: GetEnv failed\n");
	goto bail;
    }
    assert(env != NULL);

    registerMethods(env);

    /* success -- return valid version number */
    result = JNI_VERSION_1_4;

bail:
    return result;
}
