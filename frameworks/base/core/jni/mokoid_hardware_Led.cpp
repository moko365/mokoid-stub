#define LOG_TAG "MokoidPlatform"
#include "utils/Log.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <jni.h>

#include <utils/IServiceManager.h>
#include <utils/Log.h>

#include "LedService.h"

using namespace android;

sp<ILedService> mLedService;

const sp<ILedService>& getLedService()
{
    LOGI("getLedService()");

    //TODO need Mutex
    if (mLedService.get() == 0) {
        sp<IServiceManager> sm = defaultServiceManager();
        sp<IBinder> binder;
        do {
            binder = sm->getService(String16("mokoid.led"));
            if (binder != 0)
                break;
            LOGI("LedService not published, waiting...");
            usleep(100000); // 0.1s is better
        } while(true);

        mLedService = interface_cast<ILedService>(binder);
    }
    return mLedService;
}

static jboolean
led_init(JNIEnv *env, jclass clazz)
{
	mLedService = getLedService();
    return -1;
}

static jboolean led_on(JNIEnv* env, jobject thiz, jint led)
{
	mLedService->setOn((int)led);
    return -1;
}

static jboolean led_off(JNIEnv* env, jobject thiz, jint led)
{
    return -1;
}

static const JNINativeMethod gMethods[] = {
    {"_init",	  	"()Z",
			(void*)led_init},
    { "_led_on",          "(I)Z",
                        (void*)led_on },
    { "_led_off",          "(I)Z",
                        (void*)led_off },
};

int registerMethods(JNIEnv* env) {
    static const char* const kClassName =
        "mokoid/hardware/Led";
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
