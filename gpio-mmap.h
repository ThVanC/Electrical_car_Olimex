#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef GPIO_MMAP_H
#define GPIO_MMAP_H

#define GPIO_BASE 0x80018000
#define GPIO_WRITE_PIN(gpio,value) GPIO_WRITE((gpio)>>5, (gpio)&31, value)
#define GPIO_WRITE(bank,pin,value) (gpio_mmap[0x140+((bank)<<2)+((value)?1:2)] = 1<<(pin))
#define GPIO_READ_PIN(gpio) GPIO_READ((gpio)>>5, (gpio)&31)
#define GPIO_READ(bank,pin) ((gpio_mmap[0x180+((bank)<<2)] >> (pin)) & 1)

/*#define   HW_PINCTRL_MUXSEL3 0x130    //p 1445
#define   HW_PINCTRL_MUXSEL3_SET 0x134    //p 1445
#define   HW_PINCTRL_DRIVE6 0x260    //p 1463
#define   HW_PINCTRL_DRIVE6_SET 0x264    //p 1463
#define   HW_PINCTRL_PULL1 0x410    //p 1481
#define   HW_PINCTRL_PULL1_SET 0x414    //p 1481
#define   HW_PINCTRL_DOUT1 0x510    //p1486
#define   HW_PINCTRL_DOUT1_SET 0x514    //p1486
#define   HW_PINCTRL_DOE1 0x710    //p 1490
#define   HW_PINCTRL_DOE1_SET 0x714    //p 1490*/

int *gpio_mmap = 0;

int *gpio_map() {
	int fd;
	if (gpio_mmap != 0) return;
		fd = open("/dev/mem", O_RDWR);
	if( fd < 0 ) {
		perror("Unable to open /dev/mem");
		fd = 0;
	}

	//gpio_mmap = mmap(0, 0xfff, PROT_READ|PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
	gpio_mmap = mmap(0, 0xfff, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x0);
	if( -1 == (int)gpio_mmap) {
		perror("Unable to mmap file");
		gpio_mmap = 0;
	}
	if( -1 == close(fd))
		perror("Couldn't close file");
		fd=0;
}

void gpio_output(int bank, int pin) {
	gpio_mmap[0x1C1 + (bank*4)] = 1 << pin;
}

void gpio_input(int bank, int pin) {
	gpio_mmap[0x1C2 + (bank*4)] = 1 << pin;
}


void gpio_rd(long offset){
	offset = offset - GPIO_BASE;
	return gpio_mmap[offset/4];
}

/****************************************

Maak gebruik van de adressen die in imx233.h staan om de gpio te gaan gebruiken. 
De functie zal namelijk de GPIO_BASE offset ervan aftrekken.
Merk op! Gebruik aub enkel adressen die overeenkomen met een register dat te maken heeft met GPIO-controle (H37). Voor andere doeleinde maak je beste en nieuwe memory mapping.

****************************************/
void gpio_wr_eigen(long offset, long value){
	offset = offset - GPIO_BASE;
	gpio_mmap[offset/4] = value;
}

#endif