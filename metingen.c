#include "metingen.h"
#include "adc.h"
#include <sys/time.h>

int initMeasurements(){
	initLRADC0();
	initLRADC1();
	//klopt het dat we voor i²c niets moeten initialiseren
}

int measureV(){
	int V_LRADC1,V_bat;//spanningen in mV
	
	V_LRADC1=readLRADC1();
	V_bat=(V_LRADC1*(R4 + R5)) / R5; //236 owv 56+180 ; haakjes zo zetten zal best nauwkeurigheid geven
	
	return V_bat;
}

int measureI(){
	int V_LRADC0,V_Hall;//spanningen in mV
	int curr;//stromen in mA

	V_LRADC0=readLRADC0();
	V_Hall=(V_LRADC0*(R6 + R3)) / R6;//340 owv 120+220 ; haakjes zo zetten zal best nauwkeurigheid geven
	
	//positieve stroom is opladen, negatieve is ontladen
	curr=(V_Hall-2500)*10; //want 100mV/A => 10mA/mV

	return curr;
}

int measureT(){
	//dit is met i²c
}

int calculateStateofCharge(int prevSoC,int *prevCurrent,int *prevVoltage, unsigned long *prevTime){
	
	// Definieer variabelen
	int current;
	int voltage;
	unsigned long currentTime;
	int newStateofCharge;
	struct timeval tv;

	// Lees huidige spanning en stroom in
	current = measureI();
	voltage = measureV();

	// Lees huidige tijd in (microseconden)
	gettimeofday(&tv,NULL);
	currentTime = tv.tv_sec * 1000000L + tv.tv_usec;
	
	// Als alle pointers NULL zijn, moet initialisatie uitgevoerd worden
	if (prevCurrent == NULL && prevVoltage == NULL && prevTime == NULL) {
	 	// TODO: bepaal initialisatiewaarde
	}else if (prevCurrent != NULL && prevVoltage != NULL && prevTime != NULL){
		newStateofCharge = prevSoC + (((current - &prevCurrent) / 2) * (currentTime - &prevTime)) / lading;
	} else{
		// Fout: sommige pointers waren NULL-pointers
		return -1;
	}

	// Update 'vorige' waarden
	&prevCurrent = current;
	&prevVoltage = voltage;
	&prevTime = currentTime;
	return newStateofCharge;
}
