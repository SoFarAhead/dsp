#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "Dtube.h"
void main()
{
    InitSysCtrl();
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd, &RamfuncsRunStart);
    InitFlash();
    //初始化数码管
    DtubeInit();
    //数码管动态显示，一定要实时刷新，或保证一定执行次数
    Uint16 k;
    while(1)
    {
        for(k=0;k<200;k++)
        {
            DtubeDisplayFloat(131.4, 1);
        }
        for(k=0;k<200;k++)
        {
            DtubeDisplayInt(520);
        }
    }
}
