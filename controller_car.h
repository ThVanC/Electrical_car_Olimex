#ifndef CONTROLLER_CAR_H
#define CONTROLLER_CAR_H

// BATTERIJEIGENSCHAPPEN
typedef struct{
    int nr_of_cells;    // Aantal cellen in parallel
    int volt_max_cell;  // Maximale spanning per cel, V_threshold (mV)
    int volt_min_cell;  // Minimale spanning per cel (mV)
    int capacity;       // Capaciteit van batterij (mAh)
} battery;

battery specs;

void initBatterySpecs(int nr_of_cells, int volt_max_cell, int volt_min_cell, int capacity);

int voltage;//De spanning over de batterij uitgedrukt in mV
int state_of_charge;//De batterijstatus uitgedrukt in  100 x procent
int temperature;
int max_temp=50;//de default maximum temperatuur van de wagen
int load=0; //Deze waarde is een indicatie van hoe sterk de wagen mag opladen, als deze waarde positief is gaat de wagen opladen, anders ontladen. Uitgedrukt in milliwatt?

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

#endif
