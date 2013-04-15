#ifndef NiMH_H
#define NiMH_H

#define C 1800 // C in mAh
int V_max; //in mV de maximale spanning in deze sessie
//DON'T FORGET: init_V_max voor elke oplaadsessie !!!

void init_V_max();
void charge_NiMH();

#endif

