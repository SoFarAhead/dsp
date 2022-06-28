#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "stdio.h"
#include "string.h"

#define ADC_MODCLK 0x3
#define ADC_SHCLK  0x1
#define ADC_CKPS   0x0
#define BUF_SIZE   16  //缓存大小，采样后占用的大小
#define OFFSET     0

void main()
{
    Uint16 i;
    Uint16 array_index;
    //简简单单点个灯
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO68 =0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO68 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO68 = 1;
    EDIS;

    InitSysCtrl();
    asm(" RPT #8 || NOP");  //注意格式  其意思好像是等待9个周期

    InitPieCtrl();
    DINT;
    InitFlash();
    //貌似没有使用中断（大雾）或者说是想关闭中断？
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    asm(" RPT #8 || NOP");

    InitAdc();
    //配置高速时钟 HSPCLK = SYSCLKOUT/(2*ADC_MODCLK) = 150/(2*3) = 25MHz
    EALLOW;
    SysCtrlRegs.HISPCP.all = ADC_MODCLK;
    EDIS;
    //设置采样保持其宽度为（ADC_SHCLK+1）*ADC时钟周期，可理解为设置采样频率
    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;
    //设定ADC时钟 等于HSPCLK/1 = 25MHz
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;   //设置为级联方式
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;  //设置为顺序采样
    //设置采样顺序
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;

    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;

    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;
    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0xA;
    AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xB;

    AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0xC;
    AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0xD;
    AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0xE;
    AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0xF;
    //启动连续转换模式
    AdcRegs.ADCTRL1.bit.CONT_RUN = 1;
    AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;
    //设置转换通道数为16
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0xF;
    DINT;
    //初始化缓存
    float32 SampleTable[BUF_SIZE-1] = 0;

    //启动SEQ1
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;

    while(1)
    {
        array_index = 0;
        for(i = 0;i<(BUF_SIZE/16);i++)
        {
            while (AdcRegs.ADCST.bit.INT_SEQ1 == 0){}   //等待直到完成
            AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;         //清除标志位
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT0>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT1>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT2>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT3>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT4>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT5>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT6>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT7>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT8>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT9>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT10>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT11>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT12>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT13>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT14>>4)*3.0/4095.0 - OFFSET);
            SampleTable[array_index++] = ((AdcRegs.ADCRESULT15>>4)*3.0/4095.0 - OFFSET);
        }
    }


}
