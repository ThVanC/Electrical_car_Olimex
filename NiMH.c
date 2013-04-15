#include "lader.h"
#include "gpio-mmap.h"
#include "metingen.h"
#include <stdio.h>
#include "NiMH.h"
#include <time.h>

void init_V_max(){
	V_max=0;
}

int charge_NiMH(){
	int V_bat;
	setCurrent(C);

	struct timespec sleepTime_NiMH,sleepTime_off;
	
	// Slaaptijd tussen opeenvolgende metingen, in milliseconden
	sleepTime_NiMH.tv_sec = 0;
	sleepTime_NiMH.tv_nsec = 100 * 1000000L;
	sleepTime_off.tv_sec = 5;
	sleepTime_off.tv_nsec = 0;

	while (on==1) {
		V_bat=measureV();
	
		if(V_max<V_bat){
			V_max=V_bat;
		}
	
		if(V_bat<V_max*0.9975){
			//hoe kan je controleren of dit 5 sec lang zo blijft (andere tijdsduur is ook goed, maar men stelt 5 sec voor)
			nanosleep(&sleepTime_off, (struct timespec *) NULL);
			if(V_bat<V_max*0.9975){
				return 1;
			}
		}

		nanosleep(&sleepTime_NiMH, (struct timespec *) NULL);
	}
	
}
