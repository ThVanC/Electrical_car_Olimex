#ifndef METING_H
#define METING_H

// Definitie weerstandswaarden (kOhm)
#define R3	220
#define R4	330
#define R5	56
#define R6	120

unsigned long timeMoment,now;
int sum;

int initMeasurements();

//spanningsmeting: LRADC1 pin32
//uitgedrukt in mV
int measureV();

//stroommeting: LRADC0 pin33
//uitgedrukt in mA
int measureI();

//temperatuursmeting
//uitgedrukt in �C
int measureT();

// Bepaal de nieuwe State of Charge in procent op basis van vorige waarden
// Vorige waarden worden bijgehouden door caller
// TODO: batterijkarakteristieken nodig
// Aanpassen via pointers van totale stroom en tijdstip van vorige meting
// Wanneer de spanning aan de threshold is: 99% 
// Wanneer de spanning aan laagste limiet is: 1%
// return: nieuwe State of Charge in 100 x %
// return: -1 Een of meerder NULL-pointers
int calculateStateofCharge(int*, unsigned long*);

//de voltage en de spanning worden upgedate. Net zoals de stateOfCharge.
void manageMeasurements();

void* measurementsThr(void* arg);

#endif
