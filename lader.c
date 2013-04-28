#include "lader.h"
#include "metingen.h"
#include "gpio-mmap.h"
#include <stdio.h>
#include "NiMH.h"
#include "LiPo.h"
#include <math.h>
#include "controller_car.h"
#include "i2c.h"

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
        int voltage_dac;
	current=i;
        if (current == 0) {
                i2c_shutdown_DAC();
        } else{
	        voltage_dac = convertCurrent();
                i2c_write_DAC(voltage_dac);
        }
}

int convertCurrent(){
	// Gebruik altijd een positieve stroom, 
        // op of ontladen is via relais 
	return ((2500 + 0.3*current)*4096)/ VDD;
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
			charge_NiMH(load);
			break;
		default:
			printf("You have to configure your battery type!\n");
	}
}
