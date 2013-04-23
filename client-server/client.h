#ifndef CLIENT_H
#define CLIENT_H
#include <json/json.h>

json_object* SetVariables(char* buffer);
int main(int argc,char * argv);
int socket1;
char* giveHost();

#endif
