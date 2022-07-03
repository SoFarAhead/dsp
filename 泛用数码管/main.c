#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "UniversalDtube.h"
void main()
{
    InitSysCtrl();
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    UniveralDtubeInit();
    while(1)
    {
        DtubeDisplayFloat(131.4, 1);
    }
}
