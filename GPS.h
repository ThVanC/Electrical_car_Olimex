#ifndef GPS_H
#define GPS_H
#include <sys/time.h>


enum direction{
    forward,
    left,
    right,
    backward,
    standstill      // Sta stil voor distance/speed ms
};

typedef struct{
	int max_speed;          // Snelheid in cm/ms
	enum direction dir;
	int distance;           // afstand in cm
} GPS_node;

int aantal_nodes;
int nodeNumber;
GPS_node* track;
int totalDistance;  // Totale afstand per run in meter

void initGPS();
void downloadGPS();
GPS_node* getTrack();
void followTrack();

    // Bereken de tijd nodig om een afstand aan een bepaalde snelheid af te leggen
    // distance in cm, speed in cm/ms
    // return in ms
int calculateTime(int distance, int speed);

    // Stel de sleeptime in
void setTimespec(struct timespec* duration, int millisec);

/* Test en demo functies */

void generateGPSData(int nodes);


#endif
