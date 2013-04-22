#ifndef LAADPAAL_C
#define LAADPAAL_C
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <json/json.h>

#include <pthread.h>
#include <semaphore.h>
#include "globaal.h"
#include "startup.h"
#include "laadpaal.h"



char* giveJSON(){
	char* terug=(char*)malloc(500*sizeof(char));
	char * string1 = "{\"load\" : \"15\"}";	
	json_object * jobj1 = json_tokener_parse(string1);
	json_object * jobj2 = json_object_new_object();
	json_object *jarray = json_object_new_array();

	json_object *jarray2 = json_object_new_array();
  	json_object *jstring1 = json_object_new_string("voltage");
 	json_object *jstring2 = json_object_new_string("loadspeed");
  	json_object *jstring3 = json_object_new_string("temperature");
  	json_object_array_add(jarray2,jstring1);
  	json_object_array_add(jarray2,jstring2);
  	json_object_array_add(jarray2,jstring3);
	json_object_object_add(jobj2,"GET",jarray2);
	
	json_object_array_add(jarray,jobj1);
	json_object_array_add(jarray,jobj2);	
	sprintf(terug,"%s",json_object_to_json_string(jarray));
	return  terug;
}

/*char* SetVariables(char* buffer){
	//We krijgen een waarde binnen, we moeten deze naar de server doorsturen die dan een rij van json-objects teruggeeft. Deze objecten 	moeten we dan terug naar de client sturen.
	
	return giveJSON();
}*/



void *doeiets(void* erin){
	struct arg input=*((struct arg *)erin);
	int error, socket2; 
	char *tekst=malloc(tekstlengte*sizeof(char));
	void *buffer=malloc(bufferlengte*sizeof(char));
	struct sockaddr_storage client_addr;
	socklen_t clilen;
	struct arg server;	

	socket2=accept(input.socket1, (struct sockaddr *)&client_addr, &clilen);
	server=startClient(poort-1,poort_centrale_server,host_centrale_server);
	if(socket2<0){printf("problemen bij accept van client, error nummer %i, boodschap: %s\n",socket2, gai_strerror(socket2));return 0;}
	while(1){
		error=read(server.socket1,buffer,255);
		if(error<0)printf("problemen bij het ontvangen van het bericht van de server, nummer %i: %s\n", error, gai_strerror(error));
		error=send(socket2,buffer,strlen(buffer)*sizeof(char),input.hints.ai_flags);
		if(error<0)printf("problemen bij verzenden van hetpakket\n");
		error=read(socket2,buffer,255);
		if(error<0)printf("problemen bij het ontvangen van de client zijn tweede bericht\n");
		error=send(server.socket1, buffer, strlen(buffer)*sizeof(char), server.hints.ai_flags);
		if(error<0)printf("problemen bij het verzenden van een bericht naar de server");
	}
	close(input.socket1);
	close(socket2);
	free(buffer);
	free(tekst);
	return 0;
	
}




int main(){ 
	struct arg *argument=malloc(sizeof argument);
	int error, socket2, *useport=(int*)malloc(sizeof(int));
	char *tekst=malloc(tekstlengte*sizeof(char));
	void *buffer=malloc(bufferlengte*sizeof(char));
	struct addrinfo hints;
	struct sockaddr_storage client_addr;
	struct arg input;
	socklen_t clilen;
	pthread_t thr;
	init();
	input=startServer(poort, me);
	masterSlave(input);
	*useport=poort+1;
	while(1){
		error=listen(input.socket1, 5);
		if(error<0){printf("problemen bij listen, error nummer %i, boodschap %s\n", error, gai_strerror(error));return -4;}
		
		socket2=accept(input.socket1, (struct sockaddr *)&client_addr, &clilen);
		if(socket2<0){printf("problemen bij accept, error nummer %i, boodschap: %s\n",socket2, gai_strerror(socket2));return -5;}
		
		*useport=(*useport-poort)%max_poort+1+poort;
		sprintf(tekst,"%i\r\n",*useport);
		error=send(socket2,tekst,strlen(tekst)*sizeof(char),hints.ai_flags);
		if(error<0)printf("problemen bij verzenden van hetpakket\n");
		*argument=startServer(*useport, me);
		pthread_create(&thr,NULL,doeiets, (void*)argument);
		close(socket2);
	}
	close(input.socket1);
	free(buffer);
	return 0;

}


void masterSlave(struct arg input){
	//We moeten een luiseren naar de juiste poort (=poort-2);
	/*struct arg input=startServer(poort-1);*/
	pthread_t thr;
	struct sockaddr* pV4Addr=malloc(sizeof pV4Addr);
	struct sockaddr_in* pV4Addr_in;
	socklen_t *adreslengte=malloc(sizeof adreslengte);
	char* myAddress=malloc(IPLengte*sizeof(char));
	void* buffer;
	getsockname(input.socket1, pV4Addr, adreslengte);
	getsockname(input.socket1, pV4Addr, adreslengte);
	pV4Addr_in=(struct sockaddr_in*)pV4Addr;
	/*printf("test: %d.%d.%d.%d.%d\n",
	  (int)(pV4Addr_in->sin_addr.s_addr&0xFF),
	  (int)((pV4Addr_in->sin_addr.s_addr&0xFF00)>>8),
	  (int)((pV4Addr_in->sin_addr.s_addr&0xFF0000)>>16),
	  (int)((pV4Addr_in->sin_addr.s_addr&0xFF000000)>>24),
	  (int)((pV4Addr_in->sin_addr.s_addr&0xFF000000)>>32));
	printf("%s\n",inet_ntoa(pV4Addr_in->sin_addr));*/
	sprintf(myAddress,"%s",inet_ntoa(pV4Addr_in->sin_addr));
	if((int)((pV4Addr_in->sin_addr.s_addr&0xFF000000)>>24)==1){
		pthread_create(&thr,NULL,runMasterSlave, (void*)myAddress);
		buffer=malloc(bufferlengte*sizeof(char*));
		sprintf(buffer,"%s%i",prefix,1);
	}
	else {
		pthread_create(&thr,buffer,contactMasterSlave,(void*)myAddress);	
	}		
}

