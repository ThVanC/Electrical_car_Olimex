#include<stdio.h>
#include "controller_car.h"

#ifndef CONTROLLER_CAR
#define CONTROLLER_CAR

void initBatterySpecs(int nr_of_cells, int volt_max_cell, int volt_min_cell, int capacity){
    specs.capacity = capacity;
    specs.nr_of_cells = nr_of_cells;
    specs.volt_max_cell = volt_max_cell;
    specs.volt_min_cell = volt_min_cell;
}

int getVoltage(){
	return voltage;
}
void setVoltage(int i){
	voltage=i;
}

int getTemperature(){
	return temperature;
}

int getLoadFactor(){
	return load;
}

int setLoadFactor(int factor){
	load=factor;
}

int getStateOfCharge(){
	return state_of_charge;
}

void setStateOfCharge(int i){
	state_of_charge=i;
}

time_t getTime(){
	return time;
}

time_t setTime(time_t t){
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
	return capacity;
}

void setCapacity(int i){
	capacity=i;
}

int getMaxLoad(){
	return max_load;
}

void setMaxLoad(int i){
	max_load=i;
}

int getMaxUnload(){
	return max_unload;
}
void setMaxUnload(int i){
	max_unload=i;
}


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

void startConnecting(){
    pthread_mutex_unlock (&connection);
}
void stopConnecting(){
	pthread_mutex_lock (&connection);
}

void setWork(bezigheid b){
	work=b;
}

bezigheid getWork(){
	return work;
}



#endif
