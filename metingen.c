#define TEST

#include <sys/time.h>
#ifndef TEST
#include "metingen.h"
#include "adc.h"
#include "controller_car.h"
#else
#include "soc_test.h"
#include <stdio.h>
#endif
#define MARGE 0.99

#ifndef TEST
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
#endif

int calculateStateofCharge(int* oldSoC, unsigned long *prevTime){
	
	// Definieer variabelen
	int current;
	int voltage;
	unsigned long currentTime;
	int timePeriod;
	int newStateofCharge;
	struct timeval tv;
	
	// Controle van de pointers
	if (oldSoC == NULL || prevTime == NULL) return -1;

	// Lees huidige spanning en stroom in
	// en bepaal de nieuwe som van stromen
	current = measureI();
	voltage = measureV();
#ifdef TEST
    printf("## SoC: Voltage = %d mV and total current = %d mA\n", voltage, current);
#endif
	// Lees huidige tijd in (milliseconden)
	gettimeofday(&tv,NULL);
	currentTime = tv.tv_sec * 1000 + tv.tv_usec/1000;

	// Bereken de periode tussen vorig en huidig sample
	// Omzetten van milliseconden naar uur (1/(1000*60*60)
	timePeriod = (int)(currentTime - *prevTime);
#ifdef TEST
	printf("Period: %d ms\n",timePeriod);
#endif
	// Initialisatie
	if (voltage > specs.volt_max_cell*specs.nr_of_cells*MARGE) {
	 	// Batterijspanning is aan threshold
		// batterij is volledig opgeladen
        // 99.999% = 99999
		newStateofCharge = 99999;
	}else if (voltage < specs.volt_min_cell*specs.nr_of_cells*(2-MARGE)){
		// Batterij staat op laagste spanning
        // 1% = 1000
		newStateofCharge = 1000;
	} else{
		// Bereken nieuwe SoC
        // used = I x dt [mA x ms]/3600 = [uAh]
        int used = (current*timePeriod)/(3600);
#ifdef TEST
        printf("Verbruik is %d uAh\n",used);
#endif
        // used * 100 => procent, x 1000 niet nodig, want in [uAh]
		newStateofCharge = *oldSoC + (used*100)/(specs.capacity);
	}

	// Update 'vorige' waarden
	*oldSoC = newStateofCharge;
	*prevTime = currentTime;
	return newStateofCharge;
}
