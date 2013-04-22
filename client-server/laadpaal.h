#ifndef LAADPAAL_H
#define LAADPAAL_H
char* giveJSON();
char* setVariables(char* buffer);
void *doeiets(void *useport);
int main();
void masterSlave();
void *runMasterSlave();
void *contactMasterSlave();
char **IPAdressen;
int aantal;
int plaatsen;
char* geefIP();
//*host="localhost"
#endif
