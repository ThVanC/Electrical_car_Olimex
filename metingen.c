#include "metingen.h"
#include "adc.h"

int initMeasurements(){
	initLRADC0();
	initLRADC1();
	//klopt het dat we voor i²c niets moeten initialiseren
}

int measureV(){
	int V_LRADC1,V_bat;//spanningen in mV
	
	V_LRADC1=readLRADC1();
	V_bat=(V_LRADC1*236)/56;//236 owv 56+180 ; haakjes zo zetten zal best nauwkeurigheid geven
	
	return V_bat;
}

int measureI(){
	int V_LRADC0,V_Hall;//spanningen in mV
	int curr;//stromen in mA

	V_LRADC0=readLRADC0();
	V_Hall=(V_LRADC0*340)/120;//340 owv 120+220 ; haakjes zo zetten zal best nauwkeurigheid geven
	
	//positieve stroom is opladen, negatieve is ontladen
	curr=(V_Hall-2500)*10; //want 100mV/A => 10mA/mV

	return curr;
}

int measureT(){
	//dit is met i²c
}
