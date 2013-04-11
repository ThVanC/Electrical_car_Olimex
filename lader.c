#include "lader.h"
#include "gpio-mmap.h"
#include <stdio.h>
#include "NiMH.h"
#include "LiPo.h"

int init(){
	gpio_output(2,27);
	gpio_output(2,28);
	turnOff();
	Charge();
}

void turnOn(){
	GPIO_WRITE(2,28, 1);
	on = 1;
}

void turnOff(){
	GPIO_WRITE(2,28, 0);
	on = 0;
}

int Charge(){
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
	//hier wachten we nog even mee.
	//de stroom moet hier omgezet worden naar een spanning en deze spanning moet omgezet worden in een bitrij. 
	//Die bitrij sturen we via i²c door naar onze DAC. MCP4725
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

void Charge_algorithm(){
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