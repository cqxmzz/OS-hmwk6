About
-----

---

This document will walk you through test processes step-by-step.

Written by team1 :family: with :heart:.

Test Steps
----------

---

### 1. Compile and Boot Device

Compile

```
w4118@w4118:~/hmwk6-prog/flo-kernel$ make ARCH=arm flo_defconfig
w4118@w4118:~/hmwk6-prog/flo-kernel$ make ARCH=arm CROSS_COMPILE=arm-eabi-
```

In our repository's utils directory, run update-kernel-ram.sh

To enter fastboot mode, run: `adb reboot bootloader`

```
w4118@w4118:~/hmwk6-prog/utils$ ./update-kernel-ram.sh ../flo-kernel/arch/arm/boot/zImage
```

### 2. Copy File System

`It is supposed that the FS has been created, if not, please refer additional STEP 0.1`

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
w4118@w4118:~/hmwk6-prog$ ./loop.sh
```

`If we do not have hmwk6 directory we need below additional step to create one`

```
w4118@w4118:~/hmwk6-prog$ adb shell mkdir /data/misc/hmwk6
```

Now we can mount the fs

```
w4118@w4118:~/hmwk6-prog$ adb shell
root@flo:/ # mount -o loop -t ext3 /data/misc/hmwk6.fs /data/misc/hmwk6
```

### 6. Launch the GPSLocator

Simply tap the GPSLocator icon in the Nexus 7, that's it.

### 7. Start the GPS Daemon

```
root@flo:/data/misc/ # ./gpsd
```

### 8. Run Tests

`It is supposed that there already are some files and directories in out FS, if not, please refer additional STEP 0.2`

Use file_loc to test

```
root@flo:/data/misc/ # ./file_loc /data/misc/hmwk6/dir
root@flo:/data/misc/ # ./file_loc /data/misc/hmwk6/dir/file1
root@flo:/data/misc/ # ./file_loc /data/misc/hmwk6/dir/file2
```

Results
-------

---

| File/Dir  | Raw Output                                                                                                                    | Google Map URL                                        |
|:----------|:------------------------------------------------------------------------------------------------------------------------------|:------------------------------------------------------|
| dir       | File: /data/misc/hmwk6/dir <br/> Latitude: 40.806275 <br/> Longitude: -73.963655 <br/> Accuracy: 38.751999 <br/> Age: 0       | https://www.google.com/maps/@40.806275,-73.963655,13z |
| dir/file1 | File: /data/misc/hmwk6/dir/file1 <br/> Latitude: 40.806263 <br/> Longitude: -73.963654 <br/> Accuracy: 37.738998 <br/> Age: 1 | https://www.google.com/maps/@40.806263,-73.963654,13z |
| dir/file2 | File: /data/misc/hmwk6/dir/file2 <br/> Latitude: 40.806263 <br/> Longitude: -73.963654 <br/> Accuracy: 37.738998 <br/> Age: 1 | https://www.google.com/maps/@40.806263,-73.963654,13z |

Additional Steps
----------------

---

### 0.1 Create File System

If it is the first time testing, we need to create a new modified ext3 file system

```
w4118@w4118:~/hmwk6-prog$ dd if=/dev/zero of=hmwk6.fs bs=1M count=2
w4118@w4118:~/hmwk6-prog$ sudo losetup /dev/loop0 hmwk6.fs
w4118@w4118:~/hmwk6-prog$ sudo ./userspace/e2fsprogs/misc/mke2fs -I 256 -t ext3 -L w4118.hmwk6 /dev/loop0
w4118@w4118:~/hmwk6-prog$ sudo losetup -d /dev/loop0
```

### 0.2 Create Some Files and Directories in The FS

Create some files

```
w4118@w4118:~/hmwk6-prog$ adb shell
root@flo:/ # cd /data/misc/hmwk6
root@flo:/data/misc/hmwk6/ # mkdir dir
root@flo:/data/misc/hmwk6/dir/ # touch file1
root@flo:/data/misc/hmwk6/dir/ # touch file2
```
