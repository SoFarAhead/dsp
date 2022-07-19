/*
 * adc_soc.h
 *
 *  Created on: 2022年7月18日
 *      Author: 10758
 */

#ifndef APP_ADC_SOC_H_
#define APP_ADC_SOC_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define ADC_MODCLK 3

//使之可以被外部文件引用
extern Uint16 SampleTable;

void ADC_Init();
interrupt void  adc_isr();



#endif /* APP_ADC_SOC_H_ */
