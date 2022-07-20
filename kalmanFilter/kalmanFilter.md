具体文件看CCS工程adc_kalmanFilter   
卡尔曼滤波最重要的是调整三个参数： 
- init_p    estimated error convariance
- q         predict noise convariance   
- r         measure error convariance     
调参可参见温度传感器的参数     