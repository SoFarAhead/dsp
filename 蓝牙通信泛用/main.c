#include <stdio.h>
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "BlueTooth_Universal.h"
#include "adc.h"
#include "UniversalDtube.h"
void main()
{
    char * msg;
    int recievedChar;
    float k = -19.3678;
    float b = 55.9848;
    float adcValue;
    Uint16 num0;
    Uint16 num1;
    Uint16 num2;
    Uint16 num3;
    InitSysCtrl();
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO68 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO68 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO68 = 1;
    EDIS;

    AdcInit();
    UniveralDtubeInit();
    InitScibGpio();
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    InitScibFIFOConfigre();
    InitScibConfigure();
    for(;;)
    {   /*温度计发送
        adcValue = (float)ReadAdcValue()*3.0/4096;
        adcValue = k*adcValue + b;
        DtubeDisplayFloat(adcValue, 2);
        msg = "\nEnter a character\0";
        scibMsg(msg);
        Uint16 Tnum1 = adcValue*100;
        num0 = Tnum1/1000;
        num1 = Tnum1/100%10;
        num2 = Tnum1/10%10;
        num3 = Tnum1%10;
        char a[7] = {'\n',num0+48,num1+48,'.',num2+48,num3+48,'\0'};
        msg = "\nYou sent\n\0";
        msg = a;
        scibMsg(msg);
        */
          while(ScibRegs.SCIFFRX.bit.RXFFST == 0){}
          do
        {
            recievedChar = ScibRegs.SCIRXBUF.all;
//            scibXmit(recievedChar);
            if(recievedChar==49)
            {
                GpioDataRegs.GPCTOGGLE.bit.GPIO68 = 1;

            }
        }while(ScibRegs.SCIFFRX.bit.RXFFST != 0);


    }
    /*以下为如何把一个两位小数的四位数转化为char类型并发送
     * int转char因为char采用的是ascii码即'1'不是数字1
     * int转char每个数要加上48来对应ascii码
    Uint16 Tnum1 = num*100;
    Uint16 num0 = Tnum1/1000;
    Uint16 num1 = Tnum1/100%10;
    Uint16 num2 = Tnum1/10%10;
    Uint16 num3 = Tnum1%10;
    char a[7] = {'\n',num0+48,num1+48,'.',num2+48,num3+48,'\0'};
    msg = a;
    scibMsg(msg);
    while(1)
    {
    DELAY_US(1000000);
    scibMsg(msg);
    }
    */
}

