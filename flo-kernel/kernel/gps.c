#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/gps.h>
#include <linux/time.h>
#include <linux/namei.h>
#define R_OK 4

/* Wendan Kang*/
static DEFINE_RWLOCK(k_loc_lock);
static struct gps_kernel k_gps = {
	.location = {
		.latitude = 0.0,
		.longitude = 0.0,
		.accuracy = 0.0
	},
	.timestamp = {
		.tv_sec = 0,
		.tv_nsec = 0
	}

};
/* citation: hmwk3 solution*/
SYSCALL_DEFINE1(set_gps_location, struct gps_location __user *, loc)
{
	struct gps_location k_loc;
	if(current_euid() != 0)
		return -EACCES;
	if(loc == NULL)
		return -EINVAL;
	if(copy_from_user(&k_loc, loc, sizeof(k_loc)))
		return -EFAULT;
	write_lock(&k_loc_lock);
	memcpy(&k_gps.location, &k_loc, sizeof(k_loc));
	k_gps.timestamp = CURRENT_TIME;
	write_unlock(&k_loc_lock);
	return 0;
}

static int get_file_gps_location(const char *kfile, struct gps_location *kloc)
{
	int ret;
	struct inode *inode;
	struct path kpath = { .mnt = NULL, .dentry = NULL} ;

	if (kern_path(kfile, LOOKUP_FOLLOW | LOOKUP_AUTOMOUNT, &kpath) != 0)
		return -EAGAIN;
	inode = kpath.dentry->d_inode;
	if (inode == NULL) {
                path_put(&kpath);
                return -EINVAL;
        }	
	if (strcmp(inode->i_sb->s_type->name, "ext3") != 0) {
		path_put(&kpath);
		return -ENODEV;
	}
	if (inode->i_op->get_gps_location != NULL)
		ret = inode->i_op->get_gps_location(inode, kloc);
	else 
		ret = -ENOENT;
	path_put(&kpath);
	return ret;
}

void get_k_gps(struct gps_kernel *result)
{
	if (result == NULL)
		return;
	read_lock(&k_loc_lock);
	*result = k_gps;
	read_unlock(&k_loc_lock);
}

SYSCALL_DEFINE2(get_gps_location, const char __user *, pathname,
struct gps_location __user *, loc)
{
	struct gps_location kloc;
	char *kpathname;
	int ret;

	int path_size = PATH_MAX + 2;
	if (pathname == NULL || loc == NULL)
		return -EINVAL;
	kpathname = kmalloc(path_size * sizeof(char), GFP_KERNEL);
	if (kpathname == NULL)
		return -ENOMEM;
	ret = strncpy_from_user(kpathname, pathname, path_size);
	if (ret < 0) {
		kfree(kpathname);
		return -EFAULT;
	} else if (ret == path_size) {
		kfree(kpathname);
		return -ENAMETOOLONG;
	}
	ret = get_file_gps_location(kpathname, &kloc);
	if (ret < 0) {
		kfree(kpathname);
		return -EAGAIN;
	}
	/*if (kloc.latitude == 0 && kloc.longitude == 0
		&& kloc.accuracy == 0 && ret == 0) {
		kfree(kpathname);
		return -ENODEV;
	}*/
	if (copy_to_user(loc, &kloc, sizeof(struct gps_location)) != 0) {
		kfree(kpathname);
		return -EFAULT;
	}
	kfree(kpathname);
	return ret;
}
