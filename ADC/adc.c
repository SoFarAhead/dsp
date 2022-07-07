/*
 * adc.c
 *
 *  Created on: 2022年6月28日
 *      Author: 10758
 */
#include "adc.h"

void AdcInit(void)
{
    EALLOW;
    SysCtrlRegs.HISPCP.all = ADC_MODCLK;
    EDIS;
    InitAdc();

    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;   //设置为级联方式
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;  //设置为顺序采样
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x1;
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x0;
    AdcRegs.ADCTRL1.bit.CONT_RUN = 1;       // 打开连续转换模式
    //启动ADC
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;

}

Uint16 ReadAdcValue(void)
{
    while (AdcRegs.ADCST.bit.INT_SEQ1== 0);
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    return AdcRegs.ADCRESULT0>>4;
}


