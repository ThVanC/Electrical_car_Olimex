#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <linux/i2c-dev.h>


void i2c_init(char* device){
        // TODO: testen en/of aanpassen!
        // Open het I2C device 
        deviceDescriptor = open(device, O_RDWR);
        if (deviceDescriptor == -1){
                printf("Fout bij het openen van %s \n", device);
                break;
        }
}

void i2c_read_data(unsigned char* addr, unsigned char* data, int length){
        if(ioctl(deviceDescriptor,I2C_SLAVE, addr))
		printf("I2cReadData_device : IOCTL Problem");

        read(deviceDescriptor, data, length);
}

void i2c_write_data(unsigned char addr, unsigned char* data, int length){
        if(ioctl(deviceDescriptor,I2C_SLAVE, addr))
		printf("I2cSendData_device : IOCTL Problem");

        write(deviceDescriptor, data, length);
}

// Wrapper functie: gaat ervan uit dat i2c_init al is opgeroepen
void i2c_read_temp(unsigned char* msbyte, unsigned char* lsbyte){
        unsigned char data[2];
        i2c_read_data(ADDR_TEMPSENSOR, data, 2);
        // Aanpassen van MSByte en LSByte
        *msbyte = data[0];
        *lsbyte = data[1];
}
