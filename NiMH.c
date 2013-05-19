#include "lader.h"
#include "gpio-mmap.h"
#include "metingen.h"
#include <stdio.h>
#include "NiMH.h"
#include "controller_car.h"
#include "pin_config.h"
#include <unistd.h>

/*******************

Het initialiseren van de maximale spanning die over een batterij mag staan.
Deze waarde moet hard gecodeerd worden.

*******************/
void init_V_max(){
	V_max=0;
}

/*******************

Eens hij aan het algoritme begonnen is, gaat hij het blijven volhouden tot hij klaar is met laden tenzij de state aangepast wordt. 

*******************/
int charge_NiMH(int socLoad){
	int V_bat;
	int sleepTime,sleepTime_fin;
	
	init_V_max();
	setCurrentCharger(C);
	// Slaaptijd tussen opeenvolgende metingen, in milliseconden
	sleepTime = 100;
	sleepTime_fin =5000;

	while (getLoadFactor()>0) {
		setLEDS(getLoadFactor());
		if (isAtChargeLimit(socLoad)) return 2;
		V_bat=getVoltage();
	
		if(V_max<V_bat){
			V_max=V_bat;
		}
	
		if(V_bat<V_max*0.9975){
			//hoe kan je controleren of dit 5 sec lang zo blijft (andere tijdsduur is ook goed, maar men stelt 5 sec voor)
			usleep(sleepTime_fin*1000);
			if(V_bat<V_max*0.9975){
				return 1;
			}
		}

		usleep(sleepTime*1000);
	}
	return 0;
}