# 蓝牙通信  
## 用法  
- VCC接3.3V  
- GND接地  
- RXD接IO18(IO18复用功能SCIBTXD)   
- TXD接IO19(IO19复用功能SCIBRXD)  
## 功能  
可实现通过手机和28335之间进行数据收发  
## 使用注意  
要完成三步初始化  
```
void InitScibGpio();
void InitScibConfigure();
void InitScibFIFOConfigre();
```  
- 以下为如何把一个两位小数的四位数转化为char类型并发送  
int转char因为char采用的是ascii码即'1'不是数字1  
int转char每个数要加上48来对应ascii码  
```
    Uint16 Tnum1 = num*100;
    Uint16 num0 = Tnum1/1000;
    Uint16 num1 = Tnum1/100%10;
    Uint16 num2 = Tnum1/10%10;
    Uint16 num3 = Tnum1%10;
    char a[7] = {'\n',num0+48,num1+48,'.',num2+48,num3+48,'\0'};
    msg = a;
    scibMsg(msg);
```  
- 以下为如何通过手机发送 
```
      while(ScibRegs.SCIFFRX.bit.RXFFST == 0){}
          do
        {
            recievedChar = ScibRegs.SCIRXBUF.all;
            //手机以char类型发送1，28335以int类型接收要使用1+48=49
            if(recievedChar==49)
            {
                GpioDataRegs.GPCTOGGLE.bit.GPIO68 = 1;

            }
        }while(ScibRegs.SCIFFRX.bit.RXFFST != 0);
```
