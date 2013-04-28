#include <pthread.h>
#include <semaphore.h>
#include "metingen.h"
#include "controller_car.h"
#include "drive.h"
#include "client.h"

void main(){
	//niet te vergeten bij het compilen in linux: gcc mai.c -o main -l pthread 
	//We gaan enkele threads aanmmaken: ��n thread voor de meting en 1 thread voor het rijden of opladen. (de auto kan niet rijden en opladen tegelijk)
	pthread_t draad;
	setWork(wachten);
	startConnecting();
	pthread_create(&draad,NULL,*doeMeting, NULL);
	pthread_create(&draad,NULL,*client, NULL);
	pthread_create(&draad,NULL,*routine, NULL);
	return;
	//int pthread_create(pthread_t * pth, pthread_attr_t *attr, void* (*function), void * arg);
}
