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
   imx233_wr(HW_PWM_ACTIVE1, 0x00000bb8);
   
   // Set the period
   imx233_wr(HW_PWM_PERIOD1, 0x002b7530);
   
   // Enable the PWM output
   imx233_wr(HW_PWM_CTRL_SET, 0x06000002);
}

int left(){

   // Set the duty cycle
	//we kiezen 3/4 van de periode voor forward. Dit moet wel nog allemaal geverifieerd worden!
   imx233_wr(HW_PWM_ACTIVE1, 0x000008ca);
   
   // Set the period
   imx233_wr(HW_PWM_PERIOD1, 0x002b7530);
   
   // Enable the PWM output
   imx233_wr(HW_PWM_CTRL_SET, 0x06000002);
}

int right(){
	//We kiezen 5/4 van de periode van forward. Verifieren!!
   // Set the duty cycle
   imx233_wr(HW_PWM_ACTIVE1, 0x00000ea6);
   
   // Set the period
   imx233_wr(HW_PWM_PERIOD1, 0x002b7530);
   
   // Enable the PWM output
   imx233_wr(HW_PWM_CTRL_SET, 0x06000002);
}

int speed(int s){
	//Hier moet de periode, active,... nog bepaald worden.
	int waarde;
	if(s < MINIMALE_SNELHEID )
		waarde = MINIMALE_SNELHEID;
	else if(s > MAXIMALE_SNELHEID )
		waarde = MAXIMALE_SNELHEID;
	else waarde = s;
   // Set the duty cycle
   imx233_wr(HW_PWM_ACTIVE0, 0x012c0000);
   
   // Set the period
   imx233_wr(HW_PWM_PERIOD0, 0x000e04b0);
   
   // Enable the PWM output
   imx233_wr(HW_PWM_CTRL_SET, 0x06000001);
}

#endif