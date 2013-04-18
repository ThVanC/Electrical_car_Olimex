#include "imx233.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int* pwm_mmap;

int *pwm_map() {
	int fd;
	if (pwm_mmap != 0) return;
		fd = open("/dev/mem", O_RDWR);
	if( fd < 0 ) {
		perror("Unable to open /dev/mem");
		fd = 0;
	}

	pwm_mmap = mmap(0, 0xfff, PROT_READ|PROT_WRITE, MAP_SHARED, fd, HW_PWM_CTRL);
	if( -1 == (int)pwm_mmap) {
		perror("Unable to mmap file");
		pwm_mmap = 0;
	}
	if( -1 == close(fd))
		perror("Couldn't close file");
	fd=0;
}

int pwm_rd(long offset) {
	return pwm_mmap[offset/4];
}

void pwm_wr(long offset, int value) {
	offset=offset - HW_PWM_CTRL;
	printf("%d\n",offset);
	pwm_mmap[offset] = value;
}