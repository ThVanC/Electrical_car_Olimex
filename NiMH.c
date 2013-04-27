#include "lader.h"
#include "gpio-mmap.h"
#include "metingen.h"
#include <stdio.h>
#include "NiMH.h"
#include <unistd.h>


void init_V_max(){
	V_max=0;
}

int charge_NiMH(int socLoad){
	int V_bat;
	int sleepTime,sleepTime_fin;
	
	init_V_max();
	setCurrent(C);
	// Slaaptijd tussen opeenvolgende metingen, in milliseconden
	sleepTime = 100;
	sleepTime_fin =5000;

	while (on==1 && charging==1) {
		if (isAtChargeLimit(socLoad)) return 2;
		V_bat=measureV();
	
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
