#ifndef LIPO_H
#define LIPO_H
#include "controller_car.h"

// Laadalgoritme voor LiPo batterijen
// parameters: 
//  - Batterij specificaties
//  - gewenste SoC te bereiken
// return: 2 opladen gestopt omdat SoC (<100) is bereikt
// return: 1 als opladen voltooid is.
// return: 0 als opladen afgebroken wordt
int charge_LiPo(battery* spec, int socLoad);

#endif
