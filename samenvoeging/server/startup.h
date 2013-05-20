#ifndef STARTUP_H
#define STARTUP_H

#include "startup.h"
#include <netdb.h>

struct arg{
	int socket1;
	struct addrinfo hints;
	int connection;
};

struct arg startClient(int eigenpoort, int anderepoort, char* host);
struct arg startServer(int eigenpoort, char* host_hier);
int isReadyToRead(int _socketHandle, const long lWaitTimeMicroseconds);

#endif
