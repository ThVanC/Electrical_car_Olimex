#ifndef METING_H
#define METING_H

int initMeasurements();

//spanningsmeting: LRADC1 pin32
//uitgedrukt in mV
int measureV();

//stroommeting: LRADC0 pin33
//uitgedrukt in mA
int measureC();

//temperatuursmeting
//uitgedrukt in °C
int measureT();


#endif