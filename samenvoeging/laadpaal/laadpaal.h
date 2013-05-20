#ifndef LAADPAAL_H
#define LAADPAAL_H


char **IPAdressen;
int aantal;
int plaatsen;

char* geefIP();
char* giveJSON();
char* setVariables(char* buffer);
void *doeiets(void *useport);
void masterSlave();
void *runMasterSlave();
void *contactMasterSlave();
int main();
//*host="localhost"

#endif
