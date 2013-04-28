#ifndef CONTROLLER_CAR_H
#define CONTROLLER_CAR_H

// BATTERIJEIGENSCHAPPEN
typedef struct{
    int nr_of_cells;    // Aantal cellen in parallel
    int volt_max_cell;  // Maximale spanning per cel, V_threshold (mV)
    int volt_min_cell;  // Minimale spanning per cel (mV)
    int capacity;       // Capaciteit van batterij (mAh)
} battery;

<<<<<<< HEAD
enum werk {
	laden, 
	rijden, 
	wachten
} bezigheid;


=======
>>>>>>> 83841f34cbb827163b7eac4b4807bd38a35a2112
battery specs;

enum buzy{
    LOAD,
    DRIVE,
    SLEEP
};

void initBatterySpecs(int nr_of_cells, int volt_max_cell, int volt_min_cell, int capacity);

int voltage;//De spanning over de batterij uitgedrukt in mV
int state_of_charge;//De batterijstatus uitgedrukt in  1,000,000 x procent
int temperature;
int max_temp=50;//de default maximum temperatuur van de wagen
int load=0; //Deze waarde is een indicatie van hoe sterk de wagen mag opladen, als deze waarde positief is gaat de wagen opladen, anders ontladen. Uitgedrukt in milliwatt?
<<<<<<< HEAD
bezigheid work;
=======
enum buzy work = SLEEP;
>>>>>>> 83841f34cbb827163b7eac4b4807bd38a35a2112
pthread_mutex_t connection = PTHREAD_MUTEX_INITIALIZER;

int getVoltage();
void setVoltage(int i);

int getTemperature();
void setTemperature(int i);
void setMaxTemperature(int i);

int getLoadFactor();
void setLoadFactor(int factor);

int getStateOfCharge();
void setStateOfCharge(int i);

void alarm(int code);

void startLoading();
void startDriving();
void startSleeping();
<<<<<<< HEAD
bezigheid getWork();
void setWork(bezigheid b);
void startConnecting();
void stopConnecting();

=======
enum buzy getWork();
int connect();
>>>>>>> 83841f34cbb827163b7eac4b4807bd38a35a2112




#endif
