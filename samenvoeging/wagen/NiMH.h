#ifndef NiMH_H
#define NiMH_H

#define C 1800 // C in mAh
int V_max; //in mV de maximale spanning in deze sessie
//DON'T FORGET: init_V_max voor elke oplaadsessie !!!

void init_V_max();

// return: 2 opladen gestopt omdat SoC (<100) is bereikt
// return: 1 als opladen voltooid is.
// return: 0 voor charging == 0 of laden == off
int charge_NiMH(int socLoad);

#endif

