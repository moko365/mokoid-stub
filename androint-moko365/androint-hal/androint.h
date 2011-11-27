/**
 * "androint.h"
 *
 * Description:
 *   HAL Device type definition file
 *
 * Copyright (C) 2011- by William W.-Y. Liang 
 *
 * Date: $Date: 2011-09-09 09:48:41 $
 * Version: $Revision: 1.1.1.1 $
 *
 * History:
 *
 * $Log: androint.h,v $
 * Revision 1.1.1.1  2011-09-09 09:48:41  wyliang
 * initial import of androint_hal into CVS
 *
 *
 */

#define ANDROINT_HARDWARE_MODULE_ID	"androint"
#define ANDROINT_ID			"androint"

struct androint_device_t {
    struct hw_device_t common;

    int (*add)(struct androint_device_t* dev, int a, int b);
};
