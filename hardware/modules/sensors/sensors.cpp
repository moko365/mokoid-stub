/*
 * Copyright 2008, The Android Open Source Project
 *
 *	r.yang@samsung.com		2009.3.11
 *
 */


#define LOG_TAG "sensors"

#include <hardware/hardware.h>
#include <hardware/sensors.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <utils/Log.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <stdlib.h>


extern "C" {
/*****************************************************************************/

struct sensors_context_t {
    	struct sensors_control_device_t con_device;
	struct sensors_data_device_t data_device;
	
    /* our private state goes below here */
};

static int s_timeout = 0;//add by hui


static int sensors_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device);
int to_get_sensors_list(struct sensors_module_t* module, struct sensor_t const**sensors_list);

static struct hw_module_methods_t sensors_module_methods = {
    open: sensors_device_open
};

struct sensors_module_t  HAL_MODULE_INFO_SYM = {
    common: {
        tag: HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 0,
        id: SENSORS_HARDWARE_MODULE_ID,
        name: "G-sensors module",
        author: "The Android Open Source Project",
        methods: &sensors_module_methods,
    },
	
    get_sensors_list: to_get_sensors_list
};


//#define 	sensors_fd	"/sys/class/i2c-adapter/i2c-0/0-001d/xyz"
#define 	sensors_fd	"/dev/lis302dl"	//add by hui

#define 	ZERO_G_OFFSET		2048
#define 	SENSITIVITY			512

#define ST_SENSITIVITY 		0.018

static int sInputFD = -1;	//for struct sensors_data_device_t

/*
static int open_data_source(struct sensors_control_device_t *dev)
{	
    int fd;	LOGD("(struct sensors_control_device_t) --> open_data_source \n");	
    fd = open("/sys/class/i2c-adapter/i2c-0/0-001d/xyz", O_RDWR);	
    if(fd < 0)	
    {		
        LOGD("open sensors_fd failed.\n");		
        return -1;	
    }	
    return fd;
}
*/

static native_handle_t* open_data_source(struct sensors_control_device_t *dev)
{
	int fd; 
	LOGD("(struct sensors_control_device_t) --> open_data_source \n");

    fd = open(sensors_fd, O_RDONLY);
	if(fd < 0)
	{
		LOGD("open sensors_fd failed.\n");
		return NULL;
	} 
	
    LOGD("open_data_source:	sInputFD = %d\n",fd);	
	
    native_handle_t* handle = native_handle_create(1, 0);
    handle->data[0] = fd;
    return handle;
}



static int activate(struct sensors_control_device_t *dev, int handle, int enabled)
{
	LOGD("(struct sensors_control_device_t) --> activate \n");

	return 0;
}


static int set_delay(struct sensors_control_device_t *dev, int32_t ms)
{
	LOGD("(struct sensors_control_device_t) --> set_delay \n");

    s_timeout = ms*1000 ;

	return 0;
}


static int wake(struct sensors_control_device_t *dev)
{
	LOGD("(struct sensors_control_device_t) --> wake \n");

	return 0;
}


/*
static int data_open(struct sensors_data_device_t *dev, int fd)
{	
    LOGD("(struct sensors_data_device_t) --> data_open \n");	
    sInputFD = dup(fd);	
    LOGD("sensors_data_device_t: fd = %d\n", sInputFD);	
    return 0;
}
*/

static int data_open(struct sensors_data_device_t *dev, native_handle_t* handle)
{
	LOGD("(struct sensors_data_device_t) --> data_open \n");

	sInputFD = dup(handle->data[0]);
    LOGD("data_open:	handle->data[0] = %d\n",handle->data[0]);		
    LOGD("data_open:	sInputFD = %d\n",sInputFD);	
	
    native_handle_close(handle);
    native_handle_delete(handle);
 	return 0;
}

static int data_close(struct sensors_data_device_t *dev)
{
	LOGD("(struct sensors_data_device_t) --> data_close \n");

	close(sInputFD);
	//close(sBufferFD);	
	return 0;
}


