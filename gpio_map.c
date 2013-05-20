#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "gpio_map.h"

/**************************

Maak een memory mapping voor de GPIO.

***************************/
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

/**************************

Oorspronkelijk read functie: werkt NIET goed!!!

***************************/
int gpio_rd(long offset) {
	return gpio_mmap[offset/4];
}

/**************************

Oorspronkelijk write functie: werkt NIET goed!!!

***************************/
void gpio_wr(long offset, long value) {
	gpio_mmap[offset/4] = value;
}

/**************************

Stel een gpio pin in als output. Deze geeft niet altijd het gehoopte resultaat.

***************************/
void gpio_output(int bank, int pin) {
	printf("gpio_output\n");
	gpio_mmap[0x1C1 + (bank*4)] = 1 << pin;
	printf("gpio_output\n");
}

/**************************

Stel een gpio pin in als input. Niet gebruikt.

***************************/
void gpio_input(int bank, int pin) {
	gpio_mmap[0x1C2 + (bank*4)] = 1 << pin;
}

/**************************

EEn write functie die zelf geschreven is en veelvuldig getest is.

***************************/
void gpio_wr_eigen(long offset, long value){
	offset = offset - GPIO_BASE;
	gpio_mmap[offset/4] = value;
}
