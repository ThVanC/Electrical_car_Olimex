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
	offset = offset- HW_PWM_CTRL;
	return pwm_mmap[offset/4];
}


/****************************************

Maak gebruik van de adressen die in imx233.h staan om de pwm te gaan gebruiken. 
De functie zal namelijk de PWM_BASE offset ervan aftrekken.
Merk op! Gebruik aub enkel adressen die overeenkomen met een register dat te maken heeft met PWM-controle (H37). Voor andere doeleinde maak je beste en nieuwe memory mapping.

****************************************/
void pwm_wr(long offset, int value) {
	offset=offset - HW_PWM_CTRL;
	pwm_mmap[offset/4] = value;
}