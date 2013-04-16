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

// Bepaal de nieuwe State of Charge in procent op basis van vorige waarden
// Vorige waarden worden bijgehouden door caller
// TODO: batterijkarakteristieken nodig
// Aanpassen via pointers van vorige stroom en tijdstip van vorige meting
// Wanneer de spanning aan de threshold is: 99% 
// Wanneer de spanning aan laagste limiet is: 1%
// return: nieuwe State of Charge
// return: -1 Een of meerder NULL-pointers
int calculateStateofCharge(int*, unsigned long*);


#endif
