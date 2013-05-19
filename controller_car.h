#ifndef CONTROLLER_CAR_H
#define CONTROLLER_CAR_H
#include <pthread.h>
// BATTERIJEIGENSCHAPPEN
typedef struct{
    int nr_of_cells;    // Aantal cellen in parallel
    int volt_max_cell;  // Maximale spanning per cel, V_threshold (mV)
    int volt_min_cell;  // Minimale spanning per cel (mV)
    int capacity;       // Capaciteit van batterij (mAh)
} battery;


typedef enum werk {
	laden, 
	rijden, 
	wachten
} bezigheid;


battery specs;


void initBatterySpecs(int nr_of_cells, int volt_max_cell, int volt_min_cell, int capacity);

int voltage;			//De spanning over de batterij uitgedrukt in mV
int current;			//De gemetenstroom
int state_of_charge;	//De batterijstatus uitgedrukt in  1,000,000 x procent
int temperature;		//De temperatuur van de batterij
int max_temp;			//de default maximum temperatuur van de wagen
int load;				//Deze waarde is een indicatie van hoe sterk de wagen mag opladen, als deze waarde positief is gaat de wagen opladen, anders ontladen. Uitgedrukt in milliwatt?

bezigheid work;


void initCar();

extern pthread_mutex_t connection;
extern pthread_mutex_t emergency;

/* Getters en Setters voor Spanning, Stroom, SoC en Temperatuur */
int getVoltage();
void setVoltage(int i);

int getCurrent();
void setCurrent(int i);

int getTemperature();
void setTemperature(int i);

int getMaxTemperature();
void setMaxTemperature(int i);

int getLoadFactor();
void setLoadFactor(int factor);

int getStateOfCharge();
void setStateOfCharge(int i);


void alarmF(int code);

void startLoading();
void startDriving();
void startSleeping();

bezigheid getWork();
void setWork(bezigheid b);
void startConnecting();
void waitConnecting();
void emergencyStop();
void emergencyStart();

int connect();





#endif
