#include "routine.h"
//#include "drive.h"
#include "lader.h"
#include "controller_car.h"
#include "GPS.h"
#include "client.h"
#include <stdio.h>


/******************

hier wordt de thread die de drive logica en de laadlogica implementeert gemanaged. Er wordt tussen laden, rijden en wachten geswitched.

******************/
void* routine(void* arg){
	init();

    while(1){

		if(load < 0){
			setState(DISCHARGING);
		}else if(load > 0){
			setState(CHARGING);
		}else{
			setState(USE);
		}

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
				//i++;
				work = wachten;
				break;
			case laden:
				/*Hier moeten we afhankelijk van wat de server zegt de lader gaan aansturen.*/
				int oude_soc = state_of_charge;
				printf("Hier gaan we de oplaadalgoritmes gaan oproepen!\n\t\ttesttesttest\n\t\ttesttesttest\n\t\ttesttesttest\n\t\ttesttesttest\n\t\ttesttesttest");
				chargeAlgorithm();
				load = state_of_charge - oude_soc;
				/*Hij is volladen of volledig afgeladen*/
				if(load == 0){
					printf("De lader is klaar!!! \n\n");
					work = wachten;
					setState(USE);
				}
				/*De hoeveelheid energie is er uit*/
				if(load > 0 && status==DISCHARGING){
					printf("Het ontladen is klaar!!! \n\n");
					load = 0;
					setState(USE);
				}
				/*De batterij heeft de gevraagde energie opgeladen. */
				if(load < 0 && status==CHARGING){
					printf("het opladen is klaar!!! \n\n");
					load = 0;
					setState(USE);
				}
				break;
			default:
				/*Hier moeten we hem laten wachten.*/
				printf("De wagen is niets aan het doen. We wachten");
				if(specs.capacity*PERCENTUEEL_VERMOGEN >= state_of_charge){
					work = laden;
				}
				usleep(20000);
				break;
		}
		if((work!=laden) && getStateOfCharge()<specs.capacity*0.1){
			printf("We zitten onder de minimaal toegelaten energie!\n");
			work = laden;
		}
		if(work == rijden && load!= 0)
			work = laden;
    }
}
