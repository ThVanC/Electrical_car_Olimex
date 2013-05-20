#include "routine.h"
#include "metingen.h"
#include "client.h"
#include "controller_car.h"
#include <pthread.h>
#include <semaphore.h>
#include "client.h"
void *cardriver();
int main(){
	pthread_t thr;
	printf("main1\n");
	initCar();
	printf("main2\n");
	pthread_create(&thr, NULL, cardriver, NULL);
	printf("main3\n");
	pthread_create(&thr, NULL, client_thr, NULL);
	printf("main5\n");
	routine((void*)5);
}

void sleepmain(int i){
	/*
	 * deze functie zorgt ervoor dat de cardriver functie gedurende i
	 * microseconden niet meer werkt maar dat de metingen wel not worden
	 */
	while(i>0){
		i=i-1000000;
		measurementsThr();
		usleep(1000000);
	}
}
void *cardriver(){
	while(1){
		printf("begin van de while#\n");
		if(getLoadFactor()!=0){
			//Als we zien dat de loadfactor is aangegepast dan laadt de wagen op. We laten hem in dit geval nog 10 sec opladen.
			sleepmain(50000000);//we
			closeSocket();
			setWork(rijden);
			printf("We gaan rijden\n");
		}else if(getWork()==wachten){
			//Na twee seconden wachten gaan we de wagen laten laden.
			printf("We hebben gezien dat we wachter #test\n");
			startConnecting();
			sleepmain(2000000);
			setWork(laden);
			printf("We gaan laden\n");
		//In alle andere gevallen gaan we een paar seconden wachten en de voorwaarden opnieuw checken.
		}else sleepmain(2000000);
		measurementsThr();
			
	}
}
