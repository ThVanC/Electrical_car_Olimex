#include<stdio.h>

#ifndef CONTROLLER_CAR
#define CONTROLLER_CAR

int voltage;//De spanning over de batterij
int state_of_charge;//De batterijstatus uitgedrukt in het aantal procent
int temperature;
int max_temp=50;//de default maximum temperatuur van de wagen

int getVoltage(){
	return voltage;
}
void setVoltage(int i){
	voltage=i;
}

int getTemperature(){
	return temperature;
}

void setTemperature(int i){
	temperature=i;
	if(i>max_temp){
		alarm(10);
		return;
	}
	if(i>0.9*max_temp){
		alarm(9);
		return;
	}
	if(i>0.8*max_temp){
		alarm(8);
		return;
	}
	if(i>0.7*max_temp){
		alarm(7);
		return;
	}
}

int getTemperature(){
	return temperature;
}



void alarm(int code){
	//afhankelijk van de alarmcode (hoe dringend het is) moet er een functie worden opgeroepen die hierop anticipeerd.
	switch(code){
		//Bij code 10 moet alles direct afgelegd worden
		case 10: printf("groot alarm, Laurens, doe iets");break;
		//Bij code 9 moeten we mssn ook wel eens iets gaan doen
		case 9: printf("alarm, Zeger, doe iets");break;
		case 8: printf("Lap, Emmelie, t is omzeep");break;
		case 7: printf("Lap, Mathias, ge hebt een oneindige lus geprogrammeerd. please call me, number 101"); break;
	}
}

#endif