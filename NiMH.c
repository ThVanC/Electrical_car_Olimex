#include "lader.h"
#include "gpio-mmap.h"
#include "metingen.h"
#include <stdio.h>
#include "NiMH.h"

void init_V_max(){
	V_max=0;
}

void charge_NiMH(){
	int V_bat;

	setCurrent(C);
	V_bat=measureV();

	if(V_bat<V_max*0.9975){
		//hoe kan je controleren of dit 5 sec lang zo blijft (andere tijdsduur is ook goed, maar men stelt 5 sec voor)
		turnOff();
	}

	if(V_max<V_bat){
		V_max=V_bat;
	}
	
}