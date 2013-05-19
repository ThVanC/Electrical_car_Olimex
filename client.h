#ifndef CLIENT_H
#define CLIENT_H
#include <json/json.h>

json_object* SetVariables(char* buffer);
int socket1;
char* giveHost();
int clientConnect();
int *client_thr();

#endif
