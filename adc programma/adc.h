#include "imx233.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef ADC_H
#define ADC_h


int initLRADC0();
int initLRADC1();

// hier gaan we de waarde uitlezen. Je moet wel aangeven uit welke ADC je gaat lezen. 
// De chip heeft namelijk 12 kanalen die allemaal over 1 multiplexer komen. Dus je kan er maar 1 gelijktijdig gebruiken.
int readLRADC0();
int readLRADC1();

int* lradc_mmap;

int *lradc_map() {
	int fd;
	if (lradc_mmap != 0) return;
		fd = open("/dev/mem", O_RDWR);
	if( fd < 0 ) {
		perror("Unable to open /dev/mem");
		fd = 0;
	}

	lradc_mmap = mmap(0, 0xfff, PROT_READ|PROT_WRITE, MAP_SHARED, fd, HW_LRADC_CTRL0);
	if( -1 == (int)lradc_mmap) {
		perror("Unable to mmap file");
		lradc_mmap = 0;
	}
	if( -1 == close(fd))
		perror("Couldn't close file");
	fd=0;
}

int lradc_rd(long offset) {
	offset = offset - HW_LRADC_CTRL0;
	return lradc_mmap[offset/4];
}


/****************************************

Maak gebruik van de adressen die in imx233.h staan om de pwm te gaan gebruiken. 
De functie zal namelijk de PWM_BASE offset ervan aftrekken.
Merk op! Gebruik aub enkel adressen die overeenkomen met een register dat te maken heeft met PWM-controle (H37). Voor andere doeleinde maak je beste en nieuwe memory mapping.

****************************************/
void lradc_wr(long offset, int value) {
	offset=offset - HW_LRADC_CTRL0;
	lradc_mmap[offset/4] = value;
}


#endif