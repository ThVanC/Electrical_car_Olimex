#include "drive.h"
#include "imx233.h"
#include "pwm_mmap.h"
#include "gpio_mmap.h"
#include <stdio.h>

#ifndef DRIVE
#define DRIVE

#define MINIMALE_SNELHEID 0
#define MAXIMALE_SNELHEID 20
#define CLKGATE 0x40000000
#define SFTRST  0x80000000

//hier moeten de periode, de (in)active en de periode deler nog aangepast worden.

int initDrive(){
	// Change the function of the processor pins
	// deze zet pinnen 26 en 27 op bank 1 op pwm0 en pwm1.

	gpio_map();
	printf("gpio_map klaar \n");
	pwm_map();
	printf("pwm_map klaar \n");


	gpio_wr_eigen(HW_PINCTRL_MUXSEL3_CLR, 0x03f00000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE7_CLR,  0x00002200);
	gpio_wr_eigen(HW_PINCTRL_DRIVE7_SET,  0x00001100);
	gpio_wr_eigen(HW_PINCTRL_DIN1_CLR,	  0x06000000);
	gpio_wr_eigen(HW_PINCTRL_DOE1_SET,	  0x06000000);

	printf("multiplexing klaar \n");
	forward();
	printf("forward klaar \n");
	speed(0);
	printf("rijden klaar \n");

}

int forward(){
   

	pwm_wr(HW_PWM_CTRL_CLR, 0b11110000000000000000000001111000);
	pwm_wr(HW_PWM_CTRL_SET, 0b00001110000000000000000000000111);

	pwm_wr(HW_PWM_ACTIVE1_SET, 0b00000010100000000000000101000000);
	pwm_wr(HW_PWM_ACTIVE1_CLR, 0b11111101011111111111111010111111);

	pwm_wr(HW_PWM_PERIOD1_SET, 0b00000000000011100000001010000000);
	pwm_wr(HW_PWM_PERIOD1_CLR, 0b00000001111100011111110101111111);
}

int left(){

   // Set the duty cycle
	//we kiezen 3/4 van de periode voor forward. Dit moet wel nog allemaal geverifieerd worden!
   pwm_wr(HW_PWM_ACTIVE1, 0x000005dc);
   
   // Set the period
   pwm_wr(HW_PWM_PERIOD1, 0x004b7530);
   
   // Enable the PWM output
   pwm_wr(HW_PWM_CTRL_SET, 0x06000002);
}

int right(){
	//We kiezen 5/4 van de periode van forward. Verifieren!!
   // Set the duty cycle
   pwm_wr(HW_PWM_ACTIVE1, 0x00000bb8);
   
   // Set the period
   pwm_wr(HW_PWM_PERIOD1, 0x004b7530);
   
   // Enable the PWM output
   pwm_wr(HW_PWM_CTRL_SET, 0x06000002);
}

int speed(int s){
	//Hier moet de periode, active,... nog bepaald worden.
	unsigned int waarde, tijd;
	if(s < MINIMALE_SNELHEID )
		waarde = MINIMALE_SNELHEID;
	else if(s > MAXIMALE_SNELHEID )
		waarde = MAXIMALE_SNELHEID;
	else waarde = s;

	tijd = (int)((waarde - MINIMALE_SNELHEID)*1.0*(1500.0)/(MAXIMALE_SNELHEID*1.0-MINIMALE_SNELHEID*1.0)+1500.0);
	//bron is wikipedia:
	//wanneer we hem niet willen laten draaien, moeten we de breedte op 1ms instellen. De breedte kan variëren van 1ms->2ms. 

	pwm_wr(HW_PWM_CTRL_CLR, 0b11111000000000000000000001111100);
	pwm_wr(HW_PWM_CTRL_SET, 0b00000110000000000000000000000011);

	pwm_wr(HW_PWM_ACTIVE0_SET, 0b00000010100000000000000101000000);
	pwm_wr(HW_PWM_ACTIVE0_CLR, 0b11111101011111111111111010111111);

	pwm_wr(HW_PWM_PERIOD0_SET, 0b00000000100011100000001010000000);
	pwm_wr(HW_PWM_PERIOD0_CLR, 0b00000001011100011111110101111111);

}

void gpio_test(){
	int i;
	gpio_wr_eigen(HW_PINCTRL_MUXSEL3_SET, 0b00000000000000000000000000110000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE6_SET,  0b00000000000000000000000100000000);
	gpio_wr_eigen(HW_PINCTRL_DRIVE6_CLR,  0b00000000000000000000001000000000);
	gpio_wr_eigen(HW_PINCTRL_PULL1_SET,   0b00000000000001000000000000000000);
	gpio_wr_eigen(HW_PINCTRL_DIN1_CLR,    0b00000000000001000000000000000000);
	gpio_wr_eigen(HW_PINCTRL_DOE1_SET,    0b00000000000001000000000000000000);
	for(i = 0; i<100; i++){
		gpio_wr_eigen(HW_PINCTRL_DOUT1_SET,   0b00000000000001000000000000000000);
		usleep(100000);
		gpio_wr_eigen(HW_PINCTRL_DOUT1_CLR,   0b00000000000001000000000000000000);
		usleep(100000);
	}
}

#endif