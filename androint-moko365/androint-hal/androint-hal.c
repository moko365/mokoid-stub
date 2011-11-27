/**
 * "androint-hal.c"
 *
 * Description:
 *   AndroInt HAL driver
 *
 * Copyright (C) 2011- by William W.-Y. Liang
 *
 * Date: $Date: 2011-09-09 09:48:41 $
 * Version: $Revision: 1.1.1.1 $
 *
 * History:
 *
 * $Log: androint-hal.c,v $
 * Revision 1.1.1.1  2011-09-09 09:48:41  wyliang
 * initial import of androint_hal into CVS
 *
 *
 */


#include <android/log.h>
#include <fcntl.h>
#include "androint.h"

/******************************************************************************/

char const*const ADDER_FILE = "/dev/androint";

static int add_androint(struct androint_device_t* dev, int a, int b)
{
    int fd;
    int in[2], out;
    int err = 0;

    in[0] = a;
    in[1] = b;

    fd = open(ADDER_FILE, O_RDWR);
    write(fd, in, sizeof(in));
    read(fd, &out, sizeof(out));
    close(fd);

    return out;
}

static int close_androint(struct androint_device_t *dev)
{
    if (dev) free(dev);
    return 0;
}


static int open_androint(const struct hw_module_t* module, char const* name,
        struct hw_device_t** device)
{
    struct androint_device_t *dev = malloc(sizeof(struct androint_device_t));

    memset(dev, 0, sizeof(*dev));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t*)module;
    dev->common.close = (int (*)(struct hw_device_t*))close_androint;
    dev->add = add_androint;

    *device = (struct hw_device_t*)dev;

    return 0;
}


static struct hw_module_methods_t androint_module_methods = {
    .open = open_androint,
};

const struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = ANDROINT_HARDWARE_MODULE_ID,
    .name = "The AndroInt Adder Module",
    .author = "William W.-Y. Liang",
    .methods = &androint_module_methods,
};
