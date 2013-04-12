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
json_object* giveJSON(){
	json_object * jobj = json_object_new_object();
	char * string1 = "{\"name\" : \"joys of programming\"}";
	char * string2 = "{\"second\" : \"this is programming\"}";
	char * string3 = "{\"third\" : \"for vop\"}";
	char * string4 = "{\"fourth\" : \"with a test\"}";	
	json_object * jobj1 = json_tokener_parse(string1);
	json_object * jobj2 = json_tokener_parse(string2);
	json_object * jobj3 = json_tokener_parse(string3);
	json_object * jobj4 = json_tokener_parse(string4);
	json_object *jarray = json_object_new_array();
	json_object_array_add(jarray,jobj1);
	json_object_array_add(jarray,jobj2);
	json_object_array_add(jarray,jobj3);
	json_object_array_add(jarray,jobj4);	
	return jarray;
}
int maakServer(){
  //Hier moeten we een connectie maken met de server en moeten we een integer teruggeven: deze integer is de nummer van de socket van de    connectie met de server. Om te kunnen testen gaan we voorlopig 0 returnen.
return 0;
}

json_object* SetVariables(char* buffer){
	//We krijgen een waarde binnen, we moeten deze naar de server doorsturen die dan een rij van json-objects teruggeeft. Deze objecten 	moeten we dan terug naar de client sturen.
	
	return giveJSON();
}
void *communiceer(int poort, int serverpoort){
	//printf("De communicatie is begonnen!!!");
	int socket1; //Deze socket gaar een type socket voorstellen dat we gaan gebruiken
	int socket2; //Dit is de socket wanneer de verbinding reeds is gemaakt.
	int connection;
	struct addrinfo hints;//Extra info over de connectie/ontvanger die we willen meegeven
	struct addrinfo * info;//Deze bevat een lijst van de site(s) die we zoeken met alle nodige informatie
	int error;
	char* buffer=(char*)malloc(500*sizeof(char));
	json_object * zendbuffer;
	pthread_t thr;

	//de structs initialiseren
	memset(&hints, 0, sizeof hints); //De hints-struct leegmaken
	hints.ai_family=AF_UNSPEC; //maakt niet uit, ipv4: AF_INET, ipv6: AF_INET6
	hints.ai_socktype=SOCK_STREAM; //We gaan werken met TCP, UDP: 
	hints.ai_flags=AI_PASSIVE; //voorlopig gaan we ons niets aantrekken van ons eigen IP adres en laten we dit kiezen door de computer. 


	//De connectie maken
	error=getaddrinfo(NULL,poort,&hints,&info);
	if(error<0){printf("probleem bij getaddrinfo\n");return -1;}

	socket1=socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if(socket1<0){printf("probleem bij het maken van de eerste socket\n");return -2;}

	error=bind(socket1, info->ai_addr, info->ai_addrlen)
	if(error<0){printf("problemen bij de eerste binding\n");return -3;}
	
	error=listen(socket1, 10)
	if(error<0){printf("problemen bij het luiseteren/ontvangen van de client\n");return -4;}

	socket2=accept(socket1, (struct sockaddr *)&client_addr, &client_addr_size)
	if(socket2<0){printf("problemen bij het aanvaarden van de client\n");return -5;}

	error=bind(socket2, info->ai_addr, info->ai_addrlen)
	if(error<0){printf("problemen bij de eerste binding\n");return -6;}
	while(true){
		error=write(socket2, json_object_to_json_string(zendbuffer),18);
		if(socket2<0){printf("problemen bij het verzenden van de klant zijn nieuwe poortnummer\n");return -8;}
		error=read(socket2,buffer,255);
		if(error<0)printf("problemen bij het ontvangen van de client zijn bericht");	
		zendbuffer=SetVariables(buffer);
	}
}


int laadpaal(int argc, int * argv){
	int socket1; //Deze socket gaar een type socket voorstellen dat we gaan gebruiken
	int socket2; //Dit is de socket wanneer de verbinding reeds is gemaakt.
	int connection;
	struct addrinfo hints;//Extra info over de connectie/ontvanger die we willen meegeven
	struct addrinfo * info;//Deze bevat een lijst van de site(s) die we zoeken met alle nodige informatie
	int error;
	char * deel1 = "{\"poort\" : \"";
	int poort=4568;
	int serverpoort;
	char * deel2 = "\"}";
	char *poortString=(char*)malloc(25*sizeof(char));
	char* buffer=(char*)malloc(500*sizeof(char));
	pthread_t thr;
	pthread_t serverthread;

	//de structs initialiseren
	memset(&hints, 0, sizeof hints); //De hints-struct leegmaken
	hints.ai_family=AF_UNSPEC; //maakt niet uit, ipv4: AF_INET, ipv6: AF_INET6
	hints.ai_socktype=SOCK_STREAM; //We gaan werken met TCP, UDP: 
	hints.ai_flags=AI_PASSIVE; //voorlopig gaan we ons niets aantrekken van ons eigen IP adres en laten we dit kiezen door de computer. 


	//De connectie maken
	error=getaddrinfo(NULL,"4567",&hints,&info);
	if(error<0){printf("probleem bij getaddrinfo\n");return -1;}

	socket1=socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if(socket1<0){printf("probleem bij het maken van de eerste socket\n");return -2;}

	error=bind(socket1, info->ai_addr, info->ai_addrlen)
	if(error<0){printf("problemen bij de eerste binding\n");return -3;}
	while(true){
		error=listen(socket1, 10)
		if(error<0){printf("problemen bij het luiseteren/ontvangen van de client\n");return -4;}

		socket2=accept(socket1, (struct sockaddr *)&client_addr, &client_addr_size)
		if(socket2<0){printf("problemen bij het aanvaarden van de client\n");return -5;}

		error=bind(socket2, info->ai_addr, info->ai_addrlen)
		if(error<0){printf("problemen bij de eerste binding\n");return -6;}
		
		//We gaan de server opzetten
		serverpoort=maakServer();

		//Hier gaan we al een nieuwe draad laten lopen die luisterd naar de poort
		error=pthread_create(&thr,NULL,communiceer, poort,serverpoort);
		if(error<0){printf("gefaald bij het maken van een nieuwe draad\n");return -8;}

		sprintf(poortString,"%s%i%s",deel1,poort,deel2);
		error=write(socket2, poortString,18);
		if(socket2<0){printf("problemen bij het verzenden van de klant zijn nieuwe poortnummer\n");return -9;}
		poort=poort+1;

		//error=read(socket2,buffer,255);
		//if(error<0)printf("problemen bij het ontvangen van de client zijn bericht");

		
	}
	
}
