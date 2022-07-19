## Description   
这是一个基于epwm发出启动信号来启动adc采样,采样频率通过设置epwm来决定。  
## Usage  
导入文件，在`main.c`中初始化函数`ADC_Init()`，通过中断采样，采样值保存在变量`SampleTable`。
### 如何修改采样频率   
在代码   
```    
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 3;
    EPwm1Regs.TBCTL.bit.CLKDIV = 0;
```
和
```
 EPwm1Regs.TBPRD = 0x01F4;              // Set period for ePWM1
 ```
 epwm频率TBCLK = SYSCLKOUT/(2*HSPCLKDIV)*2^CLKDIV   
 采样频率为TBCLK/TBPRD 