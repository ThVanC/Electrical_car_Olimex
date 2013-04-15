#ifndef METING_H
#define METING_H

// Definitie weerstandswaarden (kOhm)
#define R3	220
#define R4	180
#define R5	56
#define R6	120


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

// Bepaal de nieuwe State of Charge op basis van vorige waarden
// Vorige waarden worden bijgehouden door caller
// Aanpassen via pointers van vorige stroom, vorige spanning en tijdstip van vorige meting
// Gebruik NULL pointers bij eerste SoC bepaling
// return: nieuwe State of Charge
// return: -1 verkeerde combinatie van pointers meegegeven
int calculateStateofCharge(int, int*, int*, unsigned long*);


#endif
