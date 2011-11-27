/* 
  File: androint_mod_add/androint_module.c
 
  Description: AndroInt Module (ADD) - the source
 
  Copyright (C) 2010- by "William W.-Y. Liang" @ EPS Lab of NTUT.CSIE 
 
  Date: $Date: 2011-07-26 10:54:44 $
  Version: $Revision: 1.2 $
 
  History:
 
  $Log: androint_module.c,v $
  Revision 1.2  2011-07-26 10:54:44  wyliang
  Fix wrong kfree problem; Remove redundant code;

  Revision 1.1.1.1  2010-07-07 05:36:59  wyliang
  initial import into CVS

  Revision 1.3  2010-07-07 04:46:54  wyliang
  Create a branch specifically for ADD operation

  Revision 1.2  2010-06-26 10:54:16  wyliang
  Change log message for read/write file operations

  Revision 1.1.1.1  2010-06-25 15:26:34  wyliang
  initial import into CVS

*/

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
 
#define	DEBUG(...)	printk(KERN_WARNING"AndroInt Driver Module ("__FILE__"): "__VA_ARGS__);

int androint_major = 123;
int androint_minor = 0;

struct androint_dev {
	int data[2];                 
	struct semaphore sem;
	struct cdev cdev;
} androint_device;

int androint_open(struct inode *inode, struct file *filp)
{
	struct androint_dev *device;

	device = container_of(inode->i_cdev, struct androint_dev, cdev);
	filp->private_data = device;

	DEBUG("open done\n");

	return 0;
}

ssize_t androint_access(int access_dir, struct file *filp, char __user *buf, 
		size_t count)
{
	struct androint_dev *device = filp->private_data; 
	int *data = device->data;
	ssize_t retval = 0;

	if (down_interruptible(&device->sem)) return -ERESTARTSYS;

	if (access_dir == 0) {	/* read the sum */

		int sum = data[0] + data[1];
		
		if (count != sizeof(int)) {
			DEBUG("read error: buffer size (%d) is not sizeof(int) (%d)\n", count, sizeof(int));
			goto out;
		}

		retval = copy_to_user(buf, &sum, sizeof(int));

		DEBUG("User reads %d \n", sum);

	} else {		/* write two integers */ 

		if (count != sizeof(int) * 2) {
			DEBUG("write error: buffer size (%d) is not sizeof(int)x2 (%d)\n", count, sizeof(int)*2);
			goto out;
		}

		retval = copy_from_user(data, buf, count);

		DEBUG("User writes %d %d \n", data[0], data[1]);

	}

	if (retval) {
		retval = -EFAULT;
		goto out;
	}

	retval = count;

  out:
	up(&device->sem);
	return retval;
}

ssize_t androint_read(struct file *filp, char __user *buf, size_t count,
                loff_t *f_pos)
{
	DEBUG("androint_read()\n");
	return androint_access(0, filp, buf, count);
}

ssize_t androint_write(struct file *filp, const char __user *buf, size_t count,
                loff_t *f_pos)
{
	DEBUG("androint_write()\n");
	return androint_access(1, filp, (char __user *)buf, count);
}

int androint_release(struct inode *inode, struct file *filp)
{
	DEBUG("release done\n");

	return 0;
}

struct file_operations androint_fops = {
	.owner =    THIS_MODULE,
	.open =     androint_open,
	.read =     androint_read,
	.write =    androint_write,
	.release =  androint_release,
};

void androint_cleanup(void)
{
	dev_t devno = MKDEV(androint_major, androint_minor);

	DEBUG("module exit\n");

	cdev_del(&androint_device.cdev);

	unregister_chrdev_region(devno, 1);

}

int androint_init(void)
{
	int result;
	dev_t devno = MKDEV(androint_major, androint_minor);

	DEBUG("module init starts\n");

	/* register region for the char device */
	result = register_chrdev_region(devno, 1, "androint");
	if (result < 0) {
		DEBUG("can not get a major %d\n", androint_major);
		return result;
	}

	/* prepare the device */
	init_MUTEX(&androint_device.sem);
	// androint_device.data = kmalloc(androint_device_size, GFP_KERNEL);

	/* register the char device */
	cdev_init(&androint_device.cdev, &androint_fops);
	androint_device.cdev.owner = THIS_MODULE;
	result = cdev_add(&androint_device.cdev, devno, 1);
	if (result) {
		DEBUG("fail to add the AndroInt driver (retcode: %d)", result);
		goto fail;  
	}

	DEBUG("module init done\n");

	return 0;

fail:
	androint_cleanup();
	return result;
}

module_init(androint_init);
module_exit(androint_cleanup);
MODULE_LICENSE("GPL");
