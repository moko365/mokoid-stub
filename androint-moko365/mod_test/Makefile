# File: mod_test/Makefile
#
# Description: Android Module Test - Makefile
#
# Copyright (C) 2010- by "William W.-Y. Liang" @ EPS Lab of NTUT.CSIE 
#
# Date: $Date: 2011-07-22 09:40:07 $
# Version: $Revision: 1.1.1.1 $
#
# History:
#
# $Log: Makefile,v $
# Revision 1.1.1.1  2011-07-22 09:40:07  wyliang
# initialization for the kernel module testing program for the AndroInt project
#
#

ifeq ($(KERNELRELEASE),)

KERNELDIR ?= $(ANDROID_DEV)/kernel
PWD       := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) LDDINC=$(PWD) ARCH=arm CROSS_COMPILE=${ANDROID_GCC_PREFIX} EXTRA_CFLAGS=-fno-pic modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions [mM]odule*

else

obj-m	:= mod_test.o

endif
