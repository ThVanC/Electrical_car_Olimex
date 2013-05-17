#include<stdio.h>
#include "controller_car.h"
#include "metingen.h"
#include "lader.h"
#include <unistd.h>

#ifndef CONTROLLER_CAR
#define CONTROLLER_CAR

/*******************

De waarden in controleer_car gaan initialiseren.

*******************/
void initCar(){
	voltage=0;			//De spanning over de batterij uitgedrukt in mV
	current=0;			//De gemetenstroom
	state_of_charge=0;	//De batterijstatus uitgedrukt in  1,000,000 x procent
	temperature=0;		//De temperatuur van de batterij
	max_temp=0;			//de default maximum temperatuur van de wagen
	load=0;
	work = wachten;
}

/*******************

De batterij specificatie gaan instellen.

*******************/
void initBatterySpecs(int nr_of_cells, int volt_max_cell, int volt_min_cell, int capacity){
    specs.capacity = capacity;
    specs.nr_of_cells = nr_of_cells;
    specs.volt_max_cell = volt_max_cell;
    specs.volt_min_cell = volt_min_cell;
}

/*******************

De huidige spanning over de batterij opvragen.

*******************/
int getVoltage(){
	return voltage;
}

/*******************

De huidige spanning over de batterij gaan instellen.

*******************/
void setVoltage(int i){
	voltage=i;
}

/*******************

De stroom die NU in/uit de batterij loop gaan opvragen.

*******************/
int getCurrent(){
    return current;
}

/*******************

De stroom die NU in/uit de batterij loop gaan instellen.

*******************/
void setCurrent(int i){
    current = i;
}

/*******************

De temperatuur van de batterij gaan opvragen.

*******************/
int getTemperature(){
	return temperature;
}

/*******************

De maximale temperatuur die de batterij mag hebben gaan instellen.

*******************/
int getMaxTemperature(){
	return max_temp;
}

/*******************

De load factor gaan opvragen.

*******************/
int getLoadFactor(){
	return load;
}

/*******************

De load factor gaan instellen.

*******************/
void setLoadFactor(int factor){
	load=factor;
}

/*******************

De SOC gaan opvragen.

*******************/
int getStateOfCharge(){
	return state_of_charge;
}

/*******************

De SOC gaan instellen.

*******************/
void setStateOfCharge(int i){
	state_of_charge=i;
}

time_t getTimeLimit(){
	return time;
}

time_t setTimeLimit(time_t t){
	time=t;
}

int getDistance(){
	return distance;
}

void setDistance(int i){
	distance=i;
}

int getMaxEnergyPerDistance(){
	return max_energy_per_distance;
}

void setMaxEnergyPerDistance(int i){
	max_energy_per_distance=i;
}

int getEnergy(){
	return energy;
}
void setEnergy(int i){
	energy=i;
}

int getCapacity(){
	return battery.capacity;
}

void setCapacity(int i){
	battery.capacity=i;
}

int getMaxLoad(){
	return max_load;
}

void setMaxLoad(int i){
	max_load=i;
}


/*******************

De temperatuur gaan instellen.

*******************/
void setTemperature(int i){
	temperature=i;
	if(i>max_temp){
		alarm(10);
		return;
	}
	if(i>0.9*max_temp){
		alarm(9);
		return;
	}
	if(i>0.8*max_temp){
		alarm(8);
		return;
	}
	if(i>0.7*max_temp){
		alarm(7);
		return;
	}
}

/*******************

De maximale temperatuur van de batterij gaan instellen.

*******************/
void setMaxTemperature(int i){
	max_temp = i;
}

/*******************

Afhankelijk van de meting, een alarm gaan oproepen. 
Elk alarm gaat een specifiek opdracht uitvoeren.

*******************/
void alarm(int code){
	//afhankelijk van de alarmcode (hoe dringend het is) moet er een functie worden opgeroepen die hierop anticipeerd.
	switch(code){
		//Bij code 10 moet alles direct afgelegd worden
		case 10: printf("groot alarm, Laurens, doe iets");break;
		//Bij code 9 moeten we mssn ook wel eens iets gaan doen
		case 9: printf("alarm, Zeger, doe iets");break;
		case 8: printf("Lap, Emmelie, t is omzeep");break;
		case 7: printf("Lap, Mathias, ge hebt een oneindige lus geprogrammeerd. please call me, number 101"); break;
	}
}

/************************

mutex gaan locken

************************/
void startConnecting(){
	pthread_mutex_lock (&connection);
}

/************************

mutex gaan unlocken

************************/
void stopConnecting(){
	 pthread_mutex_unlock (&connection);
}

/*******************

De bezigheid van de wagen instellen.
De mogelijkheden zijn:
	laden
	rijden 
	wachten

*******************/
void setWork(bezigheid b){
	work=b;
}

bezigheid getWork(){
	return work;
}

/*******************

testfunctie voor de controller_car.

*******************/
int testCC(){
    // Initialisatie
    initBatterySpecs(2, 4200, 3000, 2600);
    setBatterijType(LiPo);
    
    do {
        // Meet alle grootheden en update via setters
        
        // Meet spanning
        setVoltage(measureV());
        // Meet stroom
        setCurrent(measureI());
        // Meet State of Charge
        // Get en set in de functie
        updateStateOfCharge();
        // Meet temperatuur
        setTemperature(measureT())
        
        // Slaap 500ms vooraleer nieuwe meting te doen
        usleep(500*1000);
    } while (true);
}



#endif
