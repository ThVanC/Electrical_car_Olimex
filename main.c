#include <pthread.h>
#include <semaphore.h>
#include "meten.h"

void main(){
	//niet te vergeten bij het compilen in linux: gcc mai.c -o main -l pthread 
	//We gaan enkele threads aanmmaken: één thread voor de meting en 1 thread voor het rijden of opladen. (de auto kan niet rijden en opladen tegelijk)
	pthread_t draad;
	int pthread_create(&draad,NULL,*meting(), NULL);
	int pthread_create(&draad,NULL,*meting(), NULL);
	int pthread_create(&draad,NULL,*meting(), NULL);
	//int pthread_create(pthread_t * pth, pthread_attr_t *attr, void* (*function), void * arg);
	


}