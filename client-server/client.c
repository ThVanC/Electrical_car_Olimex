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
		/*setLoadFactor(atoi(waarde))*/;
	}else if(!strncmp("GET",key,3)){
		GET=json_tokener_parse(waarde);
		GET_arraylen = json_object_array_length(GET);
  		for (j=0; j<GET_arraylen; j++){
			strncpy(GET_waarde,json_object_to_json_string(json_object_array_get_idx(GET, j))+1, strlen(json_object_to_json_string(json_object_array_get_idx(GET, j)))-2);
			GET_waarde[strlen(json_object_to_json_string(json_object_array_get_idx(GET, j)))-2]='\0';
			if(!strncmp("voltage",GET_waarde,7)){
				sprintf(string,"{\"voltage\" : \"%i\"}",/*getVoltage()*/28);
			}else if(!strncmp("state_of_charge",GET_waarde,15)){
				sprintf(string,"{\"state_of_charge\" : \"%i\"}",/*getStateOfCharge()*/2);
			}else if(!strncmp("temperature",GET_waarde,11)){
				sprintf(string,"{\"temperature\" : \"%i\"}",/*getTemperature()*/15);
			}else if(!strncmp("max_temperature",GET_waarde,15)){
				sprintf(string,"{\"max_temperature\" : \"%i\"}",/*getMaxTemperature()*/20);
			}else if(!strncmp("loadspeed",GET_waarde,4)){
				sprintf(string,"{\"loadspeed\" : \"%i\"}",/*getLoadFactor()*/10);
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


int main(int argc,char *argv){

	struct addrinfo hints1, hints, *info;
	int error, socket1, connection, nieuwepoort;
	//int teller=0;
	char* tekst=malloc(tekstlengte*sizeof(char)), *buffer=malloc(bufferlengte*sizeof(char));

	memset(&hints1, 0, sizeof hints1); //De hints-struct leegmaken
	
	struct arg input;
	init();
	input=startClient(4931,poort,upperhost);
	error=read(input.socket1,buffer,255);
	if(error<0){printf("problemen bij read (1), error nummer %i, boodschap: %s\n",error, gai_strerror(error));return -5;}
	nieuwepoort=atoi(buffer);
	close(input.socket1);

	memset(&hints, 0, sizeof hints); //De hints-struct leegmaken
	hints.ai_family=AF_UNSPEC; //maakt niet uit, ipv4: AF_INET, ipv6: AF_INET6
	hints.ai_socktype=SOCK_STREAM; //We gaan werken met TCP, UDP: 
	hints.ai_flags=AI_PASSIVE; //voorlopig gaan we ons niets aantrekken van ons eigen IP adres en laten we dit kiezen door de computer. 
	sprintf(tekst,"%i",nieuwepoort);
	error=getaddrinfo(upperhost,tekst,&hints,&info);
	if(error<0){printf("problemen bij getaddrinfo, error nummer %i, boodschap: %s\n",error, gai_strerror(error));return -1;}
	socket1=socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if(socket1<0){printf("problemen bij socket1, error nummer %i, boodschap: %s\n",error, gai_strerror(socket1));return -2;}
	usleep(100000);
	connection=connect(socket1, info->ai_addr, info->ai_addrlen);
	if(connection<0){printf("problemen bij connection, error nummer %i, boodschap: %s\n",connection, gai_strerror(connection));return -3;}
	while(1){
		error=read(socket1,buffer,255);
		if(error<0){printf("problemen bij read (1), error nummer %i, boodschap: %s\n",error, gai_strerror(error));return -5;}
		sprintf(tekst,"%s\r\n",json_object_to_json_string(SetVariables(buffer)));
		error=send(socket1,tekst,strlen(tekst)*sizeof(char),hints.ai_flags/*18*/);
		if(error<0){printf("problemen bij send, error nummer %i, boodschap: %s\n",error, gai_strerror(error));return -6;}
		//teller=teller+1;
		
	}
	close(socket1);
	//free(tekst);
	
}
#endif
