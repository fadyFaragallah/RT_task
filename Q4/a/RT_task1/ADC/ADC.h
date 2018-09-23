#ifndef ADC_H_
#define ADC_H_
#include "../Data_Types.h"

#define myACSR   *((volatile unsigned char* const)0X28)
#define myADMUX  *((volatile unsigned char* const)0X27)
#define myADCSRA *((volatile unsigned char* const)0X26)
#define myADCH   *((volatile unsigned char* const)0X25)
#define myADCL   *((volatile unsigned char* const)0X24)

void ADC_voidInit();
void ADC_startConversion();

#endif /* ADC_H_ */