void *runMasterSlave(char* myAddress){
//Hier gaan we een rij van laadpalen bijhouden en tegelijk een server runnen waarop nieuwe laadpalen zich kunnen "aanmelden".
//Verder moeten de clients zich met deze server connecteren waarna de maser de clients verbindt met de auto.
char* tekst=malloc(tekstlengte*sizeof(char*));
char* buffer=malloc(bufferlengte*sizeof(char*));
struct sockaddr_storage client_addr;
socklen_t clilen;
int socket2, error;
struct arg input=startServer(poort-2,myAddress);
IPAdressen=malloc(max_laadpalen*sizeof(char*));
aantal=0;
while(1){
	//We nemen aan dat de client/andere laadpaal maar 1 boodschap verzend en ontvangt, zodat we hiervoor geen nieuwe thread gaan aanmaken
	socket2=accept(input.socket1, (struct sockaddr *)&client_addr, &clilen);
	if(socket2<0){printf("problemen bij accept, error nummer %i, boodschap: %s\n",socket2, gai_strerror(socket2));return NULL;}

	//Hier moeten we het tekstobject omvormen tot een json object en dit json object vervolgens uitlezen en verwerken.
	error=read(socket2,buffer,255);
	tekst=setVariables(buffer);
	error=send(socket2,tekst,strlen(tekst)*sizeof(char),input.hints.ai_flags);
	if(error<0)printf("problemen bij verzenden van hetpakket\n");

	close(socket2);
}
}

void *contactMasterSlave(char* myAddress){
//Hier gaan we ons aanmelden bij de centrale server
struct sockaddr_storage client_addr;
socklen_t clilen;
int error;
json_object * jobj;
char* buffer=malloc(IPLengte*sizeof(char));
sprintf(buffer,"%s%i",prefix,1);
struct arg input=startClient(poort-3, poort-2,buffer);
sprintf(buffer,"{\"IP-adres\" : \"%s\"}\n",myAdress);
error=send(input.socket1,buffer,strlen(buffer)*sizeof(char),input.hints.ai_flags);
if(error<0)printf("problemen bij verzenden van het pakket\n");
error=read(input.socket1,buffer,255);
if(error<0)printf("problemen bij het ontvangen van het bericht van de server, nummer %i: %s\n", error, gai_strerror(error));
jobj= json_tokener_parse(buffer);
json_object_object_foreach(jobj,key,val)
strncpy(buffer,json_object_to_json_string(val),strlen(json_object_to_json_string(val)));
//We hebben ons nu aangemeld. Het IPadres van de laadpaal waarmee we contact willen leggen zit in de buffer.De volgende stap is om telkens naar de voorganger te "pingen" om te kijken of die er nog is, en om dan een boodschap te sturen naar de master om te zeggen dat er een laadpaal is verdwenen. Dit is echter niet noodzakelijk omdat het voertuig het wel zal merken als er een laadpaal niet meer is. Die kan het dan wel aan de laadpaal zeggen.
return buffer;
}



char* setVariables(char* buffer){
  char* tekst=malloc(tekstlengte*sizeof(char*));
  char* waarde=malloc(50*sizeof(char));
  json_object * jarray2= json_tokener_parse(buffer);
  int i;
  int arraylen = json_object_array_length(jarray2);
  tekst[0]='\0';
  for (i=0; i<arraylen; i++){
    json_object_object_foreach(json_object_array_get_idx(jarray2, i),key,val){
	if(json_object_to_json_string(val)[0]!='"'){
	       waarde=strncpy(waarde,json_object_to_json_string(val),strlen(json_object_to_json_string(val)));
		waarde[strlen(json_object_to_json_string(val))]='\0';
	}else{
		waarde=strncpy(waarde,json_object_to_json_string(val)+1,strlen(json_object_to_json_string(val))-2);
		waarde[strlen(json_object_to_json_string(val))-2]='\0';
	}
	//We hebben hier een if-else constructie om, afhankelijk van de key, de juist waarde aan te passen.
       if(!strncmp("add_laadpaal",key,12)){
		IPAdressen[aantal]=malloc(IPLengte*sizeof(char));
		sprintf(IPAdressen[aantal],"%s",waarde);
		aantal=aantal+1;
	}else if(!strncmp("add_client",key,10)){
		tekst=geefIP();
	}else if(!strncmp("remove_client",key,10)){
		//Hier moeten we niets doen, dode functie
	}else if(!strncmp("remove_laadpaal",key,10)){
		int teller=0;
		for(teller;teller<aantal;teller++){
			if(!strncmp(IPAdressen[teller],waarde,strlen(waarde))){
				free(IPAdressen[teller]);
				IPAdressen[teller]=IPAdressen[aantal-1];
				break;			
			}
		}
		aantal=aantal-1;
	}
	
    } 
	
  }
  free(waarde);
  return tekst;
}

char* geefIP(){
	char* terug=tekstlengete*sizeof(char);
	int value=rand()%aantal;
	sprintf(tekst,"{\"IP-adres\" : \"%s\"}\n",terug[value]);
	return terug;
}



#endif





