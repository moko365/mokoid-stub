ROOTFS := root
ANDROID_OUT := /home/android/mokoid/out/target/product/goldfish

all:

mkfs:
	../tools/mkfs.ubifs -r $(ROOTFS)/ -m 2048 -e 129024 -c 812 -o ubifs.img

ubi:
	../tools/ubinize -o ubi.img -m 2048 -p 128KiB -s 512 ../tools/ubinize.cfg 

ext2: genroot
	genext2fs -D dev.txt -d $(ROOTFS) -b 64000 -i 4096 ext2fs.img

fixroot:
	mkdir -p $(ROOTFS)/system/etc/init.d
	cp inittab $(ROOTFS)/system/etc/
	cp fstab $(ROOTFS)/system/etc/
	cp rcS $(ROOTFS)/system/etc/init.d/
	chmod a+x $(ROOTFS)/system/etc/init.d/rcS

genroot:
	rm -rf root
	cp -a $(ANDROID_OUT)/root ./
	cp -a $(ANDROID_OUT)/system ./root/
