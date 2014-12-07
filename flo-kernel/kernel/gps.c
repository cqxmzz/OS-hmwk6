#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/gps.h>
#include <linux/time.h>

/* Wendan Kang*/
static DEFINE_RWLOCK(k_loc_lock);
static struct gps_kernel k_gps = {
	.location = {
		.latitude = 0.0,
		.longitude = 0.0,
		.accuracy = 0.0
	}
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

/* Cai Yuannan */
SYSCALL_DEFINE2(get_gps_location, const char __user *, pathname,
struct gps_location __user *, loc)
{
	return 0;
}

void get_k_gps(struct gps_kernel *result)
{
	if (result == NULL)
		return;

	read_lock(&k_loc_lock);
	*result = k_gps;
	read_unlock(&k_loc_lock);
}
