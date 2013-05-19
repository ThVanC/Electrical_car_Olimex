#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "gpio_map.h"

void *gpio_map() {
	int fd;
	if (gpio_mmap != 0) 
		return NULL;
	fd = open("/dev/mem", O_RDWR);
	if( fd < 0 ) {
		perror("Unable to open /dev/mem");
		fd = 0;
	}

	gpio_mmap = mmap(0, 0xfff, PROT_READ|PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
	if( -1 == (int)gpio_mmap) {
		perror("Unable to mmap file");
		gpio_mmap = 0;
	}
	if( -1 == close(fd))
		perror("Couldn't close file");
	fd=0;
	//return 0;
}

int gpio_rd(long offset) {
	return gpio_mmap[offset/4];
}

void gpio_wr(long offset, long value) {
	gpio_mmap[offset/4] = value;
}

void gpio_output(int bank, int pin) {
	printf("gpio_output\n");
	gpio_mmap[0x1C1 + (bank*4)] = 1 << pin;
	printf("gpio_output\n");
}

void gpio_input(int bank, int pin) {
	gpio_mmap[0x1C2 + (bank*4)] = 1 << pin;
}

void gpio_wr_eigen(long offset, long value){
	offset = offset - GPIO_BASE;
	gpio_mmap[offset/4] = value;
}
