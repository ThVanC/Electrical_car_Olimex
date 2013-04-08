#include "drive.h"
#include "imx233.h"

#ifndef DRIVE
#define DRIVE

#define MINIMALE_SNELHEID 5
#define MAXIMALE_SNELHEID 20

//hier moeten de periode, de (in)active en de periode deler nog aangepast worden.

int initDrive(){
	   // Change the function of the processor pins
	//deze zet pinnen 26 en 27 op bank 1 op pwm0 en pwm1.
   imx233_wr(HW_PINCTRL_MUXSEL3_CLR, 0x00f00000);
   
	forward();
}

int forward(){

   // Set the duty cycle
   imx233_wr(HW_PWM_ACTIVE1, 0x012c0000);
   
   // Set the period
   imx233_wr(HW_PWM_PERIOD1, 0x000b04b0);
   
   // Enable the PWM output
   imx233_wr(HW_PWM_CTRL_SET, 0x06000002);
}

int left(){

   // Set the duty cycle
   imx233_wr(HW_PWM_ACTIVE1, 0x012c0000);
   
   // Set the period
   imx233_wr(HW_PWM_PERIOD1, 0x000b04b0);
   
   // Enable the PWM output
   imx233_wr(HW_PWM_CTRL_SET, 0x06000002);
}

int right(){

   // Set the duty cycle
   imx233_wr(HW_PWM_ACTIVE1, 0x012c0000);
   
   // Set the period
   imx233_wr(HW_PWM_PERIOD1, 0x000b04b0);
   
   // Enable the PWM output
   imx233_wr(HW_PWM_CTRL_SET, 0x06000002);
}

int speed(int s){
	int waarde;
	if(s < MINIMALE_SNELHEID )
		waarde = MINIMALE_SNELHEID;
	else if(s > MAXIMALE_SNELHEID )
		waarde = MAXIMALE_SNELHEID;
	else waarde = s;
   // Set the duty cycle
   imx233_wr(HW_PWM_ACTIVE1, 0x012c0000);
   
   // Set the period
   imx233_wr(HW_PWM_PERIOD1, 0x000e04b0);
   
   // Enable the PWM output
   imx233_wr(HW_PWM_CTRL_SET, 0x06000001);
}

#endif