# 矩阵键盘  
## Description  
原理是采样行列刷新检测的方法，具体是先将行四位设为输入，列四位为输出高电平，当按键按下是，行有一位从高电平变为低电平。再翻转输入输出，从而知道列的状态   
## Usage    
C4接IO87  
C3接IO86 
C2接IO85  
C1接IO84  
R1接IO83  
R2接IO82  
R3接IO81  
R4接IO80  
- 按键检测值保存在数组key[]中    
- 调整数组大小和数值对应命令可实现控制  

参见主函数代码   
``` 
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "UniversalDtube.h"
#include "KeyBoard_Bsp.h"

extern Uint16 key[4];
extern Uint16 count;
extern Uint16 countTime;

void main()
{
    InitSysCtrl();
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    UniveralDtubeInit();
    KeyBoardInit();
    KeyBoardScan();

    //i为列，j为行


    while(1)
    {
    for(count=0;count<4;count++)
    {
        for(countTime=0;countTime<100;countTime++)
        {
        DtubeDisplayInt(key[count]);
        }
    }
    }

}

```   