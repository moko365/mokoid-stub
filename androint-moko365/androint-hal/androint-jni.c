/**
 * "androint-jni.c"
 *
 * Description:
 *   AndroInt Native code which links with the HAL driver
 *
 * Copyright (C) 2011- by "William W.-Y. Liang"
 *
 * Date: $Date: 2011-09-09 09:31:22 $
 * Version: $Revision: 1.1.1.1 $
 *
 * History:
 *
 * $Log: androint-jni.c,v $
 * Revision 1.1.1.1  2011-09-09 09:31:22  wyliang
 * initial import of AndroInt-ex8.1-standalone-service-hal into CVS
 *
 *
 */


#include <jni.h>
#include "androint.h"

#define	DEVFILE	"/dev/androint"
#define BUFLEN	128

JNIEXPORT jint JNICALL Java_com_eps_william_androint_app_AndroIntService_addJNI
  (JNIEnv *env, jobject thiz, jint a, jint b)
{
    hw_module_t* module;
    struct androint_device_t* androint_dev;
        
    hw_get_module(ANDROINT_HARDWARE_MODULE_ID, (hw_module_t const**)&module);
    module->methods->open(module, ANDROINT_ID, &androint_dev);
    result = androint_dev->add(androint_dev, a, b);

    return result;
}

