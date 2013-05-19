#include "routine.h"
//#include "drive.h"
#include "lader.h"
#include "controller_car.h"
#include "GPS.h"
#include "client.h"
#include "pin_config.h"
#include <stdio.h>


/******************

hier wordt de thread die de drive logica en de laadlogica implementeert gemanaged. Er wordt tussen laden, rijden en wachten geswitched.

******************/
void *routine(void* arg){
	int oude_soc;
	printf("De routine is begonnen\n");
	init();
	printf("We zijn gedaan met de init van de routine\n");

	initLCD15();
	initLCD16();
	initLCD17();
	initLCD18();

	while(1){
		printf("test\n");
		if(work==laden){
			if(load < 0){
				setState(DISCHARGING);
			}else{
				setState(CHARGING);
			}
		}else setState(USE);
		printf("test2\n");
		
		switch(work){
		case rijden:
			printf("Initialize GPS DATA\n\n");
			initGPS();
			printf("Seed with random GPS DATA points\n");
			downloadGPS();
			printf("Run the track\n\n");
			followTrack();
			printf("## You have reached your final destination! ##\n");
			printf("Total distance covered: %d m\n", totalDistance);
			destroyGPS();
			printf("Cleaned up!\n");
			work = wachten;
			printf("We gaan wachten #test\n");
			break;
		case laden:
			/*Hier moeten we afhankelijk van wat de server zegt de lader gaan aansturen.*/
			oude_soc = state_of_charge;
			printf("Hier gaan we de oplaadalgoritmes gaan oproepen!\n\t\ttesttesttest\n\t\ttesttesttest\n\t\ttesttesttest\n\t\ttesttesttest\n\t\ttesttesttest");
			if(status==CHARGING)chargeAlgorithm();
			load = state_of_charge - oude_soc;
			/*Hij is volladen of volledig afgeladen*/
			/*if(load == 0){
				printf("De lader is klaar!!! \n\n");
				work = wachten;
				setState(USE);
			}*/
			/*De hoeveelheid energie is er uit*/
			/*if(load > 0 && status==DISCHARGING){
				printf("Het ontladen is klaar!!! \n\n");
				load = 0;
				setState(USE);
			}*/
			/*De batterij heeft de gevraagde energie opgeladen. */
			/*if(load < 0 && status==CHARGING){
				printf("het opladen is klaar!!! \n\n");
				load = 0;
				setState(USE);
			}*/
			break;
		default:
			usleep(1000000);
			break;
		}
	}
}