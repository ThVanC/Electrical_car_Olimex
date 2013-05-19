#ifndef STARTUP_H
#define STARTUP_H

#include <netdb.h>

//struct die de netwerk gegevens combineert.
struct arg{
	int socket1;
	struct addrinfo hints;
	int connection;
};

struct arg startClient(int eigenpoort, int anderepoort, char* host);
struct arg startServer(int eigenpoort, char* host_hier);
int isReadyToRead(int _socketHandle, const long lWaitTimeMicroseconds);

#endif
