#include "Dtube.h"

unsigned char Dtubeduan[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
             0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};//0~F 数码管段选数据
            //Dtubeduan[0]对应0011 1111对应数码管八个LED灯

void DtubeInit(void)
{
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;

    GpioCtrlRegs.GPBPUD.bit.GPIO56 =0;
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO56 = 1;

    GpioCtrlRegs.GPBPUD.bit.GPIO54 =0;
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO54 = 1;

    GpioCtrlRegs.GPCPUD.bit.GPIO70 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO70 = 1;

    GpioCtrlRegs.GPCPUD.bit.GPIO71 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO71 = 1;

    GpioCtrlRegs.GPCPUD.bit.GPIO72 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO72 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO72 = 1;

    GpioCtrlRegs.GPCPUD.bit.GPIO73 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO73 = 1;

    EDIS;

    GpioDataRegs.GPCCLEAR.bit.GPIO70 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO71 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO72 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO73 = 1;

}

void HC146SendData(unsigned char data)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {   
        //74HC146是一个移位寄存器，通过GPIO下降沿来模拟时钟信号
        SPICLKA_SETL;
        if(data&0x80)//判断最高位的0，1状态，完成后左移
            SPISIMOA_SETH;
        else
            SPISIMOA_SETL;
        SPICLKA_SETH;
        data<<=1;


    }
}

void DtubeDisplayInt(Uint16 num )
{
    unsigned char SprtNum[4];
    unsigned char i=0;
    //将4位数以编码后的形式存储在SprtNum数组中
    SprtNum[0] = Dtubeduan[num/1000];
    SprtNum[1] = Dtubeduan[(num%1000)/100];
    SprtNum[2] = Dtubeduan[(num%1000%100)/10];
    SprtNum[3] = Dtubeduan[(num%1000%100%10)];
    //点亮4次数码管
    for(i=0;i<4;i++)
    {
        HC146SendData(SprtNum[i]);
        switch(i)
        {
        case 0: SEG1_SETH;SEG2_SETL;SEG3_SETL;SEG4_SETL;break;
        case 1: SEG1_SETL;SEG2_SETH;SEG3_SETL;SEG4_SETL;break;
        case 2: SEG1_SETL;SEG2_SETL;SEG3_SETH;SEG4_SETL;break;
        case 3: SEG1_SETL;SEG2_SETL;SEG3_SETL;SEG4_SETH;break;
        }
        DELAY_US(5000);
    }
}

void DtubeDisplayFloat(float num, unsigned char dotnum)
{
    unsigned char SprtNum[4];
    unsigned char i=0;
    Uint16 value;
    //在需要输入小数点的地方|0x80来置为数码管小数点位
    switch(dotnum)
    {
    case 1: value=num*10;SprtNum[0] = Dtubeduan[value/1000];SprtNum[1] = Dtubeduan[(value%1000)/100];(SprtNum[2] = Dtubeduan[(value%1000%100)/10]|0x80);SprtNum[3] = Dtubeduan[(value%1000%100%10)];break;
    case 2: value=num*100;SprtNum[0] = Dtubeduan[value/1000];(SprtNum[1] = Dtubeduan[(value%1000)/100]|0x80);SprtNum[2] = Dtubeduan[(value%1000%100)/10];SprtNum[3] = Dtubeduan[(value%1000%100%10)];break;
    case 3: value=num*1000;SprtNum[0] = (Dtubeduan[value/1000]|0x80);SprtNum[1] = Dtubeduan[(value%1000)/100];SprtNum[2] = Dtubeduan[(value%1000%100)/10];SprtNum[3] = Dtubeduan[(value%1000%100%10)];break;
    }
    for(i=0;i<4;i++)
    {
        HC146SendData(SprtNum[i]);
        switch(i)
        {
        case 0: SEG1_SETH;SEG2_SETL;SEG3_SETL;SEG4_SETL;break;
        case 1: SEG1_SETL;SEG2_SETH;SEG3_SETL;SEG4_SETL;break;
        case 2: SEG1_SETL;SEG2_SETL;SEG3_SETH;SEG4_SETL;break;
        case 3: SEG1_SETL;SEG2_SETL;SEG3_SETL;SEG4_SETH;break;
        }
        DELAY_US(5000);
    }

}




