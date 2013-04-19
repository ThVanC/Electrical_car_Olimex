#ifndef LIPO_H
#define LIPO_H

// Laadalgoritme voor LiPo batterijen
// parameters: 
//  - V_Threshold per cell (mV)
//  - capaciteit (mAh)
//  - aantal cellen in parallel
//  - gewenste SoC te bereiken
// return: 2 opladen gestopt omdat SoC (<100) is bereikt
// return: 1 als opladen voltooid is.
// return: 0 als opladen afgebroken wordt
int charge_LiPo(int VThreshCell, int capacity, int nrOfCells, int loadSoC);

#endif
