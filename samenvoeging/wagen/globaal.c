#ifndef GLOBAAL_C
#define GLOBAAL_C
#include "globaal.h"
void init_connection(){
	upperhost="192.168.2.2";//.231
	paalnummer=3;
	poort=30000;
	bufferlengte=5000;
	tekstlengte=5000;
	poort_centrale_server=40000;
	host_centrale_server="192.168.2.3";
	max_poort=60000;
	max_laadpalen=20;
	prefix="192.168.2.";
	IPLengte=30;
	interface="wlan0";
}
#endif
