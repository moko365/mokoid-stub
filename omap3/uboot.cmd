mmcinit
fatload mmc 0:1 0x81600000 ubi.img 


bootargs console=ttyS2,115200n8 ubi.mtd=4 root=ubi0:rootfs rootfstype=ubifs video=omapfb:mode:4.3inch_LCD nohz=off

console=ttyS2,115200n8 root=/dev/ram0 rw rootfstype=ext2 initrd=0x81600000,64M video=omapfb:mode:4.3inch_LCD ramdisk=64000 init=/init

setenv bootargs console=ttyS2,115200n8 root=/dev/nfs rw nfsroot=192.168.1.5:/data/target ip=192.168.1.1::255.255.255.0 nolock,rsize=1024,wsize=1024 rootdelay=2 video=omapfb:mode:1280x720@50 init=/init 

1. Install
$ sudo apt-get install nfs-common
$ sudo apt-get install nfs-kernel-server

2. /etc/exports
$ sudo vi /etc/exports
/mnt/iso *(ro,sync)

3. Start nfs server
$ sudo /etc/init.d/nfs-kernel-server start
$ showmount -e localhost
Export list for localhost:
/mnt/iso *











# error
init: Unable to open persistent property directory /data/property errno: 2 

# mount -o remount rw /                                                                                         
# mount                                                                                                         
rootfs / rootfs rw 0 0                                                                                          
/dev/root / ext2 rw 0 0                                                                                         
tmpfs /dev tmpfs rw,mode=755 0 0                                                                                
devpts /dev/pts devpts rw,mode=600 0 0                                                                          
proc /proc proc rw 0 0                                                                                          
sysfs /sys sysfs rw 0 0                                                                                         
tmpfs /sqlite_stmt_journals tmpfs rw,size=4096k 0 0   




mount -t proc /proc /proc
mount -t sysfs /sys /sys



* update init.rc : /data/property error = -2 is solved.


# export PATH=$PATH:/system/bin:/system/sbin:/system/xbin
# mount                                                                                                         
could not open /proc/mounts                                                                                     
# mount -t proc /proc /proc                                                                                     
# mount                                                                                                         
rootfs / rootfs rw 0 0                                                                                          
/dev/root / ext2 rw 0 0                                                                                  
/proc /proc proc rw 0 0       





D/dalvikvm(  820): VM cleaning up                                                  
D/dalvikvm(  820): LinearAlloc 0x0 used 4100 of 4194304 (0%)                       
W/dalvikvm(  820): JNI_CreateJavaVM failed                                         
E/AndroidRuntime(  820): JNI_CreateJavaVM failed                                   
D/AndroidRuntime(  821):                                                           
D/AndroidRuntime(  821): >>>>>>>>>>>>>> AndroidRuntime START <<<<<<<<<<<<<<        
D/AndroidRuntime(  821): CheckJNI is ON                                            
D/dalvikvm(  821): DexOpt: incorrect opt magic number (0xff ff ff ff)              
D/dalvikvm(  821): Stale deps in cache file; removing and retrying                 
W/dalvikvm(  821): partial write in inflate (16344 vs 32768)                       
E/dalvikvm(  821): Unable to extract+optimize DEX from '/system/framework/android.p
olicy.jar'                                                                         
D/dalvikvm(  821): Failed on '/system/framework/android.policy.jar' (boot=1) 


-->solution

echo "dalvik.vm.dexopt-data-only=1" >> /system/build.sapphire.prop




compile bootloader (u-boot);

android@mokoid-lab:~/omap3/u-boot-omap3_moko365 $ vi arch/arm/config.mk 
android@mokoid-lab:~/omap3/u-boot-omap3_moko365 $ make devkit8000_config
sConfiguring for devkit8000 board...
android@mokoid-lab:~/omap3/u-boot-omap3_moko365 $ make


