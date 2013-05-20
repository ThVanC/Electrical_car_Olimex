#ifndef GLOBAAL_C
#define GLOBAAL_C
#include "globaal.h"

/**************************

Globale constanten instellen.

**************************/
void init(){
	upperhost="192.168.2.2";//Hier moet het IP-adres van de master laadpaal ingevuld worden
	paalnummer=3;//niet van belang
	/***************************
	Dit is de poort waarop elke laadpaal gaat luisteren naar wagens die zich aan die laadpaal willen opladen. 
	De anere poort waarnaar de master laadpaal luisterd is poort -2.
	***************************/
	poort=30000;
	/**************************
	Hierin gaan we bijhouden hoeveel ruimte in het geheugen dat we gaan alloceren bij het oproepen van de functie malloc
	**************************/
	bufferlengte=5000;
	tekstlengte=5000;
	/**************************
	Hier houden we bij op welk poortnummer en 
	naar welk IP-adresde centrale server luisterd.
	***************************/
	poort_centrale_server=40000;
	host_centrale_server="192.168.2.3";

	/*************************
	Hier gaan we bijhouden tot welke poort we maximaal willen gaan. 
	De minimale poort dat we in dit geval gebruiken is 2*poort-max_poort-4.
	************************/
	max_poort=40000;
	/***********************
	Het maximum aantal laadpalen
	**********************/
	max_laadpalen=20;

	/**********************
	Hierin gaan we bijhouden waarmee elk IP adres uit het netwerk begint.
	**********************/
	prefix="192.168.2.";

	/**********************
	Hier gaan we bijhouden hoe lang de IP adressen maximaal mogen zijn.
	***********************/
	IPLengte=30;
}
#endif
