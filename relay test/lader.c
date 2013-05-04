#include "lader.h"
#include "gpio-mmap.h"
#include <stdio.h>
#include <math.h>


int init(){
	gpio_map();
	gpio_output(DISCHARGE_BANK, DISCHARGE_PIN);
	gpio_output(ON_OFF_BANK, ON_OFF_PIN);
	turnOff();
	charge();
	return 0;
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