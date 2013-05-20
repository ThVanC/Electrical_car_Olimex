#ifndef CLIENT_C
#define CLIENT_C
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <json/json.h>
#include <stdio.h>
#include "client.h"
#include "startup.h"
#include "globaal.h"
#include "start_wifi.h"
#include "controller_car.h"
int socket1;
json_object* SetVariables(char* buffer){
	char* string=(char*)malloc(tekstlengte*sizeof(char));
	json_object* jobj=json_object_new_array();
	char* waarde=malloc(50*sizeof(char));
	char* GET_waarde=malloc(50*sizeof(char));
	json_object * jarray2= json_tokener_parse(buffer);
	json_object * GET=json_object_new_array();
	int i, j;
	int GET_arraylen;
	int arraylen = json_object_array_length(jarray2);
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
			if(0/*Geef hier de key als volgt in: !strncmp("De key dat je wil behandelen",key,keylengte)*/){
				//Doe hier iets
			}else if(!strncmp("load",key,4)){
				setLoadFactor(atoi(waarde));
				printf("@We krijgen een string toegestuurd...");
			}else if(!strncmp("GET",key,3)){
				GET=json_tokener_parse(waarde);
				GET_arraylen = json_object_array_length(GET);
				for (j=0; j<GET_arraylen; j++){
					strncpy(GET_waarde,json_object_to_json_string(json_object_array_get_idx(GET, j))+1, strlen(json_object_to_json_string(json_object_array_get_idx(GET, j)))-2);
					//waarde[strlen(json_object_to_json_string(val))-2]='\0';
					GET_waarde[strlen(json_object_to_json_string(json_object_array_get_idx(GET, j)))-2]='\0';
					if(!strncmp("voltage",GET_waarde,7)){
						sprintf(string,"{\"voltage\" : \"%i\"}",getVoltage());
					}else if(!strncmp("state_of_charge",GET_waarde,15)){
						sprintf(string,"{\"state_of_charge\" : \"%i\"}",getStateOfCharge());
					}else if(!strncmp("temperature",GET_waarde,11)){
						sprintf(string,"{\"temperature\" : \"%i\"}",getTemperature());
					}else if(!strncmp("max_temperature",GET_waarde,15)){
						sprintf(string,"{\"max_temperature\" : \"%i\"}",getMaxTemperature());
					}else if(!strncmp("loadspeed",GET_waarde,4)){
						sprintf(string,"{\"loadspeed\" : \"%i\"}",getLoadFactor());
					}else{sprintf(string,"fout");}
					if(strncmp("fout",string,4))json_object_array_add(jobj,json_tokener_parse(string));
				}
			}

		}

	}
	free(waarde);
	free(string);
	free(GET_waarde);
	return jobj;
}


int clientConnect(){
	struct addrinfo hints1, hints, *info;
	int error, connection, nieuwepoort, open=1;
	char* tekst=malloc(tekstlengte*sizeof(char)), *buffer=malloc(bufferlengte*sizeof(char));
	char* host=malloc(IPLengte*sizeof(char));
	memset(&hints1, 0, sizeof hints1); //De hints-struct leegmaken
	struct arg input;
	char* ontvangen;
	input=startClient(50000, poort-2, upperhost);
	sprintf(tekst,"[{\"add_client\" : \"%s\"}]\n","tekst");
	error=send(input.socket1,tekst ,strlen(tekst),input.hints.ai_flags);
	error=read(input.socket1, buffer, 255);
	host=giveHost(buffer);
	close(input.socket1);
	input=startClient(50100,poort,host);
	while(input.connection<0){
		input=startClient(50000, poort-2, upperhost);
		sprintf(tekst,"[{\"remove_client\" : \"%s\"}]\n",buffer);
		error=send(input.socket1,tekst ,strlen(tekst),input.hints.ai_flags);
		sprintf(tekst,"[{\"add_client\" : \"%s\"}]\n","tekst");
		error=send(input.socket1,tekst ,strlen(tekst),input.hints.ai_flags);
		error=read(input.socket1, buffer, 255);
		host=giveHost(buffer);
		close(input.socket1);
		input=startClient(50100,poort,host);
	}
	error=read(input.socket1,buffer,255);
	if(error<0){printf("problemen bij read (1), error nummer %i, boodschap: %s\n",error, gai_strerror(error));return -5;}
	nieuwepoort=atoi(buffer);
	close(input.socket1);

	input=startClient(50200,nieuwepoort,host);
	socket1=input.socket1;
	while(open){
		error=read(input.socket1,buffer,255);
		if(error<0){printf("problemen bij read (1), error nummer %i, boodschap: %s\n",error, gai_strerror(error));open=0;}
		sprintf(tekst,"%s\r\n",json_object_to_json_string(SetVariables(buffer)));
		error=send(input.socket1,tekst,strlen(tekst)*sizeof(char),hints.ai_flags/*18*/);
		if(error<0){printf("problemen bij send, error nummer %i, boodschap: %s\n",error, gai_strerror(error));open=0;}

	}
	close(socket1);
	//free(tekst);

}

void closeSocket(){
	shutdown(socket1, SHUT_RDWR);
}

char* giveHost(char* buffer){
	char* host=malloc(IPLengte*sizeof(char));
	json_object* jobj=json_tokener_parse(buffer);
	json_object_object_foreach(jobj,key,val);
	host=strncpy(host,json_object_to_json_string(val)+1,strlen(json_object_to_json_string(val))-2);
	host[strlen(json_object_to_json_string(val))-2]='\0';
	return host;
}
char* askloader(){
	char* terug=(char*)malloc(500*sizeof(char));

	json_object * jobj2 = json_object_new_object();
	json_object *jarray = json_object_new_array();

	json_object *jarray2 = json_object_new_array();
	json_object *jstring1 = json_object_new_string("username");
	json_object *jstring2 = json_object_new_string("password");
	json_object_array_add(jarray2,jstring1);
	json_object_array_add(jarray2,jstring2);
	json_object_object_add(jobj2,"GET",jarray2);

	json_object_array_add(jarray,jobj2);	
	sprintf(terug,"%s\n",json_object_to_json_string(jarray));
	return  terug;
}
int *client_thr(){
	init_connection();
	while(1){
		printf("Begonnen in de client thread\n");
		//we gaan eerst wachten op een connectie
		printf("client thread: IP gedaan\n");
		waitConnecting();
		//vervolgens gaan we de wifi moule starten
		printf("client thread: connecting gedaan");
		me=startWifi();
		//tot slot gaan we connectie maken met de laadpaal
		clientConnect();
		printf("client thread: ready\n");
		setLoadFactor(0);	
	}
	
}

#endif
