/* 利用普中DSP28335开发板，
   实现流水灯  
*/

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

void main()
{
    InitSysCtrl();
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;
    while(1)
    {
    GpioCtrlRegs.GPCPUD.bit.GPIO68 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO68 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO68 = 1;
    DELAY_US(1000000);
    GpioDataRegs.GPCSET.bit.GPIO68 = 1;

    GpioCtrlRegs.GPCPUD.bit.GPIO67 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO67 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO67 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO67 = 1;
    DELAY_US(1000000);
    GpioDataRegs.GPCSET.bit.GPIO67 = 1;

    GpioCtrlRegs.GPCPUD.bit.GPIO66 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO66 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO66 = 1;
    DELAY_US(1000000);
    GpioDataRegs.GPCSET.bit.GPIO66 = 1;

    EDIS;
    }
