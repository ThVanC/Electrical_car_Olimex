// I2C Communicatie 
//
// source: https://github.com/OLIMEX/OLINUXINO/blob/master/SOFTWARE/iMX233/I2C/readi2c.c
//
//
// Definitie van adressen (7 bit)
#define ADDR_TEMPSENSOR    0x48 // = 100 1000
#define ADDR_DAC           0x60 // = 110 0000
#define ADDR_LCD           0x7C // zie datasheet

// Adres van I2C device
int deviceDescriptor;

// Initialiseer I2C communicatie device
void i2c_init(char* device);

// Lees van Slave op gegeven adres
void i2c_read_data(unsigned char addr, unsigned char* data, int length);

//Schrijf data naar Slave op adres
void i2c_write_data(unsigned char addr, unsigned char* data, int length);

// Wrapper om temperatuur te lezen via I2C
// parameters zijn pointers naar MSByte en LSByte
void i2c_read_temp(unsigned char* msbyte, unsigned char* lsbyte);

// Wrapper om DAC spanning door te geven
void i2c_write_DAC(int voltage);

// Wrapper om DAC uit te schakelen
void i2c_shutdown_DAC();
