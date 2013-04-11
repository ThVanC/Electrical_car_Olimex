all: imx233_controller

imx233_controller: *.o
	gcc -o imx233_controller *.o

%.o: %.c
	gcc -c -O0 -Wall -l pthread $?

clean:
	rm -rf imx233_controller *.o
