#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/gps.h>
/* Wendan Kang*/
static DEFINE_SPINLOCK(k_loc_lock);
static struct gps_location k_gps_location = {
	.latitude = 0.0,
	.longitude = 0.0,
	.accuracy = 0.0
};
/* citation: hmwk3 solution*/
SYSCALL_DEFINE1(set_gps_location, struct gps_location __user *, loc)
{
	struct gps_location k_loc;
	if(current_uid() != 0)
		return -EACCES;
	if(loc == NULL)
		return -EINVAL;
	if(copy_from_user(&k_loc, loc, sizeof(k_loc)))
		return -EFAULT;
	spin_lock(&k_loc_lock);
	memcpy(&k_gps_location, &k_loc, sizeof(k_loc));
	spin_unlock(&k_loc_lock);
	return 0;
}

/* Cai Yuannan 
SYSCALL_DEFINE2(get_gps_location, const char __user *, pathname,
struct gps_location __user *, loc)
{
	struct gps_location kloc;
	struct inode *inode;
	struct path path;
	int coord_age = 0;

	if (pathname == NULL || loc == NULL)
		return -EINVAL;

	if (!capable(CAP_SYS_ADMIN)) {
		pr_err("NOT A SYS ADMIN!!\n");
		return -EACCES;
	}

	if (user_path(pathname, &path)) {
		return -EFAULT;
	}

	if (!path.dentry->d_inode)
		return -EFAULT;

	inode = path.dentry->d_inode;

	if (inode->i_op && inode->i_op->get_gps_location)
		coord_age = inode->i_op->get_gps_location(inode, &kloc);
	else
	return -EFAULT;

	if (copy_to_user(&loc->latitude, &kloc.latitude, sizeof(loc->latitude)))
		return -EFAULT;

	if (copy_to_user(&loc->longitude, &kloc.longitude,
		sizeof(loc->longitude)))
		return -EFAULT;
	
	if (copy_to_user(&loc->accuracy, &kloc.accuracy,
		sizeof(loc->accuracy)))
		return -EFAULT;

	return coord_age;
}*/
