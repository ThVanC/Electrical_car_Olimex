#include "lader.h"
#include "metingen.h"
#include "gpio_map.h"
#include <stdio.h>
#include "NiMH.h"
#include "LiPo.h"
#include <math.h>
#include "controller_car.h"
#include "i2c.h"
#include "pin_config.h"

#define MINMARGE 0.1

/*******************

initialiseren van de constanten uit lader.h

*******************/
void init(){
	gpio_map();
	printf("We zijn in de lader.c\n");
	gpio_output(DISCHARGE_BANK, DISCHARGE_PIN);
	printf("lader1\n");
	gpio_output(ON_OFF_BANK, ON_OFF_PIN);
	printf("lader2\n");
	turnOff();
	printf("lader3\n");
	charge();
	printf("lader4\n");
		currentCharger=0; //uitgedrukt in mA
		printf("lader5\n");
//On: 1, off: 0
	on=0;
//Charging: 1, discharging: 0
	charging=1;

// Variabelen voor State of Charge
	integratedCurrent=0; // Accumulatie van vorige stromen
	printf("lader6\n");
	timeOfMeasurement=0;

//Lipo: 0, NiMH: 1
	batterij_type = LiPo;

// Toestanden voor relay-standen
	status = USE;
	printf("lader7\n");
}

/*******************

PCB aanzetten

*******************/
void turnOn(){
	GPIO_WRITE(ON_OFF_BANK, ON_OFF_PIN, 1);
	on = 1;
}

/*******************

PCB afzetten

*******************/
void turnOff(){
	GPIO_WRITE(ON_OFF_BANK, ON_OFF_PIN, 0);
	on = 0;
}

/*******************

PCB in laadmodus zetten

*******************/
void charge(){
	GPIO_WRITE(DISCHARGE_BANK, DISCHARGE_PIN, 0);
	charging = 1;
	//if(isOn()==1){
		/*We roepen meteen ook het laadalgoritme op zodat er zeker niet ongecontroleerd kan gebeuren. 
		We moeten voor zekerheid ook controleren dat de pcb niet aanstaat anders is het nutteloos van het oplaadalgoritme te laten rekenen.*/
		//chargeAlgorithm();
	//}
}

/*******************

PCB in ontlaadmodus zetten

*******************/
void discharge(){
	GPIO_WRITE(DISCHARGE_BANK, DISCHARGE_PIN, 1);
	charging = 0;
}

/*******************

Staat de PCB aan?

*******************/
int isOn(){
	return on;
}

/*******************

Staat de PCB in laadmodus?

*******************/
int isCharging(){
	return charging;
}

/*******************

Verander de status van de lader. Deze functie moet gebruikt worden aangezien bepaalde combinaties van relaystanden niet goed zijn voor de batterij
mogelijke status:   USE
					CHARGING
					DISCHARGING

*******************/
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
                //instellen van de stroom
				setCurrentCharger(0);
				usleep(3000000);
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
    status=new_state;
    return 0;
}

/*******************

Geef de status van de lader terug

*******************/
enum status getState(){
    return status;
}

/*******************

Stel de stroom in van de PCB
De stroom moet eerst omgezetten in een spanning dmv convertCurrent

*******************/
void setCurrentCharger(int i){
        int voltage_dac;
        currentCharger=i;
        if (currentCharger == 0) {
                i2c_shutdown_DAC();
        } else{
	        voltage_dac = convertCurrent();
                i2c_write_DAC(voltage_dac);
        }
}

/*******************
 
omzetting stroom in spanning voor de DAC

*******************/
int convertCurrent(){
	// Gebruik altijd een positieve stroom, 
        // op of ontladen is via relais 
	return ((2500 + 0.1*currentCharger)*4096)/ VDD;
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

/*******************

Batterij type aanpassen. Momenteel is dat LiPo of NiMH.

*******************/
void setBatterijType(enum type_batterij v){
	batterij_type = v;
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

/*******************

Uitvoeren van het algoritme dat bij de batterij hoort.

*******************/
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

void dischargeAlgorthm(){
	while(getLoadFactor() < 0 && getStateOfCharge() > (specs.volt_max_cell*specs.nr_of_cells)*MINMARGE){
		setLEDS(-1*getLoadFactor());

		// Stel de stroom in op 1 x C
		current = 1*specs.capacity;
		setCurrentCharger(-1*getLoadFactor());
		usleep(3000000);//we slapen drie seconden
	}
}


