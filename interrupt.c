#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

interrupt void ISRTime0(void);
void main()
{
    //初始系统
    InitSysCtrl();
    //初始GPIO
    InitGpio();
    //禁止和清楚CPU中断
    DINT;

    IER = 0x0000;
    IFR = 0x0000;
    //初始PIE
    InitPieCtrl();
    //初始PIE向量表
    InitPieVectTable();
    //传递中断函数地址
    EALLOW;
    PieVectTable.TINT0 = &ISRTime0;
    EDIS;
    //初始化要产生中断的外设
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 150, 1000000);
    StartCpuTimer0();
    //使能CPU中断1
    IER |= M_INT1;
    //使能PIE中断位
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
  
    EINT;   //使能全局中断
    ERTM;   //使能全局实时中断

    //配置中断前状态
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO68 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO68 = 1;
    GpioDataRegs.GPCDAT.bit.GPIO68 = 1;
    EDIS;
    while(1);
}


interrupt void ISRTime0(void)
{
    //中断函数
    GpioDataRegs.GPCDAT.bit.GPIO68 = ~GpioDataRegs.GPCDAT.bit.GPIO68;
    //清楚PIEACK和TIF
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;
    CpuTimer0Regs.TCR.bit.TIF = 1;
    //重新填充定时器
    CpuTimer0Regs.TCR.bit.TRB = 1;
}