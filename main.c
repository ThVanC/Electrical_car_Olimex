#include "routine.h"
#include "metingen.h"
#include "client.h"
#include <pthread.h>
#include <semaphore.h>

/*******************

De main functie. Deze gaat verschillende thread oproepen. We hebben er 3:
Voor de metingen uit te voeren.
Voor de client uit te voeren.
Voor de lader aan te sturen en te rijden.

*******************/
int main(){
	pthread_t thr;
	//measurementsThr((void*)5);
	pthread_create(&thr, NULL, measurementsThr, (void*)5);
	//pthread_create(&thr, NULL, client_thr, (void*)5);
	routine((void*)5);
}