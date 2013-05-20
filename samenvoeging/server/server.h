#ifndef SERVER_H
#define SERVER_H
#include <unistd.h>
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
#include "startup.h"
#include "globaal.h"
int main();
json_object* vraagWaarden();
json_object* geefWaarden();
void *setLoadSpeed();
int load;
int maxload;
#endif
