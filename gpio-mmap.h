#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define GPIO_BASE 0x80018000
#define GPIO_WRITE_PIN(gpio,value) GPIO_WRITE((gpio)>>5, (gpio)&31, value)
#define GPIO_WRITE(bank,pin,value) (gpio_mmap[0x140+((bank)<<2)+((value)?1:2)] = 1<<(pin))
#define GPIO_READ_PIN(gpio) GPIO_READ((gpio)>>5, (gpio)&31)
#define GPIO_READ(bank,pin) ((gpio_mmap[0x180+((bank)<<2)] >> (pin)) & 1)

/*#define   HW_PINCTRL_MUXSEL3 0x130    //p 1445
#define   HW_PINCTRL_MUXSEL3_SET 0x134    //p 1445
#define   HW_PINCTRL_DRIVE6 0x260    //p 1463
#define   HW_PINCTRL_DRIVE6_SET 0x264    //p 1463
#define   HW_PINCTRL_PULL1 0x410    //p 1481
#define   HW_PINCTRL_PULL1_SET 0x414    //p 1481
#define   HW_PINCTRL_DOUT1 0x510    //p1486
#define   HW_PINCTRL_DOUT1_SET 0x514    //p1486
#define   HW_PINCTRL_DOE1 0x710    //p 1490
#define   HW_PINCTRL_DOE1_SET 0x714    //p 1490*/

int *gpio_mmap = 0;

int *gpio_map() {
int fd;
if (gpio_mmap != 0) return;
fd = open("/dev/mem", O_RDWR);
if( fd < 0 ) {
perror("Unable to open /dev/mem");
fd = 0;
}

//gpio_mmap = mmap(0, 0xfff, PROT_READ|PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
gpio_mmap = mmap(0, 0xfff, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x0);
if( -1 == (int)gpio_mmap) {
perror("Unable to mmap file");
gpio_mmap = 0;
}
if( -1 == close(fd))
perror("Couldn't close file");
fd=0;
}

int gpio_rd(long offset) {
return gpio_mmap[offset/4];
}

void gpio_wr(long offset, long value) {
gpio_mmap[offset/4] = value;
}

void gpio_output(int bank, int pin) {
gpio_mmap[0x1C1 + (bank*4)] = 1 << pin;
}

void gpio_input(int bank, int pin) {
gpio_mmap[0x1C2 + (bank*4)] = 1 << pin;
}

/*void gpio_eigen_output(int bank, int pin){
	/* //gpio_mmap[0]&=~(1<<31);
	//gpio_mmap[0]|= 1<<24;*/
	//gpio_mmap[0]|= 1<<25;
	/*//gpio_mmap[0]|= 1<<26;
	//gpio_mmap[0]|= 1<<27;
	//int i;
	gpio_mmap[0x120] |= 1 | 1<<1;
	//printf("nieuwe versie\n");
	gpio_mmap[0x240] &= ~(1 | 1<<1);
	//printf("hopelijk\n");
	gpio_mmap[0x510]|= 1;
	gpio_mmap[0x710]|= 1;
	gpio_mmap[0x510]|= 1;*/

	/*gpio_mmap[0x130] |= (1<<5 | 1<<4 );
	gpio_mmap[0x260] &= ~(1<<9);
	gpio_mmap[0x260] |= (1<<8);
	gpio_mmap[0x410] |= (1<<18);
	gpio_mmap[0x510] &= ~(1<<18);
	gpio_mmap[0x710] |= (1<<18);
	/*gpio_mmap[HW_PINCTRL_MUXSEL3] |= (1<<5 | 1<<4 ); //BANK1_PIN18 := GPIO
	gpio_mmap[HW_PINCTRL_DRIVE6] &= ~(1<<9);    //
	gpio_mmap[HW_PINCTRL_DRIVE6] |= (1<<8);    //  BANK1_PIN18_MA := 8mA
	gpio_mmap[HW_PINCTRL_PULL1] |= (1<<18);    // BANK1_PIN18 enable the internal pull up resistor
	gpio_mmap[HW_PINCTRL_DOUT1] &= ~(1<<18); // BANK1_PIN18 := 0
	gpio_mmap[HW_PINCTRL_DOE1] |= (1<<18); // drive BANK1_PIN18
	/*for(i=0;i<100;i++){
		gpio_mmap[HW_PINCTRL_DOUT1] |= (1<<18);
		usleep(2000);
		gpio_mmap[HW_PINCTRL_DOUT1] &= ~(1<<18);
		usleep(2000);
	}*/
	//GPIO_WRITE(1,18,0);

