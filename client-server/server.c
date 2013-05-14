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
#include "server.h"


struct addrinfo server_hints;
int serversocket;

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

char* SetVariables(char* buffer){
	return giveJSON();
}



void *doeiets(void* erin){
	struct arg input=*((struct arg *)erin);
	int error, open=1; 
	char *tekst=malloc(tekstlengte*sizeof(char));
	void *buffer=malloc(bufferlengte*sizeof(char));
	sprintf(tekst,"%s\r\n",giveJSON());
	if(input.socket1<0){printf("problemen bij accept, error nummer %i, boodschap: %s\n",input.socket1, gai_strerror(input.socket1));return 0;}
	while(open){
		error=send(input.socket1,tekst,strlen(tekst)*sizeof(char),input.hints.ai_flags);
		if(error<0){printf("problemen bij verzenden van het pakket\n");open=0;}

		error=read(input.socket1,buffer,255);
		if(error<0){printf("problemen bij het ontvangen van de client zijn tweede bericht\n");open=0;}
		sprintf(tekst,"%s\n",SetVariables((char*)buffer));
	}
	close(input.socket1);
	free(buffer);
	free(tekst);
	return 0;
	
}




int main(){ 
	struct arg *argument=malloc(sizeof argument);
	struct arg tijdelijk;
	int socket2,error;
	void *buffer=malloc(bufferlengte*sizeof(char));
	struct addrinfo hints;
	struct sockaddr_storage client_addr;
	struct arg input;
	socklen_t clilen;
	pthread_t thr;
	init();
	input=startServer(poort_centrale_server,host_centrale_server);
	while(1){
		memset(&client_addr, 0, sizeof(client_addr));
		clilen=16;
		socket2=accept(input.socket1, (struct sockaddr *)&client_addr, &clilen);
		error=bind(socket2, input.hints.ai_addr, input.hints.ai_addrlen);
		printf("bindig: %i\n",error);
		if(socket2<0){printf("problemen bij accept, error nummer %i, boodschap: %s\n",socket2, gai_strerror(socket2));return -5;}
		tijdelijk.socket1=socket2;
		tijdelijk.hints=hints;
		*argument=tijdelijk;
		pthread_create(&thr,NULL,doeiets, (void*)argument);
		
	}
	while(1){}
	close(input.socket1);
	free(buffer);
	return 0;

}







#endif





