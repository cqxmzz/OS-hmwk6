About
-----

This document will walk you through test process step-by-step.

Written by team1 :family: with :heart:

Test Steps
----------

### 1. Compile and Boot Device

Compile

```
w4118@w4118:~/hmwk6-prog/flo-kernel$ make ARCH=arm flo_defconfig
w4118@w4118:~/hmwk6-prog/flo-kernel$ make ARCH=arm CROSS_COMPILE=arm-eabi-
```

In our repository's utils directory, run update-kernel-ram.sh

```
w4118@w4118:~/hmwk6-prog/utils$ ./update-kernel-ram.sh ../flo-kernel/arch/arm/boot/zImage
```

### 2. Create File System

If it is the first time testing, we need to create a new modified ext3 file system

```
w4118@w4118:~/hmwk6-prog$ dd if=/dev/zero of=hmwk6.fs bs=1M count=2
w4118@w4118:~/hmwk6-prog$ sudo losetup /dev/loop0 hmwk6.fs
w4118@w4118:~/hmwk6-prog$ sudo ./userspace/e2fsprogs/misc/mke2fs -I 256 -t ext3 -L w4118.hmwk6 /dev/loop0
w4118@w4118:~/hmwk6-prog$ sudo losetup -d /dev/loop0
```

After the file system created, copy the fs to our device

```
w4118@w4118:~/hmwk6-prog$ adb push hmwk6.fs /data/misc
```

### 3. Make and Copy GPS Daemon to Our Device

```
w4118@w4118:~/hmwk6-prog/userspace/gpsd$ make
w4118@w4118:~/hmwk6-prog/userspace/gpsd$ adb push gpsd /data/misc
```

### 4. Make and Copy Test Program to Our Device

```
w4118@w4118:~/hmwk6-prog/userspace/file_loc$ make
w4118@w4118:~/hmwk6-prog/userspace/file_loc$ adb push file_loc /data/misc
```

### 5. Mount the File System

First we setup a couple of symlinks, they are packed into one file

```
w4118@w4118:~/hmwk6-prog$ ./slloop.sh
```

If we do not have hmwk6 directory we need below additional step to create one)

```
w4118@w4118:~/hmwk6-prog$ adb shell mkdir /data/misc/hmwk6
```

Now we can mount the fs

```
w4118@w4118:~/hmwk6-prog$ adb push hmwk6.fs /data/misc
w4118@w4118:~/hmwk6-prog$ adb shell
# mount -o loop -t ext3 /data/misc/hmwk6.fs /data/misc/hmwk6
```

### 6. Start the GPS Daemon

```
w4118@w4118:~/hmwk6-prog$ adb shell /data/misc/gpsd
```

### 7. Run Tests

Create some files

```
w4118@w4118:~/hmwk6-prog$ adb shell
# cd /data/misc/hmwk6
# touch file1
# touch file2
# mkdir dir1
```

Use file_loc to test

```
w4118@w4118:~/hmwk6-prog$ adb shell
# cd /data/misc
# ./file_loc /data/misc/hmwk6/file1
# ./file_loc /data/misc/hmwk6/file2
# ./file_loc /data/misc/hmwk6/dir1
```

**Results**

| File/Dir | Raw Output |
|:--------:|:----------:|
|  file1   |   adsda    |
|  file2   |   adsadd   |
