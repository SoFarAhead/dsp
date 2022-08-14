/*
 * adc_soc.h
 *
 *  Created on: 2022��7��18��
 *      Author: 10758
 */

#ifndef APP_ADC_SOC_H_
#define APP_ADC_SOC_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "FPU.h"

#define ADC_MODCLK 3
#define data_len  256
//ʹ֮���Ա��ⲿ�ļ�����
extern float32 SoundBuff1[data_len];
extern float32 SoundBuff2[data_len];
extern float32 R_COVBuff12[2*data_len];

void ADC_Init();
interrupt void  adc_isr();
//��غ���,u,vΪ���룬wΪ���,nΪ����
void xcorr(float32 *x,float32 *y,int n,float32 *r);


#endif /* APP_ADC_SOC_H_ */
