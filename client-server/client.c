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
#include <string.h>
//#define BUFFERLENGTE 500;

json_object* SetVariables(char* buffer){
  int poortnummer=0;
  char* waarde=malloc(50*sizeof(char));
  char* GET_waarde=malloc(50*sizeof(char));
  char* buffer=malloc(50*sizeof(char));
  json_object* jobj=json_object_new_array();
  json_object * jarray2= json_tokener_parse(buffer);
  json_object * GET;
  int j;
  int GET_arraylen = json_object_array_length(jarray);
  int arraylen = json_object_array_length(jarray); 
  for (i=0; i<arraylen; i++){
    //printf("The %ie object %s\n",i,json_object_to_json_string(json_object_array_get_idx(jarray2, i)));
    json_object_object_foreach(json_object_array_get_idx(jarray2, i),key,val){
       //printf("key: %s, value: %s.\n",key,json_object_to_json_string(val));
       waarde=strncpy(waarde,json_object_to_json_string(val)+1,strlen(json_object_to_json_string(val))-2);
	//We hebben hier een if-else constructie om, afhankelijk van de key, de juist waarde aan te passen.
       if(0/*Geef hier de key als volgt in: !strncmp("De key dat je wil behandelen",key,keylengte)*/){
          //Doe hier iets
	}else if(!strncmp("load",key,4)){
		setLoadFactor(atoi(waarde));
	}else if(!strncmp("GET",key,3)){
		GET=json_tokener_parse(waarde);
		int GET_arraylen = json_object_array_length(GET); 
  		for (j=0; j<arraylen; j++){
			GET_waarde=json_object_to_json_string(json_object_array_get_idx(jarray2, i));
			if(!strncmp("voltage",GET_waarde,7)){
				sprintf(buffer,"{\"voltage\" : \"%i\"}",getVoltage());
			}else if(!strncmp("state_of_charge",GET_waarde,15)){
				sprintf(buffer,"{\"state_of_charge\" : \"%i\"}",getStateOfCharge());
			}else if(!strncmp("temperature",GET_waarde,11)){
				sprintf(buffer,"{\"temperature\" : \"%i\"}",getTemperature());
			}else if(!strncmp("max_temperature",GET_waarde,15)){
				sprintf(buffer,"{\"max_temperature\" : \"%i\"}",getMaxTemperature());
			}else if(!strncmp("loadspeed",GET_waarde,4)){
				sprintf(buffer,"{\"loadspeed\" : \"%i\"}",getLoadFactor());
			/*}else if(!strncmp("state_of_charge",GET_waarde,15)){
				sprintf(buffer,"{\"voltage\" : \"%i\"}",getVoltage());
			}*/
			}else(sprintf(buffer,"fout");)
			if(!strncmp("fout",buffer,4))json_object_array_add(jobj,buffer);
		}
	}else if(!strncmp("poort",key,5)){
	  poortnummer=atoi(waarde);	
	}
	
    } 
  }
  free(waarde);
  free(buffer);
  free(GET_waarde);
  return poortnummer;
}



int client(int poort, char* site){
 	int status;
    	char ipstr[INET6_ADDRSTRLEN];
	void *addr;
        char *ipver;
	int bufferlengte=500;
	int tekstlengte=500;
	struct addrinfo hints;//Extra info over de connectie/ontvanger die we willen meegeven
	struct addrinfo * info;//Deze bevat een lijst van de site(s) die we zoeken met alle nodige informatie
	int error;
	int socket1; //Deze socket gaar een type socket voorstellen dat we gaan gebruiken
	int connection;
	char* tekst=malloc(tekstlengte*sizeof(char));
	char* buffer=malloc(bufferlengte*sizeof(char));
	char* portToString=(char*)malloc(8*sizeof(char));
	int volgendepoort;
	json_object * jobj;

	if(poort<100)poort=4567;
	memset(&hints, 0, sizeof hints); //De hints-struct leegmaken
	hints.ai_family=AF_UNSPEC; //maakt niet uit, ipv4: AF_INET, ipv6: AF_INET6
	hints.ai_socktype=SOCK_STREAM; //We gaan werken met TCP, UDP: 
	hints.ai_flags=AI_PASSIVE; //voorlopig gaan we ons niets aantrekken van ons eigen IP adres en laten we dit kiezen door de computer. 
	
	//We gaan de infovariabele invullen in door gebruik te maken van de functie getaddrinfo. de sitenaam mag ook een IPadres zijn, een 		poortnummer (bv. 8000: locale poort),... Als dit niet lukt gaan we termineren met exitwaarde -1 en de fout afdrukken.
	sprintf(portToString,"%i",poort);
	error=getaddrinfo("localhost",portToString,&hints,&info);
	if(error<0){printf("Problemen bij het krijgen van de adresinfo.");return -1;}


	//We gaan de socket een nummer geven en bij een error gaan we termineren met exitwaarde -2	
	socket1=socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if(socket1<0){printf("problemen bij het aanmaken van de socket"); return -2;}
	printf("De socket is gemaakt\n");

	connection=connect(socket1, info->ai_addr, info->ai_addrlen);
	if(connection<0){printf("problemen bij het opzetten van de connectie"); return -3;}
	volgendepoort=poort;
	while(volgendepoort==poort){
		error=recv(socket1,buffer,200*sizeof(char),hints.ai_flags);
		if(error<0){printf("Problemen bij het ontvangen van een bericht"); return -4;}
		volgendepoort=SetVariables((char*)buffer);
		if(volgendepoort<100) volgendepoort==poort);
		error=send(socket1,json_object_to_json_string(jobj),strlen(json_object_to_json_string(jobj))*sizeof(char),hints.ai_flags);
		if(error<0){printf("problemen bij het verzenden van een pakketje");
	}
	//printf("We hebben iets ontvangen\n");

	//printf("test: %s",buffer);
	//printf("tekst: %s\n",json_object_get_string(jobj));
	/*json_object_object_foreach(jobj, key, val) {
		printf("tekst: %s\n",key);
	}*/
	close(socket1);

	
	//free(buffer);
	//free(tekst);
	client(poort);
}
