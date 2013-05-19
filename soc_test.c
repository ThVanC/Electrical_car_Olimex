//
//  soc_test.c
//  Electrical_Car_Olimex
//
//  Created by Zeger Van de Vannet on 21/04/13.
//  Copyright (c) 2013 Zeger Van de Vannet. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "soc_test.h"
#include "metingen.h"
#include "controller_car.h"

/***************************

De spanning meten.
Dit is een dummiefunctie die gewoon een waarde aanlegt om de test te kunnen laten lopen. We laten de spanning toch een beetje varieren om in de verschillende stadia van het proces te komen.

***************************/
int measureV(){
    if (now - start_time < 1000){
        return 8400;
    }else if (now - start_time < 13000){
        return 7400;
    }else{
        return 6000;
    }
    
}

/***************************

De stroom meten.
Dit is een dummiefunctie die gewoon een waarde aanlegt om de test te kunnen laten lopen.

***************************/
int measureI(){
    return -1000; // 1A afname
}


/******************************

Dit is een losstaand programma om de SOC logica te gaan testen.

******************************/
int main(int argc, char** argv){
    struct timeval tv, timer;
    int current, voltage, sum;
    
	//de tijd goed instellen.
    printf("Initialize time...\n");
    gettimeofday(&tv, NULL);
    start_time = tv.tv_sec*1000 + tv.tv_usec/1000;
    printf("Start time is %ld ms\n",start_time);
    
	//we stellen een batterij met willekeurig gekozen waarden in.
    printf("Initialize battery specs...\n");
    specs.capacity = 2600;
    specs.nr_of_cells = 2;
    specs.volt_max_cell = 4200;
    specs.volt_min_cell = 3000;
    
    now = start_time;
    sum = 0;
    
	//we gaan het programma gedurende een tijd van 14000 laten werken
    do {
        int soc;
        current = measureI();
        voltage = measureV();
        soc = calculateStateofCharge(&sum, &now);
        printf("%ld ms past start ",now-start_time);
        printf("SoC is %f\n",soc/1000000.0);
        gettimeofday(&timer, NULL);
        now = timer.tv_sec*1000 + tv.tv_usec/1000;
        usleep(500*1000);
    } while (now - start_time < 14000);
    
    return 0;
}