static int data_poll(struct sensors_data_device_t *dev, sensors_data_t* data)
{
#if 1
    struct pollfd pfd;//add by hui
    int ret;//add by hui

	signed char X_value, Y_value, Z_value;

	//LOGD("(struct sensors_data_device_t) --> data_poll \n");

	char buff[4];
	
    //LOGD("data_poll:	sInputFD = %d\n",sInputFD);	

	pfd.fd = sInputFD ;
	pfd.events = POLLIN ;
	ret = poll (&pfd, 1, -1);

//	LOGD("data_poll: poll = %d\n",ret);

	if (ret < 0)
		return ret;
	if (ret == 0)
		return -EWOULDBLOCK;
	
	usleep(s_timeout);
		
//	lseek(sInputFD,0,SEEK_SET);
	memset(buff,0,sizeof(buff));
	
	int length = read(sInputFD, buff, 3);
	
//	LOGD("data_poll:	xyz length = %d\n",length);
//	LOGD("data_poll:	MSB_X_axis = 0x%x, LSB_X_axis = 0x%x, MSB_Y_axis = 0x%x, LSB_Y_axis = 0x%x\n", buff[0], buff[1], buff[2], buff[3]);
//	LOGD("data_poll:	X_value = %d, Y_value = %d, Z_value = %d\n", buff[0], buff[1], buff[2]);
	LOGD("data_poll:	X_value = %02x, Y_value = %02x, Z_value = %02x\n", buff[0], buff[1], buff[2]);


	X_value = (signed char)buff[0];
	Y_value = (signed char)buff[1];
	Z_value = (signed char)buff[2];
	

//?计算公式 SENSITIVITY 256  

	//data->vector.v[0] = (float)(X_value-ZERO_G_OFFSET)/SENSITIVITY*GRAVITY_EARTH;
	//data->vector.v[1] = (float)(Y_value-ZERO_G_OFFSET)/SENSITIVITY*GRAVITY_EARTH;
	//data->vector.v[2] = (float)(Y_value-ZERO_G_OFFSET)/SENSITIVITY*GRAVITY_EARTH;
	
//	data->vector.v[0] = (float)X_value * ST_SENSITIVITY * GRAVITY_EARTH;
//	data->vector.v[1] = (float)Y_value * ST_SENSITIVITY * GRAVITY_EARTH;
//	data->vector.v[2] = (float)Z_value * ST_SENSITIVITY * GRAVITY_EARTH;

	data->vector.v[0] = (float)Y_value * ST_SENSITIVITY * GRAVITY_EARTH * (-1);
	data->vector.v[1] = (float)X_value * ST_SENSITIVITY * GRAVITY_EARTH * (-1);
	data->vector.v[2] = (float)Z_value * ST_SENSITIVITY * GRAVITY_EARTH * (-1);

	//data->vector.v[0] = 0x01;
	//data->vector.v[1] = 0xfd;
	//data->vector.v[2] = 0x02;
	
//	LOGD("test by mohuasong!\n");
//	LOGD("X_value = %d, Y_value = %d, Z_value = %d.\n", X_value, Y_value, Z_value);
//	LOGD("X_axis = %f, Y_axis = %f, Z_axis = %f.\n", data->vector.v[0], data->vector.v[1], data->vector.v[2]);
//	LOGD(">>>>Data_poll:		X_axis = %f, 	Y_axis = %f,     Z_axis = %f\n", data->vector.v[0], data->vector.v[1],data->vector.v[2]);

#endif

	return 0;
//	return SENSOR_TYPE_ACCELEROMETER;
}


static int sensors_device_close(struct hw_device_t * dev)
{
   
 struct sensors_context_t* ctx = (struct sensors_context_t*)dev;
    if (ctx) 
    {
        /* free all resources associated with this device here */
        free(ctx);
    }

    return 0;
}


static int sensors_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device)
{
   
 int status = -EINVAL;

    
	struct sensors_context_t *dev;
    	dev = (sensors_context_t*)malloc(sizeof(*dev));
    
	/* initialize our state here */
    	memset(dev, 0, sizeof(*dev));
		 
  	if (!strcmp(name, SENSORS_HARDWARE_CONTROL))
	{
 	LOGD("struct sensors_control_device_t initialize.\n");

	/* initialize the procs */
     
	dev->con_device.common.tag = HARDWARE_DEVICE_TAG;
	dev->con_device.common.version = 0;     
       dev->con_device.common.module = const_cast<hw_module_t*>(module);     
       dev->con_device.common.close = sensors_device_close;
	dev->con_device.open_data_source = open_data_source;
	dev->con_device.activate = activate;
	dev->con_device.set_delay = set_delay;
	dev->con_device.wake = wake;
 
   	*device = &dev->con_device.common;
     
   	status = 0;
    	}else{
	 LOGD("struct sensors_control_device_t initialize.\n");
    
	/* initialize the procs */
     
      dev->data_device.common.tag = HARDWARE_DEVICE_TAG;     
      dev->data_device.common.version = 0;     
      dev->data_device.common.module = const_cast<hw_module_t*>(module);     
      dev->data_device.common.close = sensors_device_close;
      dev->data_device.data_open = data_open;
      dev->data_device.data_close = data_close;
      dev->data_device.poll = data_poll;


     *device = &dev->data_device.common;
     
      status = 0;
	}
	return status;
}


int to_get_sensors_list(struct sensors_module_t* module, struct sensor_t const** sensors_list)
{
	LOGD("In to_get_sensors_list.");

	struct sensor_t * lsensors;
	
	lsensors = (sensor_t*)malloc(sizeof(*lsensors));
	memset(lsensors, 0, sizeof(*lsensors));

	//这里是设置传感器的一些参数的	
	lsensors->name = "g-sensors";
	lsensors->vendor = "meizu";
	lsensors->version = 0;
	lsensors->handle = NULL;
	lsensors->type = SENSOR_TYPE_ACCELEROMETER;  //传感器类型
	lsensors->power = 1;
	lsensors->maxRange = 2*GRAVITY_EARTH;   //最大量程
	lsensors->resolution = 0.001*GRAVITY_EARTH;
	

	*sensors_list = lsensors;

	return SENSOR_TYPE_ACCELEROMETER;
}

}//endof extern C


