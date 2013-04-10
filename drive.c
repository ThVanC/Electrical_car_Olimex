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
	speed(0);
}

int forward(){

   // Set the duty cycle
   imx233_wr(HW_PWM_ACTIVE1, 0x000008ca);
   
   // Set the period
   imx233_wr(HW_PWM_PERIOD1, 0x004b7530);
   
   // Enable the PWM output
   imx233_wr(HW_PWM_CTRL_SET, 0x06000002);
}

int left(){

   // Set the duty cycle
	//we kiezen 3/4 van de periode voor forward. Dit moet wel nog allemaal geverifieerd worden!
   imx233_wr(HW_PWM_ACTIVE1, 0x000005dc);
   
   // Set the period
   imx233_wr(HW_PWM_PERIOD1, 0x004b7530);
   
   // Enable the PWM output
   imx233_wr(HW_PWM_CTRL_SET, 0x06000002);
}

int right(){
	//We kiezen 5/4 van de periode van forward. Verifieren!!
   // Set the duty cycle
   imx233_wr(HW_PWM_ACTIVE1, 0x00000bb8);
   
   // Set the period
   imx233_wr(HW_PWM_PERIOD1, 0x004b7530);
   
   // Enable the PWM output
   imx233_wr(HW_PWM_CTRL_SET, 0x06000002);
}

int speed(int s){
	//Hier moet de periode, active,... nog bepaald worden.
	int waarde, tijd;
	if(s < MINIMALE_SNELHEID )
		waarde = MINIMALE_SNELHEID;
	else if(s > MAXIMALE_SNELHEID )
		waarde = MAXIMALE_SNELHEID;
	else waarde = s;

	tijd = (int)((waarde - MINIMALE_SNELHEID)*1.0*(1500.0)/(MAXIMALE_SNELHEID*1.0-MINIMALE_SNELHEID*1.0)+1500.0);
	//bron is wikipedia:
	//wanneer we hem niet willen laten draaien, moeten we de breedte op 1ms instellen. De breedte kan variëren van 1ms->2ms. 
	// Set the duty cycle
	imx233_wr(HW_PWM_ACTIVE0, tijd);
   
	// Set the period
	imx233_wr(HW_PWM_PERIOD0, 0x000b7530);
   
	// Enable the PWM output
	imx233_wr(HW_PWM_CTRL_SET, 0x06000001);
}

#endif