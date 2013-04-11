<<<<<<< HEAD
enum mode{
	rust,
	rijd,
	rijd_en_zoek,
	laad
}
=======
#ifndef CONTROLLER_CAR_H
#define CONTROLLER_CAR_H


int voltage;//De spanning over de batterij uitgedrukt in mV
int state_of_charge;//De batterijstatus uitgedrukt in procent
int temperature;
int max_temp=50;//de default maximum temperatuur van de wagen
int load=0; //Deze waarde is een indicatie van hoe sterk de wagen mag opladen, als deze waarde positief is gaat de wagen opladen, anders ontladen. Uitgedrukt in milliwatt?

int getVoltage();
void setVoltage(int i);

int getTemperature();
void setTemperature(int i);
void setMaxTemperature(int i);

void alarm(int code);

#endif
>>>>>>> 3bd2912827071a719ce6daab1eee58c8e8246a09
