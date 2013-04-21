//
//  gps_test.c
//  Electrical_Car_Olimex
//
//  Created by Zeger Van de Vannet on 20/04/13.
//  Copyright (c) 2013 Zeger Van de Vannet. All rights reserved.
//

#define TESTMODE

#include <stdio.h>
#include "GPS.h"

int main(int argc, char** args){
    printf("Initialize GPS DATA\n\n");
    initGPS();
    printf("Seed with random GPS DATA points\n");
    downloadGPS();
    printf("Run the track\n\n");
    followTrack();
    printf("## You have reached your final destination! ##\n");
    printf("Total distance covered: %d m\n", totalDistance);
    destroyGPS();
    printf("Cleaned up!\n");
    return 0;
}


