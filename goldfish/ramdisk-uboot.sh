mkimage -A arm -O linux -T ramdisk -C none -a 0x50800000 -n "ramdisk" -d ramdisk.img ramdisk-uboot.img
