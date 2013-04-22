installatie json:
-----------------
sudo apt-get install libjson0 libjson0-dev
 

compilatie:
----------- 
server compileren: gcc -Wall server.c globaal.c startup.c -l pthread -l json -o server -std=gnu99 
client compileren: gcc -Wall client.c globaal.c startup.c -l pthread -l json -o client -std=gnu99
laadpaal compileren: gcc -Wall client.c globaal.c startup.c -l pthread -l json -o laadpaal -std=gnu99

opmerkingen:
------------
Ik heb er nog niet achter gezocht om de connecties proper af te sluiten en het toevoegen van extra laadpalen 
aan een netwerk is nog niet getest (hier zitten wss nog fouten in)