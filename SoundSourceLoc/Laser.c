/*
 * Laser.c
 *
 *  Created on: 2022Äê7ÔÂ29ÈÕ
 *      Author: 10758
 */
#include "Laser.h"

void LaserInit()
{
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO74 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO74 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO74 = 1;
    EDIS;
    GpioDataRegs.GPCCLEAR.bit.GPIO74 = 1;
}

void LaserOn()
{
    GpioDataRegs.GPCSET.bit.GPIO74 = 1;
}

void LaserOff()
{
    GpioDataRegs.GPCCLEAR.bit.GPIO74 = 1;
}