//}

void gpio_eigen_output(int bank, int pin){
	//gpio_mmap[0]&=~(1<<31);
	//gpio_mmap[0]|= 1<<24;
	//gpio_mmap[0]|= 1<<25;
	//gpio_mmap[0]|= 1<<26;
	//gpio_mmap[0]|= 1<<27;
	gpio_mmap[0x120] |= 1 | 1<<1;
	printf("nieuwe versie\n");
	gpio_mmap[0x240] &= ~(1 | 1<<1);
	printf("hopelijk\n");
	gpio_mmap[0x510]|= 1;
	gpio_mmap[0x710]|= 1;
	gpio_mmap[0x510]|= 1;

	gpio_mmap[0x134] |= (1<<5 | 1<<4 );
	gpio_mmap[0x264] &= ~(1<<9);
	gpio_mmap[0x264] |= (1<<8);
	gpio_mmap[0x414] |= (1<<18);
	gpio_mmap[0x514] &= ~(1<<18);
	gpio_mmap[0x714] |= (1<<18);
	GPIO_WRITE(1,18,0);
	//gpio_mmap[0x120] |= 1;
	/*int index = 0x100+bank*8+4*(pin/16);
	printf("%x\n",index);
	//printf("%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o\n",gpio_mmap[index],gpio_mmap[index+1],gpio_mmap[index+2],gpio_mmap[index+3],gpio_mmap[index+4],gpio_mmap[index+5],gpio_mmap[index+6],gpio_mmap[index+7],gpio_mmap[index+8],gpio_mmap[index+9],gpio_mmap[index+9],gpio_mmap[index+10],gpio_mmap[index+11],gpio_mmap[index+12],gpio_mmap[index+13],gpio_mmap[index+14],gpio_mmap[index+15],gpio_mmap[index+16],gpio_mmap[index+17],gpio_mmap[index+18],gpio_mmap[index+19],gpio_mmap[index+20],gpio_mmap[index+21],gpio_mmap[index+22],gpio_mmap[index+23],gpio_mmap[index+24],gpio_mmap[index+25],gpio_mmap[index+26],gpio_mmap[index+27],gpio_mmap[index+28],gpio_mmap[index+29],gpio_mmap[index+30],gpio_mmap[index+31]);
	gpio_mmap[index]|=(1<<((pin%16)*2));
	gpio_mmap[index]|=(1<<((pin%16)*2+1));
	//gpio_mmap[0x720]=0<<27;
	//gpio_mmap[0x720]=0<<28;
	//gpio_mmap[index]=0x3<<(pin%16)*2;
	//gpio_mmap[index]=0x1<<((pin%16)*2+1);
	//printf("%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o%o\n",gpio_mmap[index],gpio_mmap[index+1],gpio_mmap[index+2],gpio_mmap[index+3],gpio_mmap[index+4],gpio_mmap[index+5],gpio_mmap[index+6],gpio_mmap[index+7],gpio_mmap[index+8],gpio_mmap[index+9],gpio_mmap[index+9],gpio_mmap[index+10],gpio_mmap[index+11],gpio_mmap[index+12],gpio_mmap[index+13],gpio_mmap[index+14],gpio_mmap[index+15],gpio_mmap[index+16],gpio_mmap[index+17],gpio_mmap[index+18],gpio_mmap[index+19],gpio_mmap[index+20],gpio_mmap[index+21],gpio_mmap[index+22],gpio_mmap[index+23],gpio_mmap[index+24],gpio_mmap[index+25],gpio_mmap[index+26],gpio_mmap[index+27],gpio_mmap[index+28],gpio_mmap[index+29],gpio_mmap[index+30],gpio_mmap[index+31]);
	*/
}