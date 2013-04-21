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
	int max_speed;          // Snelheid in m/s = mm/ms
	enum direction dir;
	int distance;           // afstand in mm
} GPS_node;

int aantal_nodes;
int nodeNumber;
GPS_node* track;
int totalDistance;  // Totale afstand per run in meter

// Initialiseer de GPS waarden
void initGPS();
// Verwijder de GPS waarden
void destroyGPS();

void downloadGPS();
GPS_node* getTrack();
void followTrack();

// Bereken de tijd nodig om een afstand aan een bepaalde snelheid af te leggen
// distance in cm, speed in cm/ms
// return in ms
int calculateTime(int distance, int speed);


/* Test en demo functies */

void generateGPSData(int nodes);


#endif
