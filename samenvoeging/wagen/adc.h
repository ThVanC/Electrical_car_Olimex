#include "imx233.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef ADC_H
#define ADC_H


int initLRADC0();
int initLRADC1();

int convertToVoltage(int value);

// hier gaan we de waarde uitlezen. Je moet wel aangeven uit welke ADC je gaat lezen. 
// De chip heeft namelijk 12 kanalen die allemaal over 1 multiplexer komen. Dus je kan er maar 1 gelijktijdig gebruiken.
int readLRADC0();
int readLRADC1();

int *lradc_mmap;

void *lradc_map();

int lradc_rd(long offset);


/****************************************

Maak gebruik van de adressen die in imx233.h staan om de pwm te gaan gebruiken. 
De functie zal namelijk de PWM_BASE offset ervan aftrekken.
Merk op! Gebruik aub enkel adressen die overeenkomen met een register dat te maken heeft met PWM-controle (H37). Voor andere doeleinde maak je beste en nieuwe memory mapping.

****************************************/
void lradc_wr(long offset, int value);


#endif
