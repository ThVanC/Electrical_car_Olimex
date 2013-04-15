#include "lader.h"
#include "gpio-mmap.h"
#include <stdio.h>
#include "NiMH.h"
#include "LiPo.h"
#include <math.h>

int init(){
	gpio_output(2,27);
	gpio_output(2,28);
	turnOff();
	charge();
}

void turnOn(){
	GPIO_WRITE(2,28, 1);
	on = 1;
}

void turnOff(){
	GPIO_WRITE(2,28, 0);
	on = 0;
}

int charge(){
	GPIO_WRITE(2,27, 0);
	charging = 1;
}

int discharge(){
	GPIO_WRITE(2,27, 1);
	charging = 0;
}

int isOn(){
	return on;
}

int isCharging(){
	return charging;
}

void setCurrent(int i){
	current=i;
}

void convertCurrent(){
	//gebruik altijd een positieve stroom, op of ontladen is via relais 
	float V_ADC=0.0; //in mV
	int bits_geheel;
	float V_bit=5000.0/(pow(2.0,12));//in mV

	//spanning in mV
	V_ADC=2500+(current*0.1);
	bits_geheel=V_ADC/V_bit;

	//bits_geheel moet nog omgezet worden naar een bitrij
	//deze bitrij moeten we dan ofwel als output geven ofwel onder een variabele steken in het h-bestand
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
			charge_LiPo();
			break;
		case NiMH:
			charge_NiMH();
			break;
		default:
			printf("You have to configure your battery type!\n");
	}
}
