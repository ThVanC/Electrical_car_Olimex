#include "routine.h"
#include "metingen.h"
#include "client.h"
#include <pthread.h>
#include <semaphore.h>

void *cardriver();

/*******************

De main functie. Deze gaat verschillende thread oproepen. We hebben er 3:
Voor de metingen uit te voeren.
Voor de client uit te voeren.
Voor de lader aan te sturen en te rijden.

*******************/
int main(){
	pthread_t thr;
	printf("main1\n");
	initCar();
	printf("main2\n");
	pthread_create(&thr, NULL, measurementsThr, NULL);
	printf("main3\n");
	pthread_create(&thr, NULL, client_thr, NULL);
	printf("main4\n");
	pthread_create(&thr, NULL, cardriver, NULL);
	printf("main5\n");
	routine((void*)5);
}


void *cardriver(){
	while(1){
		printf("begin van de while#\n");
		if(getLoadFactor()!=0){
			//Als we zien dat de loadfactor is aangegepast dan laadt de wagen op. We laten hem in dit geval nog 10 sec opladen.
			usleep(50000000);
			closeSocket();
			setWork(rijden);
			printf("We gaan rijden\n");
		}else if(getWork()==wachten){
			//Na twee seconden wachten gaan we de wagen laten laden.
			printf("We hebben gezien dat we wachter #test\n");
			startConnecting();
			usleep(2000000);
			setWork(laden);
			printf("We gaan laden\n");
		//In alle andere gevallen gaan we een paar seconden wachten en de voorwaarden opnieuw checken.
		}else usleep(2000000);
			
	}
}