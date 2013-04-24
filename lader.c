#include "lader.h"
#include "metingen.h"
#include "gpio-mmap.h"
#include <stdio.h>
#include "NiMH.h"
#include "LiPo.h"
#include <math.h>
#include "controller_car.h"

int init(){
	gpio_output(DISCHARGE_BANK, DISCHARGE_PIN);
	gpio_output(ON_OFF_BANK, ON_OFF_PIN);
	turnOff();
	charge();
}

void turnOn(){
	GPIO_WRITE(ON_OFF_BANK, ON_OFF_PIN, 1);
	on = 1;
}

void turnOff(){
	GPIO_WRITE(ON_OFF_BANK, ON_OFF_PIN, 0);
	on = 0;
}

void charge(){
	GPIO_WRITE(DISCHARGE_BANK, DISCHARGE_PIN, 0);
	charging = 1;
	if(isOn()==1){
		/*We roepen meteen ook het laadalgoritme op zodat er zeker niet ongecontroleerd kan gebeuren. 
		We moeten voor zekerheid ook controleren dat de pcb niet aanstaat anders is het nutteloos van het oplaadalgoritme te laten rekenen.*/
		chargeAlgorithm();
	}
}

void discharge(){
	GPIO_WRITE(DISCHARGE_BANK, DISCHARGE_PIN, 1);
	charging = 0;
}

int isOn(){
	return on;
}

int isCharging(){
	return charging;
}


int setState(enum status new_state){
    if (new_state == status) return 1;
    // Huidige status bepaalt overgangsmethode
    switch (status) {
        case CHARGING:
            // Stel stroom in op 0A
            setCurrent(0);
            if (new_state == DISCHARGING) {
                // Ontkoppel de lader
                turnOff();
                // Schakel naar ontladen
                discharge();
                // Koppel lader
                turnOn();
                // Stel stroom in op gewenste waarde
                // TODO: gewenste stroom instellen
            }else if (new_state == USE){
                // Veilig ontkoppelen na opladen
                // Schakel naar ontladen
                discharge();
                // Ontkoppel de lader
                turnOff();
            }
            break;
        case DISCHARGING:
            // Stel stroom in op 0A
            setCurrent(0);
            // Ontkoppel de lader
            turnOff();
            if (new_state == CHARGING){
                // Schakel naar opladen
                charge();
                // Koppel de lader
                turnOn();
            }
            break;
        case USE:
            if (new_state == DISCHARGING) {
                // Schakel naar ontladen
                discharge();
                // Koppel de lader
                turnOn();
                // Stel stroom in
                // TODO: gewenste stroom instellen
            }else if (new_state == CHARGING){
                // Schakel naar opladen
                charge();
                // Koppel de lader
                turnOn();
                // Stel stroom in
                // TODO: gewenste stroom instellen
            }
            break;
        default:
            break;
    }
    return 0;
}

enum status getState(){
    return status;
}

void setCurrent(int i){
	current=i;
	convertCurrent();
	/*Hier moeten we ook de waarde in 1 keer doorsturen naar de comparator zodat die stroom aangepast wordt.*/
}

void convertCurrent(){
	//gebruik altijd een positieve stroom, op of ontladen is via relais 
	int V_ADC=0; //in mV
	int bits_geheel;
	int V_bit=(int)5000.0/(pow(2.0,12));//in mV

	//spanning in mV
	V_ADC=2500+(int)(current*0.1);
	bits_geheel=V_ADC/V_bit;

	//bits_geheel moet nog omgezet worden naar een bitrij
	//deze bitrij moeten we dan ofwel als output geven ofwel onder een variabele steken in het h-bestand
}


// Update de SoC
void updateStateofCharge(){
	// Bereken SoC
    int soc = getStateOfCharge();
	calculateStateofCharge(&soc, &timeOfMeasurement);
	// Update de waarde in controller (?)
	setStateOfCharge(soc);
}


// Controleer of de batterij aan zijn limiet is
int isAtChargeLimit(int load){
	if(getStateOfCharge() < load) return 0;
	else return 1;
}


void setBatterijType(int v){
	batterij_type = (enum type_batterij)(v);
}


/*****************************************************

!!!!Vergeet die output niet vrij te geven als we het niet langer nodig hebben!!!

*****************************************************/
char* getBatterijType(){
	char* output = (char*)malloc(5*sizeof(char));
	switch(batterij_type){
		case 0:
			output = "LiPo";
			break;
		case 1:
			output = "NiMH";
			break;
		default:
			output = (char*)realloc(output,14*sizeof(char));
			output="Ongeldig type";
			break;
	}
	return output;
}

void chargeAlgorithm(){
	switch(batterij_type){
		case LiPo:
			charge_LiPo(&specs, load);
			break;
		case NiMH:
			charge_NiMH();
			break;
		default:
			printf("You have to configure your battery type!\n");
	}
}
