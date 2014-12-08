#include "file_loc.h"

int main(int argc, char **argv)
{
	char *path;
	double lat;
	double lon;
	float acc;
	int ret;
	struct gps_location loc;

	if (argc != 2)
		return -EINVAL;
	path = argc[1];
	ret = syscall(379, path, &loc);
	if (ret < 0) {
		printf("Error: syscall returned %d\n", ret);
		return -EINVAL;
	}
	else {
		printf("File: %s\n", path);
		printf("Latitude: %lf\n", lat);
		printf("Longitude: %lf\n", lon);
		printf("Accuracy: %d\n", acc);
		printf("Age: %d\n", ret);
	}
	return 0;
}
