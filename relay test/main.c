#include "lader.h"
#include <stdio.h>

int main(){
	init();
	printf("Initialized\n");
	turnOff();
	charge();
	usleep(2000000);
	turnOn();
	printf("ON\n");
	usleep(2000000);
	charge();
	printf("Charging\n");
	usleep(2000000);
	turnOff();
	printf("OFF\n");
	usleep(2000000);
	discharge();
	printf("Discharging\n");
	usleep(2000000);
	printf("End of the program.\n");
}