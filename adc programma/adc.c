#include "adc.h"
#include "imx233.h"


#define LRADC0_DIVIDE_BY_2 0x02000000
#define LRADC1_DIVIDE_BY_2 0x01000000
#define NO_ACCUMULATION 0x20000000 
#define LRADC0_IRQ_PENDING 0x00000001
#define LRADC1_IRQ_PENDING 0x00000002
#define CH0_SCHEDULE 0x00000001
#define CH1_SCHEDULE 0x00000002
#define ZERO_SAMPLES 0x1f000000

int initLRADC0(){
	lradc_map();
	//we kunnen maar meten tot een spanning van 1.85V. We hebben echter de functie V = 2.5V + 0.1V/A * I
	lradc_wr(HW_LRADC_CTRL2_SET, LRADC0_DIVIDE_BY_2);
	//de accumulatie moet afgezet worden.
	lradc_wr(HW_LRADC_CH0_CLR,NO_ACCUMULATION | ZERO_SAMPLES);
	return 1;
}

int initLRADC1(){
	lradc_map();
	//geen divide by 2
	lradc_wr(HW_LRADC_CTRL2_CLR, LRADC1_DIVIDE_BY_2);
	//de accumulatie moet afgezet worden.
	lradc_wr(HW_LRADC_CH1_CLR,NO_ACCUMULATION | ZERO_SAMPLES);
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
			printf("wait a minute");
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
}