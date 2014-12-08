#include "file_loc.h"

int main(int argc, char **argv)
{
	char *path;
	int ret;
	struct gps_location loc;

	if (argc != 2)
		return -EINVAL;
	path = argv[1];
	ret = syscall(379, path, &loc);
	if (ret < 0) {
		printf("Error: syscall returned %d\n", ret);
		return -EINVAL;
	}else {
		printf("File: %s\n", path);
		printf("Latitude: %lf\n", loc.latitude);
		printf("Longitude: %lf\n", loc.longitude);
		printf("Accuracy: %f\n", loc.accuracy);
		printf("Age: %d\n", ret);
	}
	return 0;
}
