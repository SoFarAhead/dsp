/*
 * Universal_Dtube.c
 *
 *  Created on: 2022年7月3日
 *      Author: 10758
 */
#include "UniversalDtube.h"

unsigned char DtubeNum[18]={
//01234567
0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
//89ABCDEF
0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,
//熄灭 .
0xFF,0x7F};
//共阳数码管段码“0123456789AbCdEF熄灭 . ”
unsigned char DtubeSituation[4]={0x01,0x02,0x04,0x08};
//第一位至第四位位码

void UniveralDtubeInit(void)
{
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO70 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO70 = 1;

    GpioCtrlRegs.GPCPUD.bit.GPIO71 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO71 = 1;

    GpioCtrlRegs.GPCPUD.bit.GPIO72 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO72 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO72 = 1;
    EDIS;
}

void HC585SendData(unsigned char data)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        SPICLKA_SETL;
        if(data&0x80)
            SPISIMOA_SETH;
        else
            SPISIMOA_SETL;
        SPICLKA_SETH;
        data<<=1;
    }


}

void DtubeDisplayInt(Uint16 num)
{
    unsigned char SprtNum[4];
    unsigned char i=0;
    SprtNum[3] = DtubeNum[num/1000];
    SprtNum[2] = DtubeNum[(num%1000)/100];
    SprtNum[1] = DtubeNum[(num%1000%100)/10];
    SprtNum[0] = DtubeNum[(num%1000%100%10)];
    for(i=0;i<4;i++)
    {
        HC585SendData(SprtNum[i]);
        HC585SendData(DtubeSituation[i]);
        GpioDataRegs.GPCCLEAR.bit.GPIO72=1;
        GpioDataRegs.GPCSET.bit.GPIO72=1;
        DELAY_US(5000);
    }

}

void DtubeDisplayFloat(float num, unsigned char dotnum)
{
    unsigned char SprtNum[4];
    unsigned char i=0;
    Uint16 value;
    switch(dotnum)
    {
        case 1:
            value=num*10;
            SprtNum[3] = DtubeNum[value/1000];
            SprtNum[2] = DtubeNum[(value%1000)/100];
            SprtNum[1] = DtubeNum[(value%1000%100)/10]&0x7F;
            SprtNum[0] = DtubeNum[(value%1000%100%10)];
            break;
        case 2:
            value=num*100;
            SprtNum[3] = DtubeNum[value/1000];
            SprtNum[2] = DtubeNum[(value%1000)/100]&0x7F;
            SprtNum[1] = DtubeNum[(value%1000%100)/10];
            SprtNum[0] = DtubeNum[(value%1000%100%10)];
            break;
        case 3:
            value=num*1000;
            SprtNum[3] = DtubeNum[value/1000]&0x7F;
            SprtNum[2] = DtubeNum[(value%1000)/100];
            SprtNum[1] = DtubeNum[(value%1000%100)/10];
            SprtNum[0] = DtubeNum[(value%1000%100%10)];
            break;
    }
    for(i=0;i<4;i++)
    {
        HC585SendData(SprtNum[i]);
        HC585SendData(DtubeSituation[i]);
        GpioDataRegs.GPCCLEAR.bit.GPIO72=1;
        GpioDataRegs.GPCSET.bit.GPIO72=1;
        DELAY_US(5000);
    }

}