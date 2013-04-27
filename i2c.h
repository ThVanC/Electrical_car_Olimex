// I2C Communicatie 
//
// Definitie van adressen (7 bit)
#define ADDR_TEMPSENSOR    0x48 // = 100 1000
#define ADDR_DAC           0x60 // = 110 0000
#define ADDR_LCD           0x7C // zie datasheet

// Wrapper om temperatuur te lezen via I2C
// parameters zijn pointers naar MSByte en LSByte
void i2c_read_temp(int* msbyte, int* lsbyte);
