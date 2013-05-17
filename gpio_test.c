#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <unistd.h>
#include <sched.h>
#include "imx233.h"
#include "gpio_map.h"

#ifndef MAIN
#define MAIN

/***************************************

init:	instellen van de pin als GPIO-output.
set:	laat een hoog signaal naar buiten gaan.
clr:	laat een laag signaal naar buiten gaan.

***************************************/

/***************************************

LCD6

***************************************/
void initLCD6(){
	gpio_map();
	gpio_wr_eigen(HW_PINCTRL_MUXSEL2_SET, 0b00000000000000000011000000000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE4_SET,  0b00000001000000000000000000000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE4_CLR,  0b00000010000000000000000000000000);
	//gpio_wr_eigen(HW_PINCTRL_PULL1_SET,   0b00000000000001000000000000000000);
	gpio_wr_eigen(HW_PINCTRL_DIN1_CLR,    0b00000000000000000000000001000000);
	gpio_wr_eigen(HW_PINCTRL_DOE1_SET,    0b00000000000000000000000001000000);
}

void setLCD6(){
	gpio_wr_eigen(HW_PINCTRL_DOUT1_SET,   0b00000000000000000000000001000000);
}

void clrLCD6(){
	gpio_wr_eigen(HW_PINCTRL_DOUT1_CLR,   0b00000000000000000000000001000000);
}

/***************************************

LCD7

***************************************/
void initLCD7(){
	gpio_map();
	gpio_wr_eigen(HW_PINCTRL_MUXSEL2_SET, 0b00000000000000001100000000000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE4_SET,  0b00010000000000000000000000000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE4_CLR,  0b00100000000000000000000000000000);
	//gpio_wr_eigen(HW_PINCTRL_PULL1_SET,   0b00000000000001000000000000000000);
	gpio_wr_eigen(HW_PINCTRL_DIN1_CLR,    0b00000000000000000000000010000000);
	gpio_wr_eigen(HW_PINCTRL_DOE1_SET,    0b00000000000000000000000010000000);
}

void setLCD7(){
	gpio_wr_eigen(HW_PINCTRL_DOUT1_SET,   0b00000000000000000000000010000000);
}

void clrLCD7(){
	gpio_wr_eigen(HW_PINCTRL_DOUT1_CLR,   0b00000000000000000000000010000000);
}

/***************************************

LCD8: NOG NIET GEFIXED!!

***************************************/
void initLCD8(){
	gpio_map();
	gpio_wr_eigen(HW_PINCTRL_MUXSEL0_SET, 0b00000000000000000000000000000011);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_SET,  0b00000000000000000000000000000001);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_CLR,  0b00000000000000000000000000000010);
	gpio_wr_eigen(HW_PINCTRL_PULL0_SET,   0b00000000000000000000000000000001);
	gpio_wr_eigen(HW_PINCTRL_DIN0_CLR,    0b00000000000000000000000000000001);
	gpio_wr_eigen(HW_PINCTRL_DOE0_SET,    0b00000000000000000000000000000001);
}

void setLCD8(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_SET,   0b00000000000000000000000000000001);
}

void clrLCD8(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_CLR,   0b00000000000000000000000000000001);
}

/***************************************

LCD9

***************************************/
void initLCD9(){
	gpio_map();
	gpio_wr_eigen(HW_PINCTRL_MUXSEL0_SET, 0b00000000000000000000000000001100);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_SET,  0b00000000000000000000000000010000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_CLR,  0b00000000000000000000000000100000);
	gpio_wr_eigen(HW_PINCTRL_PULL0_SET,   0b00000000000000000000000000000010);
	gpio_wr_eigen(HW_PINCTRL_DIN0_CLR,    0b00000000000000000000000000000010);
	gpio_wr_eigen(HW_PINCTRL_DOE0_SET,    0b00000000000000000000000000000010);
}

void setLCD9(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_SET,   0b00000000000000000000000000000010);
}

void clrLCD9(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_CLR,   0b00000000000000000000000000000010);
}

/***************************************

LCD10

***************************************/
void initLCD10(){
	gpio_map();
	gpio_wr_eigen(HW_PINCTRL_MUXSEL0_SET, 0b00000000000000000000000000110000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_SET,  0b00000000000000000000000100000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_CLR,  0b00000000000000000000001000000000);
	gpio_wr_eigen(HW_PINCTRL_PULL0_SET,   0b00000000000000000000000000000100);
	gpio_wr_eigen(HW_PINCTRL_DIN0_CLR,    0b00000000000000000000000000000100);
	gpio_wr_eigen(HW_PINCTRL_DOE0_SET,    0b00000000000000000000000000000100);
}

