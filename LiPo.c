#include "lipo.h"
#include "metingen.h"
#include <time.h>

#define	V_THRESHOLD_CELL 	4200.0	// Tresholdspanning voor een cel (mV)
#define	C 			4000.0 	// Stroomcapaciteit (mAh)
#define	NR_OF_CELLS		2 	// Aantal cellen in parallel

#define MARGE			0.99 	// Marge-factor

// Teller voor oplaadbeurten
global int k = 1;

int charge_LiPo(){
	// Definitie van variabelen
	int voltage;
	int current;
	struct timespec sleepTime;
	
	// Slaaptijd tussen opeenvolgende metingen, in milliseconden
	sleepTime.tv_sec = 0;
	sleepTime.tv_nsec = 100 * 1000000L;

	// Eerste fase:
	// Legt een constante stroom aan zolang de spanning onder de V_treshold blijft.
	do {	
		// Meet huidige spanning
		voltage = measureV();
		// Stel de stroom in op 1 x C
		current = 1*C;
		setCurrent(current);
		
		// Wacht enkele milliseconden vooraleer volgende meting uit te voeren.
		nanosleep(&sleepTime, (struct timespec *) NULL);
	} while (voltage < (V_THRESHOLD_CELL*NR_OF_CELLS)*MARGE);


	// Meet nu zowel stroom als spanning
	voltage = measureV();
	current = measureI();

	// Tweede fase:
	// Laat de stroom afnemen.
	// Wacht totdat de spanning terug V_threshold is en herhaal
	// Stroom neemt per iteratie 10% af
	while (current > (1-MARGE)*C) {
		// Als spanning ongeveer V_threshold is, verlaag de stroom
		if (voltage > (V_THRESHOLD_CELL*NR_OF_CELLS)*MARGE) k++;
		
		// Stel stroom in
		current = C*(1-k/10);
		setCurrent(current);

		// Meet de nieuwe spanning
		voltage = measureV();

		// Wacht enkele milliseconden tot volgende meting
		nanosleep(&sleepTime, (struct timespec *) NULL);
	}
	
	// Opladen voltooid
	return 1; 
}
