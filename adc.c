#include "adc.h"
#include "imx233.h"

//voor meer informatie zie imx233RM.pdf hoofdstuk over de LRADC
//Vele disables zijn vaak functies die de LRADC aanbiedt, maar die niet nodig zijn. Bijvoorbeeld temperatuurmeting,...
#define LRADC0_DIVIDE_BY_2	0x01000000
#define LRADC1_DIVIDE_BY_2	0x02000000
#define NO_ACCUMULATION		0x20000000 
#define LRADC0_IRQ_PENDING	0x00000001
#define LRADC1_IRQ_PENDING	0x00000002
#define CH0_SCHEDULE		0x00000001
#define CH1_SCHEDULE		0x00000002
#define ZERO_SAMPLES		0x1f000000
#define SFTRST				0x80000000
#define CLKGATE				0x40000000
#define NUTTELOZE_ENABLE	0b00000000000111110000000000000000
#define SCHEDULE_OFF		0b00000000000000000000000011111111
#define GROUNDREF			0b00000000001000000000000000000000

#define ENABLE_IRQ			0b00000000000000110000000000000000
#define DISABLE_IRQ			0b00000001111111000000000000000000
#define CLEAR_IRQ			0b00000000000000000000000111111111

#define NO_DIVIDE2			0b11111110111000000000000000000000
#define DISABLE_CTRL2		0b00000000000000001000000000000000
#define TEMP_DISABLE		0b00000000000000000000001111111111

#define CTRL3_DISABLE		0b00000010110000000000000100110011
#define CTRL3_ENABLE		0b00000001000000000000001000000000

#define SELECT_C_0_1		0b00000000000000000000000000010000
#define CTRL4_CLEAR			0b11111111111111111111111111101111

/*******************

LRADC0 goed instellen. 

*******************/
int initLRADC0(){
	lradc_map();

	//printf("CTRL01: %d\n",lradc_rd(HW_LRADC_CTRL0));
	//de softreset
	lradc_wr(HW_LRADC_CTRL0_CLR, SFTRST|CLKGATE);
	//overbodige functies afzetten
	lradc_wr(HW_LRADC_CTRL0_CLR, NUTTELOZE_ENABLE);
	lradc_wr(HW_LRADC_CTRL0_CLR, SCHEDULE_OFF );
	lradc_wr(HW_LRADC_CTRL0_SET, GROUNDREF );

	//printf("CTRL02: %d\n",lradc_rd(HW_LRADC_CTRL0));
	//CTRL1
	//printf("CTRL11: %d\n",lradc_rd(HW_LRADC_CTRL1));
	lradc_wr(HW_LRADC_CTRL1_SET, ENABLE_IRQ );
	lradc_wr(HW_LRADC_CTRL1_CLR, DISABLE_IRQ );
	lradc_wr(HW_LRADC_CTRL1_CLR, CLEAR_IRQ );
	//printf("CTRL12: %d\n",lradc_rd(HW_LRADC_CTRL1));
	//CTRL2
	//printf("CTRL21: %d\n",lradc_rd(HW_LRADC_CTRL2));
	//we kunnen maar meten tot een spanning van 1.85V. We hebben echter de functie V = 2.5V + 0.1V/A * I
	lradc_wr(HW_LRADC_CTRL2_CLR, LRADC0_DIVIDE_BY_2);
	lradc_wr(HW_LRADC_CTRL2_SET, DISABLE_CTRL2);
	lradc_wr(HW_LRADC_CTRL2_CLR, NO_DIVIDE2);
	lradc_wr(HW_LRADC_CTRL2_CLR, TEMP_DISABLE);
	//printf("CTRL22: %d\n",lradc_rd(HW_LRADC_CTRL2));
	//CTRL3
	//printf("CTRL31: %d\n",lradc_rd(HW_LRADC_CTRL3));
	lradc_wr(HW_LRADC_CTRL3_CLR, CTRL3_DISABLE);
	lradc_wr(HW_LRADC_CTRL3_SET, CTRL3_ENABLE);
	//printf("CTRL32: %d\n",lradc_rd(HW_LRADC_CTRL3));
	//CTRL4
	//printf("CTRL41: %d\n",lradc_rd(HW_LRADC_CTRL4));
	lradc_wr(HW_LRADC_CTRL4_CLR, CTRL4_CLEAR);
	lradc_wr(HW_LRADC_CTRL4_SET, SELECT_C_0_1);
	//printf("CTRL42: %d\n",lradc_rd(HW_LRADC_CTRL4));
	//de accumulatie moet afgezet worden.
	lradc_wr(HW_LRADC_CH0_CLR,NO_ACCUMULATION | ZERO_SAMPLES);
	return 1;
}

