all: imx233_controller

imx233_controller: *.o
	gcc -o imx233_controller *.o

%.o: %.c
	gcc -c -O0 -Wall $?

clean:
	rm -rf imx233_controller *.o
