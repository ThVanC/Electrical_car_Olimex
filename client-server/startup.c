#ifndef STARTUP_C
#define STARTUP_C
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
#include "laadpaal.h"
#include "startup.h"
#include "globaal.h"

struct arg startClient(int eigenpoort, int anderepoort, char* host){
	struct arg terug;
	struct addrinfo hints1, *hints2, hints, *info;
	int error, connection, socket1;
	char* tekst=malloc(tekstlengte*sizeof(char));
	memset(&hints1, 0, sizeof hints1); //De hints-struct leegmaken
	memset(&terug, 0, sizeof(terug));
	terug.socket1=-1;
	hints1.ai_family=AF_UNSPEC; //maakt niet uit, ipv4: AF_INET, ipv6: AF_INET6
	hints1.ai_socktype=SOCK_STREAM; //We gaan werken met TCP, UDP: 
	hints1.ai_flags=AI_PASSIVE; //voorlopig gaan we ons niets aantrekken van ons eigen IP adres en laten we dit kiezen door de computer.
	sprintf(tekst,"%i",eigenpoort);
	getaddrinfo(NULL,tekst,&hints1,&hints2);
	hints=*hints2;
	hints.ai_family=AF_UNSPEC; //maakt niet uit, ipv4: AF_INET, ipv6: AF_INET6
	hints.ai_socktype=SOCK_STREAM; //We gaan werken met TCP, UDP: 
	hints.ai_flags=AI_PASSIVE; //voorlopig gaan we ons niets aantrekken van ons eigen IP adres en laten we dit kiezen door de computer.
	hints.ai_protocol=0;	
	sprintf(tekst,"%i",anderepoort);	
	error=getaddrinfo(host,tekst,&hints1,&info);
	if(error<0){printf("problemen bij getaddrinfo, error nummer %i, boodschap: %s\n",error, gai_strerror(error));return terug;}

	//We gaan de socket een nummer geven en bij een error gaan we termineren met exitwaarde -2	
	socket1=socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if(socket<0){printf("problemen bij socket1, error nummer %i, boodschap: %s\n",error, gai_strerror(socket1));return terug;}
	connection=-1;
	error=bind(socket1, hints.ai_addr, hints.ai_addrlen);
	if(error<0){printf("problemen bij bind, error nummer %i, boodschap: %s\n",error, gai_strerror(error));return terug;}
	printf("problemen bij de connectie? dan is de schuldige host %s met poortnummer %i en ik heb gezonden vanaf poort %i\n",host, anderepoort, eigenpoort);
	connection=connect(socket1, info->ai_addr, info->ai_addrlen);
	if(connection<0){printf("problemen met connectie\n");}
	terug.connection=connection;
	terug.hints=hints;
	terug.socket1=socket1;
	return terug;
}

struct arg startServer(int eigenpoort, char* host_hier){
	struct arg terug;
	char* nummer=malloc(6*sizeof(char));//langer dan 6 tekens kan een poortnummer niet zijn
	struct addrinfo hints, *info;
	int error, socket1;
	memset(&terug, 0, sizeof(terug));
	terug.socket1=-1;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_PASSIVE;

	sprintf(nummer,"%i",eigenpoort);
	error=getaddrinfo(host_hier,nummer,&hints,&info);
	if(error<0){printf("problemen bij adresinfo, error nummer %i, boodeschap: %s\n",error,gai_strerror(error));return terug;}
	
	socket1=socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if(socket1<0){printf("problemen bij socket1, error nummer %i, boodschap: %s\n",socket1,gai_strerror(socket1));return terug;}

	error=bind(socket1, info->ai_addr, info->ai_addrlen);
	if(error<0){printf("problemen bij bind, error nummer %i, boodschpa: %s\n",error, gai_strerror(error));return terug;}

	error=listen(socket1, 5);
	if(error<0){printf("problemen bij listen, error nummer %i, boodschap %s\n", error, gai_strerror(error));return terug;}
	terug.socket1=socket1;
	terug.hints=hints;
	terug.connection=0;
	return terug;
}



#endif

