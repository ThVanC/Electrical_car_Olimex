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

// Wrapper functie: deel spanning op in twee bytes om door te geven aan DAC
void i2c_write_DAC(int voltage){
        unsigned char data[3];
        // Eerste byte bevat instellingen voor DAC
        // 0x40: Normale mode - schrijf spanning naar register en constante spanning
        // 0x60: schrijf register en EEPROM en constante spanning
        // 0x62: power down: Vout wordt ontkoppeld
        data[0] = 0x40;
        // Tweede byte bevat msb van instelspanning
        data[1] = voltage >> 8;
        // derde byte bevat laatste vier bits en vier ongebruikte bits
        data[2] = voltage & 0xF0;

        i2c_write_data(ADDR_DAC, data, 3);
}

// Wrapper functie: zet stroom op nul en schakel DAC uit
void i2c_shutdown_DAC(){
        unsigned char data[3];
        // Uitleg: zie i2c_write_DAC
        // Zet DAC in shutdown mode
        data[0] = 0x62;
        // Stel stroom in op nul
        data[1] = 0x00;
        data[2] = 0x00;
}
