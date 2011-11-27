/* 
  File: mod_test/test.c
 
  Description: Android Module Test - The source
 
  Copyright (C) 2010- by "William W.-Y. Liang" @ EPS Lab of NTUT.CSIE 
 
  Date: $Date: 2011-07-22 09:40:07 $
  Version: $Revision: 1.1.1.1 $
 
  History:
 
  $Log: mod_test.c,v $
  Revision 1.1.1.1  2011-07-22 09:40:07  wyliang
  initialization for the kernel module testing program for the AndroInt project

*/
 
#include <linux/module.h>
#include <linux/kernel.h>	/* printk() */

int test_init(void)
{
	printk("<1>Hello Test Module!!\n");
	return 0;
}

void test_cleanup(void)
{
	printk("<1>Bye Test Module!!\n");
}


module_init(test_init);
module_exit(test_cleanup);
MODULE_LICENSE("GPL");
