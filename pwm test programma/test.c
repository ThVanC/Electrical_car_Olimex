#include "drive.h"
#include <stdio.h>


int main(){
	int i;
	initDrive();
	usleep(20000);
	forward();
	printf("speed starten\n");
	/*for(i=0;i<21;i++){
		speed(i);
		usleep(20000);
	}*/
	speed(0);
	//gpio_test();
}