#ifndef LADER_H
#define LADER_H

int current; //uitgedrukt in mA

//Dit is relay 2 aansturen op pin31. bank 2: pin 28
void turnOn();
void turnOff();

//Dit is relay 1 aansturen op pin30. bank 2: pin 27
void charge();
void uncharge();

//we geven een spanning door die door de comparator omgezet zal worden in een stroom.
void setCurrent(int v);

#endif