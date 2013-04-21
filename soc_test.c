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


int measureV(){
    if (now - start_time < 1000){
        return 8400;
    }else if (now - start_time < 13000){
        return 7400;
    }else{
        return 6000;
    }
    
}

int measureI(){
    return -1000; // 1A afname
}

int main(int argc, char** argv){
    struct timeval tv, timer;
    int current, voltage, sum;
    
    printf("Initialize time...\n");
    gettimeofday(&tv, NULL);
    start_time = tv.tv_sec*1000 + tv.tv_usec/1000;
    printf("Start time is %ld ms\n",start_time);
    
    printf("Initialize battery specs...\n");
    specs.capacity = 2600;
    specs.nr_of_cells = 2;
    specs.volt_max_cell = 4200;
    specs.volt_min_cell = 3000;
    
    now = start_time;
    sum = 0;
    
    do {
        int soc;
        current = measureI();
        voltage = measureV();
        soc = calculateStateofCharge(&sum, &now);
        printf("%ld ms past start ",now-start_time);
        printf("SoC is %f\n",soc/1000.0);
        gettimeofday(&timer, NULL);
        now = timer.tv_sec*1000 + tv.tv_usec/1000;
        usleep(5000*1000);
    } while (now - start_time < 14000);
    
    return 0;
}

