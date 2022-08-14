/*
 * motor.c
 *
 *  Created on: 2022年7月30日
 *      Author: 10758
 */
#include "motor.h"
Uint16 horizontal;
Uint16 vertical;

void InitEPwm3Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)

/* Configure ePWM-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM3 functional pins.
// Comment out other unwanted lines.
    //黄色信号线，红色+5V。棕色接地
    //io4接水平，io5接垂直
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    EDIS;
}

void EPwmSetup(void)
{
    InitEPwm3Gpio();
    EPwm3Regs.TBSTS.all=0;
    EPwm3Regs.TBPHS.half.TBPHS=0;
    EPwm3Regs.TBCTR=0;

    //EPwm2Regs.CMPCTL.all=0x50;        // Immediate mode for CMPA and CMPB
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = 0x0;
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = 0x0;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = 0x0;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = 0x0;
    //1ms 3125
    EPwm3Regs.CMPA.half.CMPA = 4688;
    EPwm3Regs.CMPB= 4688;

    //EPwm3Regs.AQCTLA.all=0x60;        // EPWMxA = 1 when CTR=CMPA and counter inc
                                                             // EPWMxA = 0 when CTR=CMPA and counter dec
    EPwm3Regs.AQCTLA.bit.CBD = 0x0;
    EPwm3Regs.AQCTLA.bit.CBU = 0x0;
    EPwm3Regs.AQCTLA.bit.CAD = 0x0;
    EPwm3Regs.AQCTLA.bit.CAU = 0x1;
    EPwm3Regs.AQCTLA.bit.PRD = 0x0;
    EPwm3Regs.AQCTLA.bit.ZRO = 0x2;
    //EPwm3Regs.AQCTLA.all = 0x0012;

    EPwm3Regs.AQCTLB.bit.CBD = 0x0;
    EPwm3Regs.AQCTLB.bit.CBU = 0x1;
    EPwm3Regs.AQCTLB.bit.CAD = 0x0;
    EPwm3Regs.AQCTLB.bit.CAU = 0x0;
    EPwm3Regs.AQCTLB.bit.PRD = 0x0;
    EPwm3Regs.AQCTLB.bit.ZRO = 0x2;
    //EPwm3Regs.AQCTLB.all = 0x0102;

    EPwm3Regs.AQSFRC.bit.RLDCSF = 0x0;
    EPwm3Regs.AQCSFRC.all=0x0;

    EPwm3Regs.DBCTL.all=0x0;
    EPwm3Regs.DBRED=0;
    EPwm3Regs.DBFED=0;

    EPwm3Regs.TZSEL.all=0;
    EPwm3Regs.TZCTL.all=0;
    EPwm3Regs.TZEINT.all=0;
    EPwm3Regs.TZFLG.all=0;
    EPwm3Regs.TZCLR.all=0;
    EPwm3Regs.TZFRC.all=0;

    EPwm3Regs.ETSEL.all=0;            // Interrupt when TBCTR = 0x0000
    EPwm3Regs.ETFLG.all=0;
    EPwm3Regs.ETCLR.all=0;
    EPwm3Regs.ETFRC.all=0;
    EPwm3Regs.PCCTL.all=0;

    EPwm3Regs.TBPRD=62499;
    EPwm3Regs.TBCTL.bit.FREE_SOFT = 0x2;
    EPwm3Regs.TBCTL.bit.CLKDIV = 0x2;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0x6;
    EPwm3Regs.TBCTL.bit.SYNCOSEL = 0x3;
    EPwm3Regs.TBCTL.bit.PRDLD = 0x0;
    EPwm3Regs.TBCTL.bit.PHSEN = 0x0;
    EPwm3Regs.TBCTL.bit.CTRMODE = 0x0;
}

void MotorConfig(Uint16 horizontal, Uint16 vertical)
{
    EPwm3Regs.CMPA.half.CMPA = horizontal;
    EPwm3Regs.CMPB= vertical;
}

void MotorDegreeConfig(float32 horizontalDeg, float32 verticalDeg)
{
    horizontal = k*horizontalDeg + b;
    vertical = k*verticalDeg + b;
    EPwm3Regs.CMPA.half.CMPA = horizontal;
    EPwm3Regs.CMPB= vertical;
}
