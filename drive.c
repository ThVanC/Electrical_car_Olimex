#include "drive.h"
#include "pin_config.h"
#include "imx233.h"
#include <stdio.h>

#ifndef DRIVE
#define DRIVE

#define MINIMALE_SNELHEID 0
#define MAXIMALE_SNELHEID 20


/**************************

//hier moeten de periode, de (in)active en de periode deler nog aangepast worden.

***************************/
int initDrive(){
	// Change the function of the processor pins
	// deze zet pinnen 26 en 27 op bank 1 op pwm0 en pwm1.


	printf("multiplexing klaar \n");
	initLCD6();
	initLCD7();
	initLCD8();
	initLCD9();
	initLCD10();
	initLCD11();
	initLCD12();
	initLCD13();
	initLCD14();
	moveForward();
	printf("forward klaar \n");
	speed(0);
	printf("rijden klaar \n");
}


/**************************

Stel de servo in op forward. De periode is 20 ms en het signaal moet 1.5ms hoog staan.

***************************/
int moveForward(){
	clrLCD6();
	setLCD7();
	clrLCD8();
	clrLCD9();
}

/**************************

Stel de servo in op 90° left. De periode is 20 ms en het signaal moet 1ms hoog staan.

***************************/
int moveLeft(){
	setLCD6();
	clrLCD7();
	clrLCD8();
	clrLCD9();
}

/**************************

Stel de servo in op 90° right. De periode is 20 ms en het signaal moet 2ms hoog staan.

***************************/
int moveRight(){
	clrLCD6();
	clrLCD7();
	clrLCD8();
	setLCD9();
}

/**************************

Stel de snelheid hier in. 
De ESC werkt aan een frequentie van 50Hz. Wederom signaal tussen de 1ms (stilstaan) en 2 ms (plank gas!) instellen.

***************************/
int speed(int s){
	int par1 = (int)(MINIMALE_SNELHEID), par2 = (int)( MAXIMALE_SNELHEID/4), par3 = (int) ((MAXIMALE_SNELHEID/2)), par4= (int)((3*MAXIMALE_SNELHEID/4));
	if(s<0){
		clrLCD6();
		clrLCD7();
		setLCD8();
		clrLCD9();
		clrLCD10();
		clrLCD11();
		clrLCD12();
		clrLCD13();
		clrLCD14();
		return 1;
	}
	printf("Par1: %d\nPar2: %d\nPar3: %d\nPar4: %d\n",par1,par2,par3,par4);
	if(par1 <= s && s <= par2){
		printf("1 ledje\t%d\n",s);
		setLCD10();
		clrLCD11();
		clrLCD12();
		clrLCD13();
		clrLCD14();
	}else if(par2< s && s <= par3){
		printf("2 ledjes\t%d\n",s);
		setLCD10();
		setLCD11();
		clrLCD12();
		clrLCD13();
		clrLCD14();
	}else if(par3 < s && s <= par4){
		printf("3 ledjes\t%d\n",s);
		setLCD10();
		setLCD11();
		setLCD12();
		clrLCD13();
		clrLCD14();
	}else{
		printf("4 ledjes\t%d\n",s);
		setLCD10();
		setLCD11();
		setLCD12();
		setLCD13();
		setLCD14();
	}
}

#endif