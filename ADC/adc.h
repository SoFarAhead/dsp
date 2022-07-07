/*
 * adc.h
 *
 *  Created on: 2022年6月28日
 *      Author: 10758
 */
//使用ADA1
#ifndef APP_ADC_H_
#define APP_ADC_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define ADC_MODCLK 0x3
#define ADC_SHCLK  0xf
#define ADC_CKPS   0x1
void AdcInit(void);
Uint16 ReadAdcValue(void);




#endif /* APP_ADC_H_ */
