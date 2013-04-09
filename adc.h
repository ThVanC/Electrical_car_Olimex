#ifndef ADC_H
#define ADC_h

int initLRADC0();
int initLRADC1();

// hier gaan we de waarde uitlezen. Je moet wel aangeven uit welke ADC je gaat lezen. 
// De chip heeft namelijk 12 kanalen die allemaal over 1 multiplexer komen. Dus je kan er maar 1 gelijktijdig gebruiken.
int read(int number);

#endif