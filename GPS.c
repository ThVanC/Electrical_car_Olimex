#include "GPS.h"
#include "drive.h"
#include <sys/time.h>
#include <stdlib.h>

void initGPS(){
    initDrive();
    aantal_nodes=0;
    nodeNumber=0;
    totalDistance = 0;
    track = (GPS_node*)malloc(aantal_nodes*sizeof(GPS_node));
}

void followTrack(){
    struct timespec dur;
    for(nodeNumber=0; nodeNumber<aantal_nodes; nodeNumber++){
        
        // Stel de holdtime in
        setTimespec(&dur, calculateTime(track[nodeNumber].distance,track[nodeNumber].max_speed ));
        
        /*Richtingsaanwijzer*/
        switch(track[nodeNumber].dir){
            case forward:
                moveForward();
                break;
            case left:
                moveLeft();
                break;
            case right:
                moveRight();
                break;
            default:
                moveForward();
        }
    
        /*Snelheidsaanduider*/
        speed(track[nodeNumber].max_speed);
    
        /*Kilometerteller*/
        totalDistance += track[nodeNumber].distance / 100000;
        
        
        // Stop de lus voor de bepaalde tijd
        nanosleep(&dur, (struct timespec *) NULL);

    }
}

void downloadGPS(){
    // Genereer random GPS data
    generateGPSData(20);
}

GPS_node* getTrack(){
    return track;
}


int calculateTime(int distance, int speed){
	int time;
	time = 	distance / speed;
	return time;
}

void setTimespec(struct timespec* spec, int millisec){
    spec->tv_sec = millisec/1000;
    spec->tv_nsec = (millisec - (spec->tv_sec)) * 1000000L;
}


void generateGPSData(int nodes){
    int i = 0;
    aantal_nodes = nodes;
    track = (GPS_node*)realloc(track, nodes);
    for(i = 0; i < nodes; i++){
        track[i].dir = direction(rand() % 4);
        track[i].distance = rand() % 10000; // maximaal 100m
        track[i].max_speed = 1; // = 10 m/s
    }
}

