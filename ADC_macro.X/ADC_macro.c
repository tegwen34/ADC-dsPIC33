
#include "pic24_all.h"
#include "stdio.h"

// uncomment the next line to setup this project for a 12-bit ADC
#define USE_12BIT_ADC

#ifdef  USE_12BIT_ADC
#define   ADC_LEN           12
#define   ADC_NSTEPS        4096
#define   ADC_12BIT_FLAG    1
#else
#define   ADC_LEN           10
#define   ADC_NSTEPS        1024
#define   ADC_12BIT_FLAG    0
#endif

int main (void) {
  uint16_t  u16_pot1, u16_pot2;
  float   f_pot1, f_pot2;

  configBasic(HELLO_MSG); //DEFAULT_BAUDRATE macro is 230,400
  // make RA0/AN0/VREF+ a digital input to kill the pullup and
  // set the TRISA bit, then make it ANALOG so the ADC will work
  CONFIG_RA0_AS_ANALOG();
  CONFIG_RA1_AS_ANALOG();

  while (1) {
    configADC1_ManualCH0(RA0_AN, 31, ADC_12BIT_FLAG );
    u16_pot1 = convertADC1();
    configADC1_ManualCH0(RA1_AN, 31, ADC_12BIT_FLAG );
    u16_pot2 = convertADC1();

    f_pot1 = 3.3 / ADC_NSTEPS * u16_pot1;
    f_pot2 = 3.3 / ADC_NSTEPS * u16_pot2;
    printf("AN0 is 0x%0X or %1.4fV. |  AN1 is 0x%0X or %1.4fV.\n",    \
           u16_pot1, (double) f_pot1, u16_pot2, (double) f_pot2 );
    DELAY_MS(1500);

  } 
} 

