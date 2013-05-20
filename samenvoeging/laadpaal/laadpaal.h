#ifndef LAADPAAL_H
#define LAADPAAL_H

void masterSlave();
void *runMasterSlave();
void *contactMasterSlave();
char **IPAdressen;
int aantal;
int plaatsen;

char* geefIP();
char* giveJSON();
char* setVariables(char* buffer);
void *doeiets(void *useport);
int main();
//*host="localhost"

#endif
