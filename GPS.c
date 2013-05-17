//#define TESTMODE

#include "GPS.h"
#ifndef TESTMODE
#include "drive.h"
#include "controller_car.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*******************

initialiseren van de constanten uit GPS.h

*******************/
void initGPS(){
#ifndef TESTMODE
    initDrive();
#endif
    aantal_nodes=0;
    nodeNumber=0;
    totalDistance = 0;
    track = (GPS_node*)malloc(aantal_nodes*sizeof(GPS_node));
}

/*******************

Een gps-track vrijgegeven

*******************/
void destroyGPS(){
    free(track);
}

/*******************

Een gps track afleggen: elke node overlopen.

*******************/
void followTrack(){
    int millisec = 0;
    for(nodeNumber=0; nodeNumber<aantal_nodes; nodeNumber++){
        
        // Stel de holdtime in
        millisec = calculateTime(track[nodeNumber].distance,track[nodeNumber].max_speed );
        
        /*Richtingsaanwijzer*/
        switch(track[nodeNumber].dir){
            case forward:
//#ifdef TESTMODE
                printf("Move forward\n");
//#else
                moveForward();
//#endif
                break;
            case left:
//#ifdef TESTMODE
                printf("Turn left\n");
//#else
                moveLeft();
//#endif
                break;
            case right:
//#ifdef TESTMODE
                printf("Turn right\n");
//#else
                moveRight();
//#endif
                break;
            case backward:
//#ifdef TESTMODE
                printf("Reverse\n");
//#else  
                moveForward();
				speed(-1);
//#endif
                break;
            default:
//#ifdef TESTMODE
                printf("Default: Stand still\n");
//#else
				moveForward();
				speed(0);
//#endif
        }

#ifndef TESTMODE
        /*Snelheidsaanduider*/
        speed(track[nodeNumber].max_speed);
		printf("De snelheid is %d\t%d\n",track[nodeNumber].max_speed,nodeNumber);
#endif
        /*Kilometerteller*/
        totalDistance += (int)(track[nodeNumber].distance/1000);
		state_of_charge -= specs.capacity/100;
#ifdef TESTMODE
        printf("Drive %d m at %d m/s = %d ms\n\n",track[nodeNumber].distance/1000, track[nodeNumber].max_speed, calculateTime(track[nodeNumber].distance, track[nodeNumber].max_speed));
#endif
        
        // Stop de lus voor de bepaalde tijd
        usleep(millisec*1000);
    }
}

/*******************

De track inladen

*******************/
void downloadGPS(){
    // Genereer random GPS data
    generateGPSData(20);

}

/*******************

De track opvragen

*******************/
GPS_node* getTrack(){
    return track;
}

/*******************

Bepalen hoe lang de wagen erover doet om de bepaalde afstand af te leggen.

*******************/
int calculateTime(int distance, int speed){
	int time;
	time = 	(int)(distance / speed);
	return time;
}

/*******************

At random een GPS-track genereren.

*******************/
void generateGPSData(int nodes){
    int i = 0;
    aantal_nodes = nodes;
    track = (GPS_node*)realloc(track, nodes);
    for(i = 0; i < nodes; i++){
        track[i].dir = rand() % 5;
        track[i].distance = (rand() % 10000)+1; // maximaal 10m
        track[i].max_speed = (rand() % 20)+1; // = 1 m/s = 3.6km/h
#ifdef TESTMODE
        printf("%d: Node set for distance: %d mm\n",i,track[i].distance);
#endif
    }
}

