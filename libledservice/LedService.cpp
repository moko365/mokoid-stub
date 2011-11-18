/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include <math.h>
#include <sys/types.h>

#include <utils/SortedVector.h>
#include <utils/KeyedVector.h>
#include <utils/threads.h>
#include <utils/Atomic.h>
#include <utils/Errors.h>
#include <utils/RefBase.h>
#include <utils/String16.h>
#include <utils/Binder.h>
#include <utils/IServiceManager.h>

#include <mokoid/led.h>

#include "LedService.h"

namespace android {
// ---------------------------------------------------------------------------

/*
 * Binder proxy object implementation
 */
class BpLedService: public BpInterface<ILedService>
{
public:
    BpLedService(const sp<IBinder>& impl)
        : BpInterface<ILedService>(impl)
    {
    }

    virtual int setOn(int led)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ILedService::getInterfaceDescriptor());
        remote()->transact(BnLedService::LED_ON, data, &reply);
        return 0;
    }

};

IMPLEMENT_META_INTERFACE(LedService, "mokoid.hardware.ILedService");

#define CHECK_INTERFACE(interface, data, reply) \
        do { if (!data.enforceInterface(interface::getInterfaceDescriptor())) { \
            LOGW("Call incorrectly routed to " #interface); \
            return PERMISSION_DENIED; \
        } } while (0)

status_t BnLedService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case CONNECT: {
            CHECK_INTERFACE(ILedService, data, reply);
            return NO_ERROR;
        } break;
	case LED_ON:
	    return NO_ERROR;
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

/****** Implementation *****/

static struct led_control_device_t *sLedDevice = NULL;

LedService::LedService()
{
    led_module_t* module;

    LOGI("ledserver->LedService: trying to get stub object");

    if (hw_get_module(LED_HARDWARE_MODULE_ID, (const hw_module_t**)&module) == 0) {
        LOGI("ledserver->LedService: stub found.");
        if (led_control_open(&module->common, &sLedDevice) == 0) {
            LOGI("ledserver->LedService: ops not found.");
            return;
        }
    }

    LOGE("ledserver->LedService: failed to get LED stub");
    return;
}

LedService::~LedService()
{
}
//Singleton
void LedService::instantiate() {
     defaultServiceManager()->addService(
             String16("mokoid.led"), new LedService());
}

int LedService::setOn(int led)
{
    LOGI("ledserver->LedService::setOn");

    if (sLedDevice == NULL) {
        LOGI("ledserver: sLedDevice was not fetched correctly.");
        return -1;
    } else {
        return sLedDevice->set_on(sLedDevice, led);
    }

    return 0;
}

// ---------------------------------------------------------------------------
}; // namespace android


