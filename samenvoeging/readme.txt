installatie json:
-----------------
Debian: 	sudo apt-get install libjson0 libjson0-dev
Archlinux:	pacman -S json-c


installatie GUI (GTK):
----------------------
 sudo apt-get install libgtk2.0-dev
 

compilatie:
----------- 
server compileren: gcc -Wall server.c globaal.c startup.c -l pthread -l json -o server -std=gnu99 
client compileren: gcc -Wall *.c -lpthread -ljson -o wagen-std=gnu99
laadpaal compileren: gcc -Wall client.c globaal.c startup.c -l pthread -l json -o laadpaal -std=gnu99
GUI voor laadpaal cimpileren: gcc -Wall gui_laadpaal.c `pkg-config --cflags --libs gtk+-2.0` -o guitest