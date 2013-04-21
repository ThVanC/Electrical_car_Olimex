#ifndef LADER_H
#define LADER_H

int current; //uitgedrukt in mA
//On: 1, off: 0
int on;
//Charging: 1, discharging: 0
int charging;

// Variabelen voor State of Charge
int integratedCurrent; // Accumulatie van vorige stromen
unsigned long timeOfMeasurement;

//Lipo: 0, NiMH: 1
enum type_batterij {LiPo, NiMH} batterij_type;

//Dit is relay 2 aansturen op pin31. bank 2: pin 28
void turnOn();
void turnOff();
int isOn();

//Dit is relay 1 aansturen op pin30. bank 2: pin 27
void charge();
void discharge();
int isCharging();

//we geven een stroom door
void setCurrent(int i);
void convertCurrent();

// Herbereken de SoC en update de waarde in de contoller
// Om nauwkeurig te zijn moet deze functie regelmatig opgeroepen worden
void updateStateofCharge();

// Controleer of de batterij opgeladen is tot zijn limiet (SoC)
int isAtChargeLimit(int load);

void setBatterijType(int v);
char* getBatterijType();

void chargeAlgorithm();

#endif
