#include "gpio-mmap.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <unistd.h>
#include <sched.h>
#include "imx233.h";

#ifndef MAIN
#define MAIN

//using namespace std;
int fun(){
	int i;
	gpio_output(0, 0);
	gpio_output(0, 1);
	gpio_output(0, 2);
	gpio_output(0, 3);
	gpio_output(0, 4);
	gpio_output(0, 5);
	gpio_output(0, 6);
	gpio_output(0, 7);
	gpio_output(1, 19);
	gpio_output(1, 20);
	gpio_output(1, 21);
	gpio_output(0, 23);
	gpio_output(0, 25);
	gpio_output(2, 27);
	gpio_output(2, 28);
	
	

	//gpio_output(1, 0);
	//gpio_output(1, 23);
	//gpio_output(1, 24);
	GPIO_WRITE(0,0,0);
	GPIO_WRITE(0,1,0);
	GPIO_WRITE(0,2,0);
	GPIO_WRITE(0,3,0);
	GPIO_WRITE(0,4,0);
	GPIO_WRITE(0,5,0);
	GPIO_WRITE(0,6,0);
	GPIO_WRITE(0,7,0);
	GPIO_WRITE(1,19,0);
	GPIO_WRITE(1,20,0);
	GPIO_WRITE(1,21,0);
	GPIO_WRITE(0,23,0);
	GPIO_WRITE(0,25,0);
	GPIO_WRITE(2,27,0);
	GPIO_WRITE(2,28,0);

	for(i=0;i<10;i++){
		GPIO_WRITE(0,7,0);
		usleep(10000);
		GPIO_WRITE(0,6,1);
		usleep(10000);
		GPIO_WRITE(0,5,1);
		usleep(10000);
		GPIO_WRITE(0,5,1);
		usleep(10000);
		GPIO_WRITE(0,3,1);
		usleep(10000);
		GPIO_WRITE(0,2,1);
		usleep(10000);
		GPIO_WRITE(0,1,1);
		usleep(10000);
		GPIO_WRITE(0,0,1);
		usleep(10000);
		GPIO_WRITE(1,19,1);
		usleep(10000);
		GPIO_WRITE(1,20,1);
		usleep(10000);
		GPIO_WRITE(1,21,1);
		usleep(10000);
		GPIO_WRITE(0,23,1);
		usleep(10000);
		GPIO_WRITE(0,25,1);
		usleep(10000);
		GPIO_WRITE(2,27,1);
		usleep(10000);
		GPIO_WRITE(2,28,1);
		usleep(10000);
		GPIO_WRITE(1,0,1);

		GPIO_WRITE(0,7,0);
		usleep(10000);
		GPIO_WRITE(0,6,0);
		usleep(10000);
		GPIO_WRITE(0,5,0);
		usleep(10000);
		GPIO_WRITE(0,4,0);
		usleep(10000);
		GPIO_WRITE(0,3,0);
		usleep(10000);
		GPIO_WRITE(0,2,0);
		usleep(10000);
		GPIO_WRITE(0,1,0);
		usleep(10000);
		GPIO_WRITE(0,0,0);
		usleep(10000);
		GPIO_WRITE(1,19,0);
		usleep(10000);
		GPIO_WRITE(1,20,0);
		usleep(10000);
		GPIO_WRITE(1,21,0);
		usleep(10000);
		GPIO_WRITE(0,23,0);
		usleep(10000);
		GPIO_WRITE(0,25,0);
		usleep(10000);
		GPIO_WRITE(2,27,0);
		usleep(10000);
		GPIO_WRITE(2,28,0);
		usleep(10000);
		GPIO_WRITE(1,0,1);
	}
}

int test(){
	gpio_output(1,0);
	GPIO_WRITE_PIN(32,1);
	usleep(200000);
	GPIO_WRITE_PIN(32,0);
	return 0;
}

int gpioTest(){
	int pin30 = 27;
	int pin31 = 28;
	int i, j;

	gpio_map();

	gpio_mmap[HW_PINCTRL_MUXSEL3_CLR>>5]=0x00f00000;
	gpio_mmap[HW_PWM_ACTIVE1>>5]=0x012c0000;
	gpio_mmap[HW_PWM_PERIOD1>>5]=0x000b04b0;
	gpio_mmap[HW_PWM_CTRL_SET>>5]=0x06000003;

	test();



}

#endif