/*******************

LRADC1 goed instellen

*******************/
int initLRADC1(){
	lradc_map();

	//printf("CTRL01: %d\n",lradc_rd(HW_LRADC_CTRL0));
	//de softreset
	lradc_wr(HW_LRADC_CTRL0_CLR, SFTRST|CLKGATE);
	//overbodige functies afzetten
	lradc_wr(HW_LRADC_CTRL0_CLR, NUTTELOZE_ENABLE);
	lradc_wr(HW_LRADC_CTRL0_CLR, SCHEDULE_OFF );
	lradc_wr(HW_LRADC_CTRL0_SET, GROUNDREF );

	//printf("CTRL02: %d\n",lradc_rd(HW_LRADC_CTRL0));
	//CTRL1
	//printf("CTRL11: %d\n",lradc_rd(HW_LRADC_CTRL1));
	lradc_wr(HW_LRADC_CTRL1_SET, ENABLE_IRQ );
	lradc_wr(HW_LRADC_CTRL1_CLR, DISABLE_IRQ );
	lradc_wr(HW_LRADC_CTRL1_CLR, CLEAR_IRQ );
	//printf("CTRL12: %d\n",lradc_rd(HW_LRADC_CTRL1));
	//CTRL2
	//printf("CTRL21: %d\n",lradc_rd(HW_LRADC_CTRL2));
	//we kunnen maar meten tot een spanning van 1.85V. We hebben echter de functie V = 2.5V + 0.1V/A * I
	//lradc_wr(HW_LRADC_CTRL2_SET, LRADC1_DIVIDE_BY_2);
	lradc_wr(HW_LRADC_CTRL2_SET, DISABLE_CTRL2);
	lradc_wr(HW_LRADC_CTRL2_CLR, NO_DIVIDE2);
	lradc_wr(HW_LRADC_CTRL2_CLR, TEMP_DISABLE);
	//printf("CTRL22: %d\n",lradc_rd(HW_LRADC_CTRL2));
	//CTRL3
	//printf("CTRL31: %d\n",lradc_rd(HW_LRADC_CTRL3));
	lradc_wr(HW_LRADC_CTRL3_CLR, CTRL3_DISABLE);
	lradc_wr(HW_LRADC_CTRL3_SET, CTRL3_ENABLE);
	//printf("CTRL32: %d\n",lradc_rd(HW_LRADC_CTRL3));
	//CTRL4
	//printf("CTRL41: %d\n",lradc_rd(HW_LRADC_CTRL4));
	lradc_wr(HW_LRADC_CTRL4_CLR, CTRL4_CLEAR);
	lradc_wr(HW_LRADC_CTRL4_SET, SELECT_C_0_1);
	//printf("CTRL42: %d\n",lradc_rd(HW_LRADC_CTRL4));
	//de accumulatie moet afgezet worden.
	lradc_wr(HW_LRADC_CH0_CLR,NO_ACCUMULATION | ZERO_SAMPLES);
	return 1;
}

