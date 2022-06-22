# GPIO  
- GPIO分为三大类：   
  **第一类和第三类寄存器受EALLOW保护**
  1. GPIO控制寄存器  
      - GPxMUXn实现功能选择  
      - GPxDIR控制方向  
      - GP下PUD上拉控制器，使其从不定态到高电平
  2. GPIO数据寄存器  
      - GPxDAT一般用于读取数据
      - GPxSET置位  
      - GPxCLEAR清零
      - GPxTPGGLE电平翻转 
  3. GPIO外部中断源及低功耗唤醒寄存器  