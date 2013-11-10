/*
 * Copyright (C) 2008 The Android Open Source Project
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

#include <hardware/hardware.h>

#include <fcntl.h>
#include <errno.h>

#include <cutils/log.h>
#include <cutils/atomic.h>

/*****************************************************************************/

struct led_module_t {
   struct hw_module_t common;

   int (*init_led)(struct led_control_device_t *dev);
};

struct led_control_device_t {
   struct hw_device_t common;

   int fd;              /* file descriptor of LED device */

   /* supporting control APIs go here */
   int (*set_on)(struct led_control_device_t *dev, int32_t led);
   int (*set_off)(struct led_control_device_t *dev, int32_t led);
   int (*set_name)(struct led_control_device_t *dev, char *name);
};

/*****************************************************************************/

#define LED_HARDWARE_MODULE_ID "led"

/** helper APIs */
static inline int led_control_open(const struct hw_module_t* module,
        struct led_control_device_t** device) {
    return module->methods->open(module,
            LED_HARDWARE_MODULE_ID, (struct hw_device_t**)device);
}

