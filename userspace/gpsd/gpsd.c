#include "gpsd.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#define LINE_SIZE 1024

/* Wendan Kang */

/* citation: hmwk3 solution*/
void daemon_mode()
{
	pid_t pid;
	if((pid = fork()) < 0) {
		perror("Fail fork");
		exit(EXIT_FAILURE);
	}

	if(pid > 0)
		exit(EXIT_SUCCESS);

	if(setsid() < 0) {
		perror("Fail to setsid");
		exit(EXIT_FAILURE);
	}

	if((pid = fork()) < 0) {
                perror("Fail fork");
                exit(EXIT_FAILURE);
        }

        if(pid > 0)
                exit(EXIT_SUCCESS);

	close(0);
	close(1);
	close(2);
	chdir("/data/misc/");
	umask(0);

	return;
}

static int poll_gps_data()
{
	struct gps_location data;
	FILE *fp;
	char line[LINE_SIZE];
	int place = 0;
	fp = fopen(GPS_LOCATION_FILE, "r");
	if(fp == NULL)
		return EXIT_FAILURE;
	while (fgets(line, sizeof(line), fp)) {
		if (place == 0)
			data.latitude = strtod(line, NULL);
		else if (place == 1)
			data.longitude = strtod(line, NULL);
		else if (place == 2)
			data.accuracy = atof(line);
		place++;
		if (place > 3) 
			break;
	}
	fclose(fp);
	set_gps_location(&data);
	return 0;
}

int main(int argc, char *argv[])
{
	daemon_mode();
	while(1) {
		poll_gps_data();
		usleep(1000000);
	}
	return 0;
}
