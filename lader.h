#ifndef LADER_H
#define LADER_H

#define ON_OFF_BANK 2
#define DISCHARGE_BANK 2
#define ON_OFF_PIN 28
#define DISCHARGE_PIN 27

#define VDD   5000   // Voedingsspanning

/*****************************************/
//
//        COMBINATIES RELAISSTANDEN
//
//    STANDEN RELAYS   |  TOESTAND BATT
// -----------------------------------------
//  ON & DISCHARGING   |  Ontladen
//  ON & CHARGING      |  Verboden toestand!
//  OFF & DISCHARGING  |  Normaal gebruik
//  OFF & CHARGING     |  Opladen
//
/******************************************/

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

// Toestanden voor relay-standen
enum status {CHARGING, DISCHARGING, USE} status;

// Schakelen tussen opladen, ontladen of gewoon gebruik
int setState(enum status);

// Geef huidige status
enum status getState();


//we geven een stroom door
void setCurrent(int i);
int convertCurrent();

// Herbereken de SoC en update de waarde in de contoller
// Om nauwkeurig te zijn moet deze functie regelmatig opgeroepen worden
void updateStateofCharge();

// Controleer of de batterij opgeladen is tot zijn limiet (SoC)
int isAtChargeLimit(int load);

void setBatterijType(int v);
char* getBatterijType();

void chargeAlgorithm();

/* HULPFUNCTIES - NIET rechtstreeks gebruiken */

//Dit is relay 2 aansturen op pin31. bank 2: pin 28
void turnOn();
void turnOff();
int isOn();

//Dit is relay 1 aansturen op pin30. bank 2: pin 27
void charge();
void discharge();
int isCharging();

#endif
