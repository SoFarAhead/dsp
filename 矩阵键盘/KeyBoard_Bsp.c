/*
 * KeyBoard_Bsp.c
 *
 *  Created on: 2022年7月26日
 *      Author: 10758
 */
#include "KeyBoard_Bsp.h"

Uint16 key[4];
Uint16 i = 0;
Uint16 j = 0;
Uint16 count = 0;
Uint16 countTime = 0;

void KeyBoardInit()
{
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;
    //选择通用GPIO模式
    GpioCtrlRegs.GPCMUX2.bit.GPIO80 = 0;
    GpioCtrlRegs.GPCMUX2.bit.GPIO81 = 0;
    GpioCtrlRegs.GPCMUX2.bit.GPIO82 = 0;
    GpioCtrlRegs.GPCMUX2.bit.GPIO83 = 0;
    GpioCtrlRegs.GPCMUX2.bit.GPIO84 = 0;
    GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 0;
    GpioCtrlRegs.GPCMUX2.bit.GPIO86 = 0;
    GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 0;
    //先禁止所以上拉（禁止是置1，使能是置0）
    GpioCtrlRegs.GPCPUD.bit.GPIO80 =0;
    GpioCtrlRegs.GPCPUD.bit.GPIO81 =0;
    GpioCtrlRegs.GPCPUD.bit.GPIO82 =0;
    GpioCtrlRegs.GPCPUD.bit.GPIO83 =0;
    GpioCtrlRegs.GPCPUD.bit.GPIO84 =0;
    GpioCtrlRegs.GPCPUD.bit.GPIO85 =0;
    GpioCtrlRegs.GPCPUD.bit.GPIO86 =0;
    GpioCtrlRegs.GPCPUD.bit.GPIO87 =0;
    //设置为输出模式
    GpioCtrlRegs.GPCDIR.bit.GPIO80 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO81 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO82 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO83 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO84 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO85 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO86 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO87 = 0;

    EDIS;
    //设置列低电平

    GpioDataRegs.GPCCLEAR.bit.GPIO83 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO82 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO81 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO80 = 1;
}

void KeyBoardScan()
{
    for(;;)
        {
            EALLOW;
            //设置为输出模式
            GpioCtrlRegs.GPCDIR.bit.GPIO80 = 1;
            GpioCtrlRegs.GPCDIR.bit.GPIO81 = 1;
            GpioCtrlRegs.GPCDIR.bit.GPIO82 = 1;
            GpioCtrlRegs.GPCDIR.bit.GPIO83 = 1;
            GpioCtrlRegs.GPCDIR.bit.GPIO84 = 0;
            GpioCtrlRegs.GPCDIR.bit.GPIO85 = 0;
            GpioCtrlRegs.GPCDIR.bit.GPIO86 = 0;
            GpioCtrlRegs.GPCDIR.bit.GPIO87 = 0;
            //设置列低电平

            GpioDataRegs.GPCCLEAR.bit.GPIO83 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO82 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO81 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO80 = 1;
            EDIS;
            DELAY_US(1000);
            if(((GpioDataRegs.GPCDAT.bit.GPIO87&&GpioDataRegs.GPCDAT.bit.GPIO86)&&(GpioDataRegs.GPCDAT.bit.GPIO85&&GpioDataRegs.GPCDAT.bit.GPIO84))==0)
            {
            DELAY_US(10000);
            if(GpioDataRegs.GPCDAT.bit.GPIO87==0)
            {
                i = 1;
            }
            else if(GpioDataRegs.GPCDAT.bit.GPIO86==0)
            {
                i = 3;
            }
            else if(GpioDataRegs.GPCDAT.bit.GPIO85==0)
            {
                i = 2;
            }
            else if(GpioDataRegs.GPCDAT.bit.GPIO84==0)
            {
                i = 4;
            }
            EALLOW;
            //设置为输出模式
            GpioCtrlRegs.GPCDIR.bit.GPIO80 = 0;
            GpioCtrlRegs.GPCDIR.bit.GPIO81 = 0;
            GpioCtrlRegs.GPCDIR.bit.GPIO82 = 0;
            GpioCtrlRegs.GPCDIR.bit.GPIO83 = 0;
            GpioCtrlRegs.GPCDIR.bit.GPIO84 = 1;
            GpioCtrlRegs.GPCDIR.bit.GPIO85 = 1;
            GpioCtrlRegs.GPCDIR.bit.GPIO86 = 1;
            GpioCtrlRegs.GPCDIR.bit.GPIO87 = 1;
            //设置行低电平

            GpioDataRegs.GPCCLEAR.bit.GPIO87 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO86 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO85 = 1;
            GpioDataRegs.GPCCLEAR.bit.GPIO84 = 1;
            EDIS;
            DELAY_US(10000);
            if(GpioDataRegs.GPCDAT.bit.GPIO83==0)
            {
                j = 4;
            }
            else if(GpioDataRegs.GPCDAT.bit.GPIO82==0)
            {
                j = 3;
            }
            else if(GpioDataRegs.GPCDAT.bit.GPIO81==0)
            {
                j = 2;
            }
            else if(GpioDataRegs.GPCDAT.bit.GPIO80==0)
            {
                j = 1;
            }
            while(((GpioDataRegs.GPCDAT.bit.GPIO83&&GpioDataRegs.GPCDAT.bit.GPIO82)&&(GpioDataRegs.GPCDAT.bit.GPIO81&&GpioDataRegs.GPCDAT.bit.GPIO80))==0)
            {}
            key[count] = j*1000 + i*10;
            count++;
            if(count==4)
            {
                count = 0;
                break;
            }
        }
    }
}
