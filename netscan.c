#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "networkscan.h"


#ifndef NETSCAN
#define NETSCAN

/********************

wifi interface inorde zetten.

********************/
int init(){
	system("ifconfig wlan0 up");
	//wpa supplicant wordt bij het effectief connecteren pas opgeroepen.
	//https://bbs.archlinux.org/viewtopic.php?id=43818 check deze website hiervoor!
}

/********************

scannen van alle zichtbare netwerken

********************/
int netscan(){
	system("sudo su");
	system("rootPass");
	system("sudo iwlist wlan0 scan | grep -E \'Address|ESSID\' | awk -F \\\"  \'BEGIN{RS=\"Cell\";FS=\"\\n\"}{print $1 \";\" $2}\' | grep -E \'[0-9|A-F]\' | sed \'s/[0-9][0-9] - Address: //\' | sed \'s/[ |\t]* ESSID:/ /\' > bestand.txt ");
}

/********************

Een rij van alle netwerken krijgen

********************/
char** getNetworks(){

	//geef hier enkel de netwerken die beginnen met laadpaal, de andere worden genegeerd. 
	int aantal_netwerken, i;
	FILE* fr;
	char line[80], ESSID[12];
	char** netwerken;

	fr = fopen ("bestand.txt", "rt");  /* open the file for reading */
   /* "rt" means open the file for reading text */

   	while(fgets(line, 80, fr) != NULL)
   	{
		for(i=0;i<11;i++){
			if(line[21+i]=='\n' || line[21+i]=='\"'){
				ESSID[i]='\0';
				break;
			}
			else
				ESSID[i] = line[21+i];
		}
		if(i==11)
			ESSID[i]='\0';
        aantal_netwerken++;
        netwerken= (char**)realloc(netwerken,sizeof(char*)*aantal_netwerken);
        netwerken[aantal_netwerken-1]=(char*)malloc(sizeof(char)*(i+1));	
		for(j=0;j<=i;j++){
			netwerken[aantal_netwerken-1][j]=ESSID[j];
		}

   	}

	/*******************************************************************
	MERK OP! WE MOETEN OP HET OGENBLIK DAT WE NIETS MEER MET DE NETWERKEN DOEN, DIT GEALLOCEERD GEHEUGEN VRIJGEVEN.
	*******************************************************************/

	/*for(i=0; i<aantal_netwerken; i++){
		printf("%d: %s\n",i,netwerken[i]);
		free(netwerken[i]);
	}
   	free(netwerken);*/

	fclose(fr);
	return netwerken;
}

/********************

Aantal zichtbare netwerken weergeven.

********************/
int getAantalNetwerken(){
	FILE* fr;
	char line[80];
	int aantal_netwerken;

	fr = fopen ("bestand.txt", "rt");  /* open the file for reading */
   /* "rt" means open the file for reading text */

   	while(fgets(line, 80, fr) != NULL)
   	{
       aantal_netwerken++;
   	}
	fclose(fr);
	return aantal_netwerken;
}


/********************

Toetreden tot een bepaald netwerk

********************/
char* chooseNetwork(){
	int aantal_netwerken = 0, scanned_networks = 0;
	int index;
	int* scanned;
	char** netwerken = 0;
	char* chosenNetwork;

	while(netwerken == 0){
		while(aantal_netwerken == 0){
			netscan();
			aantal_netwerken = getAantalNetwerken();
		}

		netwerken = getNetworks();
	}
	//rand genereert een getal tussen 0 en RAND_MAX, wat op zijn minst 32767 is.
	while(1){
		char* temp;
		int i, ok=1;
		while(!ok){
			ok = 1;
			index = rand()%aantal_netwerken;
			for(i=0;i<scanned_networks; i++){
				if(scanned[i] == index)
					ok=0;
			}
		}
		
		for(i=0; i<8; i++){
			temp[i]= netwerken[index][i];
			if(temp[i] == '\0') //we moeten eruit springen want hij zit al op het einde van de string.
				i=8;
		}
		temp[i]= '\0';

		if(strcmp(temp,"laadpaal")==0){
			int lengte =0;
			chosenNetwork = (char*)malloc(0);

			while(netwerken[index][lengte] != '\0'){
				lengte++;
				chosenNetwork = (char*)realloc(chosenNetwork, lengte*sizeof(char));
				chosenNetwork[lengte-1] = netwerken[index][lengte-1];
			}
			lengte++;
			chosenNetwork = (char*)realloc(chosenNetwork, lengte*sizeof(char));
			chosenNetwork[lengte-1] ='\0';
			break;
		}
		scanned[scanned_networks] = index;
		scanned_networks ++;
		if(scanned_networks==aantal_netwerken){
			for(i=0; i<aantal_netwerken; i++){
				printf("%d: %s\n",i,netwerken[i]);
				free(netwerken[i]);	
			}	
   			free(netwerken);

			while(netwerken == 0){
				while(aantal_netwerken == 0){
					netscan();
					aantal_netwerken = getAantalNetwerken();
				}
				netwerken = getNetworks();
			}
			scanned_networks=0;
		}
	}

	for(index=0; index<aantal_netwerken; index++){
		printf("%d: %s\n",i,netwerken[index]);
		free(netwerken[index]);
	}
   	free(netwerken);

	return chosenNetwork;
}

#endif