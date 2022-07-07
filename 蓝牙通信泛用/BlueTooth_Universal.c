/*
 * BlueTooth_Universal.c
 *
 *  Created on: 2022年7月5日
 *      Author: 10758
 */
#include "BlueTooth_Universal.h"

void InitScibGpio()
{
    EALLOW;
    //保证无信号是为高电平，对于通信的稳定很重要
    //sci通信四个连续低电平为有效位
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;
    //接收异步信号
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;    //19为接收引脚
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;    //18为发送引脚

    EDIS;
}

void InitScibConfigure()
{
    ScibRegs.SCICCR.all = 0x0007;   //一个结束位，无校验位，8数据位
    //使能发送接收
    ScibRegs.SCICTL1.all = 0x0003;
    //使能接收发送中断
    ScibRegs.SCICTL2.all = 0x0003;
    ScibRegs.SCICTL2.bit.RXBKINTENA = 1;
    ScibRegs.SCICTL2.bit.TXINTENA = 1;
    #if(CPU_FRQ_150MHZ)
        ScibRegs.SCIHBAUD = 0x0001;     //数据传输9600
        ScibRegs.SCILBAUD = 0x00E7;
    #endif

    #if(CPU_FRQ_100MHZ)
        ScibRegs.SCIHBAUD = 0x0001;     //数据传输9600
        ScibRegs.SCILBAUD = 0x0044;
    #endif
    //重启Sci
    ScibRegs.SCICTL1.all = 0x0023;



}

void InitScibFIFOConfigre()
{
    ScibRegs.SCIFFTX.all = 0xE040;
    ScibRegs.SCIFFRX.all = 0x204F;
    ScibRegs.SCIFFCT.all = 0x0;
}

void scibXmit(int a)
{
    while(ScibRegs.SCIFFTX.bit.TXFFST!=0){}
    ScibRegs.SCITXBUF = a;
}

void scibMsg(char * msg)
{
    int i=0;
    while(msg[i]!='\0')
    {
        scibXmit(msg[i]);
        i++;
    }
}
