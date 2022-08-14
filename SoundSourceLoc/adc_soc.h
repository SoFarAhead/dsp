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
#include "FPU.h"

#define ADC_MODCLK 3
#define data_len  256
//使之可以被外部文件引用
extern float32 SoundBuff1[data_len];
extern float32 SoundBuff2[data_len];
extern float32 R_COVBuff12[2*data_len];

void ADC_Init();
interrupt void  adc_isr();
//相关函数,u,v为输入，w为输出,n为长度
void xcorr(float32 *x,float32 *y,int n,float32 *r);


#endif /* APP_ADC_SOC_H_ */