void setLCD10(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_SET,   0b00000000000000000000000000000100);
}

void clrLCD10(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_CLR,   0b00000000000000000000000000000100);
}

/***************************************

LCD11

***************************************/
void initLCD11(){
	gpio_map();
	gpio_wr_eigen(HW_PINCTRL_MUXSEL0_SET, 0b00000000000000000000000011000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_SET,  0b00000000000000000001000000000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_CLR,  0b00000000000000000010000000000000);
	gpio_wr_eigen(HW_PINCTRL_PULL0_SET,   0b00000000000000000000000000001000);
	gpio_wr_eigen(HW_PINCTRL_DIN0_CLR,    0b00000000000000000000000000001000);
	gpio_wr_eigen(HW_PINCTRL_DOE0_SET,    0b00000000000000000000000000001000);
}

void setLCD11(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_SET,   0b00000000000000000000000000001000);
}

void clrLCD11(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_CLR,   0b00000000000000000000000000001000);
}

/***************************************

LCD12

***************************************/
void initLCD12(){
	gpio_map();
	gpio_wr_eigen(HW_PINCTRL_MUXSEL0_SET, 0b00000000000000000000001100000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_SET,  0b00000000000000010000000000000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_CLR,  0b00000000000000100000000000000000);
	gpio_wr_eigen(HW_PINCTRL_PULL0_SET,   0b00000000000000000000000000010000);
	gpio_wr_eigen(HW_PINCTRL_DIN0_CLR,    0b00000000000000000000000000010000);
	gpio_wr_eigen(HW_PINCTRL_DOE0_SET,    0b00000000000000000000000000010000);
}

void setLCD12(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_SET,   0b00000000000000000000000000010000);
}

void clrLCD12(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_CLR,   0b00000000000000000000000000010000);
}

/***************************************

LCD13

***************************************/
void initLCD13(){
	gpio_map();
	gpio_wr_eigen(HW_PINCTRL_MUXSEL0_SET, 0b00000000000000000000110000000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_SET,  0b00000000000100000000000000000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_CLR,  0b00000000001000000000000000000000);
	gpio_wr_eigen(HW_PINCTRL_PULL0_SET,   0b00000000000000000000000000100000);
	gpio_wr_eigen(HW_PINCTRL_DIN0_CLR,    0b00000000000000000000000000100000);
	gpio_wr_eigen(HW_PINCTRL_DOE0_SET,    0b00000000000000000000000000100000);
}

void setLCD13(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_SET,   0b00000000000000000000000000100000);
}

void clrLCD13(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_CLR,   0b00000000000001000000000000000000);
}

/***************************************

LCD14

***************************************/
void initLCD14(){
	gpio_wr_eigen(HW_PINCTRL_MUXSEL0_SET, 0b00000000000000000011000000000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_SET,  0b00000001000000000000000000000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE0_CLR,  0b00000010000000000000000000000000);
	gpio_wr_eigen(HW_PINCTRL_PULL0_SET,   0b00000000000000000000000001000000);
	gpio_wr_eigen(HW_PINCTRL_DIN0_CLR,    0b00000000000000000000000001000000);
	gpio_wr_eigen(HW_PINCTRL_DOE0_SET,    0b00000000000000000000000001000000);
}

void setLCD14(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_SET,   0b00000000000000000000000001000000);
}

void clrLCD14(){
	gpio_wr_eigen(HW_PINCTRL_DOUT0_CLR,   0b00000000000000000000000001000000);
}

/***************************************

Main: de ledjes 100 keer laten pinken.

***************************************/
int gpio_test(){
	int i;
	gpio_map();
	initLCD6();
	initLCD7();
	initLCD8();
	initLCD9();
	initLCD10();
	initLCD11();
	initLCD12();
	initLCD13();
	initLCD14();



	for(i=0; i<100; i++){
		setLCD6();
		setLCD7();
		setLCD8();
		setLCD9();
		setLCD10();
		setLCD10();
		setLCD11();
		setLCD12();
		setLCD13();
		setLCD14();

		usleep(200000);
		clrLCD6();
		clrLCD7();
		clrLCD8();
		clrLCD9();
		clrLCD10();
		clrLCD10();
		clrLCD11();
		clrLCD12();
		clrLCD13();
		clrLCD14();
		
		usleep(200000);
	}
}

#endif