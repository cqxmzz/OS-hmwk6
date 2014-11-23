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
