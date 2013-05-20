#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globaal.h"
char* startWifi(){
	char value[2];
	int master;
	int aantal=0;
	char* buffer=malloc(5000*sizeof(char));
	char* interface="wlan1";
	char* line=malloc(100*sizeof(char));
	size_t len = 0;
       	ssize_t read;
	char** names=malloc(20*sizeof(char**));
	FILE* fp;
	char* key="electricccars";
	char* IP="192.168.2.1";
	char* myAddress=malloc(sizeof(char)*IPLengte);
	sprintf(buffer,"iwlist %s scan |grep -E \'ESSID:\"charge\'| awk \'BEGIN { FS = \"ESSID:\" } ; { print $2 }\'>bestand.txt",interface);
	system(buffer);
	fp=fopen ("bestand.txt", "rt");
	while ((read = getline(&line, &len, fp)) != -1) {
           printf("Retrieved line of length %zu :\n", read);
           printf("%s", line);
	names[aantal]=malloc((len+1)*sizeof(char));
	sprintf(names[aantal],"%s",line);
	//master=
	names[aantal][strlen(names[aantal])-1]='\0';
	aantal=aantal+1;
       }
	fclose(fp);
	printf("test: %s\n",names[0]);
	sprintf(buffer,"iwconfig %s essid %s",interface,names[0]);
	system(buffer);
	printf("%s\n",buffer);
	sprintf(buffer,"iwconfig %s key s:%s",interface,key);
	system(buffer);
	printf("%s\n",buffer);
	sprintf(buffer,"arping %s -I %s -c 2 |grep -E \'Received \'| awk \'BEGIN { FS = \"Received \" } ; { print $2 }\'>bestand2.txt",IP, interface);
	system(buffer);
	printf("%s\n",buffer);	
	fp=fopen ("bestand2.txt", "rt");
	read = getline(&line, &len, fp);
		fgets(value, 1, fp);
		value[1]='\0'; 
		master=atoi(value);
	fclose(fp);
	if(master==0){
		sprintf(buffer,"ifconfig wlan1 192.168.2.2");
		system(buffer);
		sprintf(myAddress,"192.168.2.2");
		//sprintf(buffer,"dhclient");
	}else{
		sprintf(buffer,"dhclient %s",interface);
		system(buffer);
		sprintf(buffer,"ifconfig %s|grep -E \'inet addr\'| awk \'BEGIN { FS=\"addr:\"};{print $2}\'| awk \'END { FS=\"B\"};{print $2}\'",interface);
		system(buffer);
		fp=fopen ("bestand2.txt", "rt");
		getline(&myAddress, &len, fp);
		fclose(fp);
	}
	
	printf("%s\n",buffer);
	return myAddress;
}
