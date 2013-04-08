#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef FILEREADER
#define FILEREADER

FILE *fr;

int test()

{
   int n;
   long elapsed_seconds;
	//ESSID is van de vorm LAADPAALXXX => 11 karakters
   char line[80],ESSID[12];
   char ** netwerken = (char**)malloc(sizeof(char*)*0);
   int aantal_netwerken =0; 
   int i=0;
   int j;


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
	printf("%s\n",ESSID);
        aantal_netwerken++;
        netwerken= (char**)realloc(netwerken,sizeof(char*)*aantal_netwerken);
        netwerken[aantal_netwerken-1]=(char*)malloc(sizeof(char)*(i+1));	
		for(j=0;j<=i;j++){
			netwerken[aantal_netwerken-1][j]=ESSID[j];
		}
		/*if(i==11)
			ESSID[i]='\0';*/
   }
   for(i=0; i<aantal_netwerken; i++){
	printf("%s\n",netwerken[i]);
	free(netwerken[i]);
   }
   free(netwerken);
   fclose(fr);
}

#endif