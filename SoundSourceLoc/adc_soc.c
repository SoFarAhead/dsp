/*
 * adc_soc.c
 *
 *  Created on: 2022年7月18日
 *      Author: 10758
 */
#include "adc_soc.h"

// Global variable for this example
Uint16 SampleTable;
Uint16 j = 0;
Uint16 index = 0;

void ADC_Init()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
    SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Disable TBCLK within the ePWM同步使能要按照顺序，看c2000手册
    //非同步多个epwm好像顺序不重要
    EDIS;

    // Specific clock setting for this example:
    EALLOW;
    SysCtrlRegs.HISPCP.all = ADC_MODCLK;    // HSPCLK = SYSCLKOUT/2*ADC_MODCLK
    //配置为25MHz，为最高adc时钟频率
    EDIS;

    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    EALLOW;  // This is needed to write to EALLOW protected register
    PieVectTable.ADCINT = &adc_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    InitAdc();  // For this example, init the ADC

    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;    // Enable ADCINT in PIE
    IER |= M_INT1; // Enable CPU Interrupt 1
    EINT;          // Enable Global interrupt INTM
    ERTM;          // Enable Global realtime interrupt DBGM

 //   AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;       //相当于FIFO Enable Sequencer override feature
    //设置adc频率
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 2;
    AdcRegs.ADCTRL1.bit.CPS = 1;
    //设置采样窗口大小为16
    AdcRegs.ADCTRL1.bit.ACQ_PS = 16;
    AdcRegs.ADCMAXCONV.all = 0x0001;       // Setup 2 conv's on SEQ1
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x3; // Setup ADCINA3 as 1st SEQ1 conv.
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x2; // Setup ADCINA2 as 2nd SEQ1 conv.

    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;// Enable SOCA from ePWM to start SEQ1
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  // Enable SEQ1 interrupt (every EOS)

    // Assumes ePWM1 clock is already enabled in InitSysCtrl();
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 3;
    EPwm1Regs.TBCTL.bit.CLKDIV = 0;

    EPwm1Regs.ETSEL.bit.SOCAEN = 1;        // Enable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL = 4;       // Select SOC from from CPMA on upcount
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;        // Generate pulse on 1st event
    EPwm1Regs.CMPA.half.CMPA = 0x0080;    // Set compare A value
    EPwm1Regs.TBPRD = 0x1388;              // Set period for ePWM1  0x01F4 50000    0x1388 5000Hz
    EPwm1Regs.TBCTL.bit.CTRMODE = 0;          // count up and start
}


interrupt void  adc_isr()
{

    SampleTable= ( (AdcRegs.ADCRESULT0)>>4);
    SoundBuff1[j] = (float)SampleTable*3.0/4096;
    SampleTable= ( (AdcRegs.ADCRESULT1)>>4);
    SoundBuff2[j] = (float)SampleTable*3.0/4096;
    j++;
    if(j==data_len)
    {
        xcorr(SoundBuff1,SoundBuff2,data_len,R_COVBuff12);
        index = maxidx_SP_RV_2(R_COVBuff12,2*data_len);
        index = index - (data_len-1);
        j = 0;
    }
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
    // Reinitialize for next ADC sequence
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;// Acknowledge interrupt to PIE

    /*
    i++;
    if(i==data_len)
    {
        i = 0;
        //禁止中断
        AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;
        //计算时延
        for(loopVar_1 = -(data_len-1);loopVar_1<=(data_len-1);loopVar_1++)
        {
            if (loopVar_1<0)
            {
                loopVar_3 = 0;
                for(loopVar_3=0;loopVar_3<=(data_len-1+loopVar_1);loopVar_3++)
                {
                    R_COVBuff12[loopVar_2] = R_COVBuff12[loopVar_2] + SoundBuff1[loopVar_3]*SoundBuff2[loopVar_3-loopVar_1];
                }
                loopVar_2++;

            }
            if (loopVar_1>=0)
            {
                loopVar_3 = 0;
                for(loopVar_3=loopVar_1;loopVar_3<=(data_len-1);loopVar_3++)
                {
                    R_COVBuff12[loopVar_2] = R_COVBuff12[loopVar_2] + SoundBuff1[loopVar_3]*SoundBuff2[loopVar_3-loopVar_1];
                }
                loopVar_2++;
            }
        }
        index = maxidx_SP_RV_2(R_COVBuff12,(2*data_len - 1));
        DELAY_US(100000);

    }
     */

}

void xcorr(float32 *x,float32 *y,int n,float32 *r)
{
    int k=0;
    int i=0;//求和次数
    int wLength = n+n-1;//相关输出序列的长度
    for(k=0;k<wLength;k++)
    {
        *(r+k) = 0;
        for(i=(0>k+1-n?0:k+1-n);i<=(k<n-1?k:n-1);i++)
        {
            *(r+k) +=(*(x+k-i)) *(*(y+n-1-i));
        }
    }
}
