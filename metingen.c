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

int calculateStateofCharge(int *prevCurrent, unsigned long *prevTime){
	
	// Definieer variabelen
	int current;
	int voltage;
	unsigned long currentTime;
	int timePeriod;
	int newStateofCharge;
	struct timeval tv;
	
	// Controle van de pointers
	if (prevCurrent == NULL || prevTime == NULL) return -1; 

	// Lees huidige spanning en stroom in
	// en bepaal de nieuwe som van stromen
	current = measureI() + *prevCurrent;
	voltage = measureV();

	// Lees huidige tijd in (microseconden)
	gettimeofday(&tv,NULL);
	currentTime = tv.tv_sec * 1000000L + tv.tv_usec;

	// Bereken de periode tussen vorig en huidig sample
	// Omzetten van microseconden naar uur (1/(1000*1000*60*60)
	timePeriod = (currentTime - *prevTime)/(1000*1000*60*60);
	
	// Als alle pointers NULL zijn, moet initialisatie uitgevoerd worden
	if (voltage > V_THRESHOLD_CELL*NR_OF_CELLS*MARGE) {
	 	// Batterijspanning is aan threshold
		// batterij is volledig opgeladen
		newStateofCharge = 99;
	}else if (voltage < V_LOW_CELL*NR_OF_CELLS*(2-MARGE)){
		// Batterij staat op laagste spanning
		newStateofCharge = 1;
	} else{
		// Bereken nieuwe SoC
		newStateofCharge = (current*timePeriod) / C;
	}

	// Update 'vorige' waarden
	*prevCurrent = current;
	*prevTime = currentTime;
	return newStateofCharge;
}
