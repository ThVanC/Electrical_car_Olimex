#include "lipo.h"
#include "metingen.h"
#include "controller_car.h"
#include <unistd.h>
#include "lader.h"

#define	V_THRESHOLD_CELL 	4200	// Tresholdspanning voor een cel (mV)
#define	C                   4000 	// Stroomcapaciteit (mAh)
#define	NR_OF_CELLS         2       // Aantal cellen in parallel

#define MARGE               0.99 	// Marge-factor


int charge_LiPo(int VThreshCell, int cap, int nrOfCells, int socLoad){
	// Definitie van variabelen
	int k;
	int voltage;
	int current;
	int sleepTime;
    
	// Slaaptijd tussen opeenvolgende metingen, in milliseconden
	sleepTime = 100;

	// Initialisatie
	k = 1;


	// Eerste fase:
	// Legt een constante stroom aan zolang de spanning onder de V_treshold blijft.
	do {	
		// Stopconditie
		if (charging == 0) return 0;
		if (isAtChargeLimit(socLoad)) return 2;

		// Meet huidige spanning
		voltage = measureV();

		// Stel de stroom in op 1 x C
		current = 1*cap;
		setCurrent(current);
		
		// Wacht enkele milliseconden vooraleer volgende meting uit te voeren.
		usleep(sleepTime*1000);
	} while (voltage < (VThreshCell*nrOfCells)*MARGE);


	// Meet nu zowel stroom als spanning
	voltage = measureV();
	current = measureI();

	// Tweede fase:
	// Laat de stroom afnemen.
	// Wacht totdat de spanning terug V_threshold is en herhaal
	// Stroom neemt per iteratie 10% af
	while (current > (1-MARGE)*cap) {

		// Stopconditie
		if (charging == 0) return 0;
		if (isAtChargeLimit(socLoad)) return 2;

		// Als spanning ongeveer V_threshold is, verlaag de stroom
		if (voltage > (VThreshCell*nrOfCells)*MARGE) k++;
		
		// Stel stroom in
		current = cap*(1-(k/10));
		setCurrent(current);

		// Meet de nieuwe spanning
		voltage = measureV();

		// Wacht enkele milliseconden tot volgende meting
		usleep(sleepTime*1000);
	}
	
	// Opladen voltooid
	return 1; 
}
