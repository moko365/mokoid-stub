# File: mod_test2/Makefile
#
# Description: AndroInt Module - Makefile
#
# Copyright (C) 2010- by "William W.-Y. Liang" @ EPS Lab of NTUT.CSIE 
#
# Date: $Date: 2011-07-20 10:52:16 $
# Version: $Revision: 1.2 $
#
# History:
#
# $Log: Makefile,v $
# Revision 1.2  2011-07-20 10:52:16  wyliang
# fix GCC 4.4.3 problem, specifically for NDK r6
#
# Revision 1.1.1.1  2010-07-07 05:36:59  wyliang
# initial import into CVS
#
# Revision 1.1.1.1  2010-06-25 15:26:34  wyliang
# initial import into CVS
#
#

ifeq ($(KERNELRELEASE),)

KERNELDIR ?= $(ANDROID_DEV)/kernel
PWD       := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) LDDINC=$(PWD) ARCH=arm CROSS_COMPILE=$(ANDROID_GCC_PREFIX) EXTRA_CFLAGS+=-fno-pic modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions [mM]odule*

else

obj-m	:= androint_module.o

endif
