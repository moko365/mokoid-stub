
#include <mokoid/led.h>

int led_device_open(const struct hw_module_t* module, const char* id,
            struct hw_device_t** device) 
{
}

struct hw_module_methods_t led_module_methods  {
	open: led_device_open
};

struct led_module_t HAL_MODULE_INFO_SYM = {
    common: {
	tag: HARDWARE_MODULE_TAG,
	version_major: 1,
      	version_minor: 0,
	id: "led",
	name: "LED Stub",
	author: "Jollen chen",
    	methods: &led_module_methods,
    }
};
