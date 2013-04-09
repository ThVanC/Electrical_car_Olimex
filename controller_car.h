#ifndef CONTROLLER_CAR_H
#define CONTROLLER_CAR_H


int voltage;//De spanning over de batterij
int state_of_charge;//De batterijstatus uitgedrukt in procent
int temperature;
int max_temp=50;//de default maximum temperatuur van de wagen

int getVoltage();
void setVoltage(int i);

int getTemperature();
void setTemperature(int i);
void setMaxTemperature(int i);

void alarm(int code);

#endif