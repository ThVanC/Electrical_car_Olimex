// #define TEST
#include <sys/time.h>
#ifndef TEST
#include "metingen.h"
#include "adc.h"
//#include "i2c.h"
#include "controller_car.h"
#include "lader.h"
#else
#include "soc_test.h"
#include <stdio.h>
#endif
#define MARGE 0.99
#define TEMP_FRAC 125

#ifndef TEST
int initMeasurements(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	now = tv.tv_sec*1000 + tv.tv_usec/1000;
	sum = 0;
	initLRADC0();
	initLRADC1();
	//klopt het dat we voor i�c niets moeten initialiseren
}

int measureV(){
	int V_LRADC1,V_bat;//spanningen in mV

	V_LRADC1=convertToVoltage(readLRADC1());
	V_bat=(V_LRADC1*(R4 + R5)) / R5; //236 owv 56+180 ; haakjes zo zetten zal best nauwkeurigheid geven

	return V_bat;
}

// Bereken de stroom
// Positief is naar de batterij
// negatief weg van de batterij
int measureI(){
	int V_LRADC0,V_Hall;//spanningen in mV
	int curr;//stromen in mA

	//if (getState() == CHARGING) {
	if(getState() == CHARGING){
		// Bij opladen is de stroom in de batterij gelijk aan de stroom uit de lader
		// De rest van de schakeling wordt gevoed door de externe voeding
		return currentCharger;
	}else {
		V_LRADC0=convertToVoltage(readLRADC0());
		V_Hall=(V_LRADC0*(R6 + R3)) / R6;

		curr=(V_Hall)*10; //want 100mV/A => 10mA/mV

		if (getState() == DISCHARGING) {
			// Bij ontladen vloeit de ingestelde stroom weg uit de batterij
			// En een deel via de Hall sensor naar het circuit
			return currentCharger + curr;
		}else {
			// Alle stroom wordt onttrokken door het circuit
			return curr;
		}

	}
}


/*int measureT(){
    unsigned char msbyte, lsbyte;
    int raw_temp;
    i2c_read_temp(&msbyte, &lsbyte);
    // Kap 5 lsb van LSByte af en tel op bij MSByte die 3 bits verschoven is
    // AND om carry in 12e bit te verwijderen
    raw_temp = ((lsbyte >> 5) + (msbyte << 3)) & 0x7FF;

    // Test 11e bit
    if ((raw_temp & 0x400) != 0){
        // 11e bit is 1 => negatieve temperatuur
        return (raw_temp - 0x800)*TEMP_FRAC;
    } else{
        // 11e bit is 0 => positieve temperatuur
        return (raw_temp)*TEMP_FRAC;
    }

}*/
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
	voltage = getVoltage();
	current = getCurrent();

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
		// 99.999% = 99,999,999
		newStateofCharge = 99999999;
	}else if (voltage < specs.volt_min_cell*specs.nr_of_cells*(2-MARGE)){
		// Batterij staat op laagste spanning
		// 1% = 1,000,000
		newStateofCharge = 1000000;
	} else{
		// Bereken nieuwe SoC
		// used = I x dt [mA x ms]/3600 = [uAh]
		int used = (current*timePeriod*1000)/(3600);
#ifdef TEST
		printf("Verbruik is %d mAh\n",used);
#endif
		// used * 100 => procent, x 1000 niet nodig, want in [uAh]
		newStateofCharge = *oldSoC + (used*100)/(specs.capacity);
	}

	// Update 'vorige' waarden
	*oldSoC = newStateofCharge;
	*prevTime = currentTime;
	return newStateofCharge;
}

void manageMeasurements(){
	setVoltage(measureV());
	setCurrent(measureI());
	state_of_charge = calculateStateofCharge(&sum, &now);
}

void manageStateOfCharge(){
	state_of_charge = calculateStateofCharge(&sum, &now);
}


void measurementsThr(){
	int i;
	//at random wat waarden meegegeven. Deze moeten voor een batterij aangepast worden!
	printf("De metingen zijn begonnen \n");
	initBatterySpecs(5,4000,200,2000);

	initMeasurements();
	manageMeasurements();
	printf("V: %d\nI: %d\nT: %d\nMT: %d\nLF: %d\nSOC: %d\nBuzy: %d\n",
			getVoltage(),
			getCurrent(),
			getTemperature(),
			getMaxTemperature(),
			getLoadFactor(),
			getStateOfCharge(),
			getWork());
	printf("load: %i\n",getLoadFactor());

	printf("einde van de measurementsThr\n");
}