/*******************

De waarde uit LRADC0 uitlezen.

*******************/
int readLRADC0(){
	int value=0, current;

	lradc_wr(HW_LRADC_CTRL1_CLR, LRADC0_IRQ_PENDING);
	
	while ( !(lradc_rd(HW_LRADC_CTRL1) & LRADC0_IRQ_PENDING) ){
		// Schedule a conversion on ch 1
		lradc_wr(HW_LRADC_CTRL0_CLR, CH1_SCHEDULE);
		lradc_wr(HW_LRADC_CTRL0_SET, CH0_SCHEDULE);
		//printf( "conversion scheduled...\n" );

		// Wait for schedule bit to be cleared, indicating conversion complete
		while ( (lradc_rd(HW_LRADC_CTRL0) & CH0_SCHEDULE) ) { }
		//printf( "conversion complete.\n" );

		// The next line is a hack. I've found that the data is somtimes not
		// ready even though the processor cleared the schedule bit. This slight
		// delay is enough time to allow the data to become ready.
		usleep(100);	  
	}
	//18 bits bevatten de waarde.
	value = lradc_rd(HW_LRADC_CH0) & 0x3ffff;

	//hier moet nog een omzetting komen naar mV
	//vb: value = value/20+20;

	//omzetting spanning naar stroom
	//current = (int)((value*1.0-2.5)*100);

	return value;
}

/*******************

De waarde uit LRADC1 uitlezen

*******************/
int readLRADC1(){
	int value=0;

	lradc_wr(HW_LRADC_CTRL1_CLR, LRADC1_IRQ_PENDING);

	while ( !(lradc_rd(HW_LRADC_CTRL1) & LRADC1_IRQ_PENDING) ){
		// Schedule a conversion on ch 1
		lradc_wr(HW_LRADC_CTRL0_CLR, CH0_SCHEDULE);
		lradc_wr(HW_LRADC_CTRL0_SET, CH1_SCHEDULE);
		//printf( "conversion scheduled...\n" );

		// Wait for schedule bit to be cleared, indicating conversion complete
		while ( (lradc_rd(HW_LRADC_CTRL0) & CH1_SCHEDULE) ) {
			//printf("wait a minute");
		}
		//printf( "conversion complete.\n" );

		// The next line is a hack. I've found that the data is somtimes not
		// ready even though the processor cleared the schedule bit. This slight
		// delay is enough time to allow the data to become ready.
		usleep(100);	  
	}
	//18 bits bevatten de waarde.
	value = lradc_rd(HW_LRADC_CH1) & 0x3ffff;

	//hier moet nog een omzetting komen naar mV
	//vb: value = value/20+20;

	return value;
}

/*******************

Deze functie is empirisch bepaald. De spanning staat in functie van de waarde van de LRADC weergeven.

*******************/
int convertToVoltage(int value){
	int output = 0.4604*value-25.239;
	return output;
}

/*******************

Memorymapping maken

*******************/
int *lradc_map() {
	int fd;
	if (lradc_mmap != 0) return;
		fd = open("/dev/mem", O_RDWR);
	if( fd < 0 ) {
		perror("Unable to open /dev/mem");
		fd = 0;
	}

	lradc_mmap = mmap(0, 0xfff, PROT_READ|PROT_WRITE, MAP_SHARED, fd, HW_LRADC_CTRL0);
	if( -1 == (int)lradc_mmap) {
		perror("Unable to mmap file");
		lradc_mmap = 0;
	}
	if( -1 == close(fd))
		perror("Couldn't close file");
	fd=0;
}

/*******************

Lezen op een bepaalde offset voor de verschillende registers van de LRADC

*******************/
int lradc_rd(long offset) {
	offset = offset - HW_LRADC_CTRL0;
	return lradc_mmap[offset/4];
}


/****************************************

Maak gebruik van de adressen die in imx233.h staan om de pwm te gaan gebruiken. 
De functie zal namelijk de PWM_BASE offset ervan aftrekken.
Merk op! Gebruik aub enkel adressen die overeenkomen met een register dat te maken heeft met PWM-controle (H37). Voor andere doeleinde maak je beste en nieuwe memory mapping.

****************************************/
void lradc_wr(long offset, int value) {
	offset=offset - HW_LRADC_CTRL0;
	lradc_mmap[offset/4] = value;
}