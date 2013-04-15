#ifndef METING_H
#define METING_H

// Definitie weerstandswaarden (kOhm)
#define R3	220
#define R4	180
#define R5	56
#define R6	220


int initMeasurements();

//spanningsmeting: LRADC1 pin32
//uitgedrukt in mV
int measureV();

//stroommeting: LRADC0 pin33
//uitgedrukt in mA
int measureI();

//temperatuursmeting
//uitgedrukt in °C
int measureT();


#endif
