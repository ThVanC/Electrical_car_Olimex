#include "adc.h"
#include "imx233.h"

//voor meer informatie zie imx233RM.pdf hoofdstuk over de LRADC
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
	lradc_wr(HW_LRADC_CTRL2_SET, LRADC0_DIVIDE_BY_2);
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
	current = (int)((value*1.0-2.5)*100);

	return current;
}

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

int main(){
	initLRADC0();
	int i;
	for(i=0;i<100;i++){
		printf("%d\n",readLRADC0());
	}

	initLRADC1();
	int i;
	for(i=0;i<100;i++){
		printf("%d\n",readLRADC1());
	}
}