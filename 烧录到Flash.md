- 第一步：把28335_RAM_lnk.cmd这个从project中移除，用右键选择28335_RAM_lnk.cmd然后选delate。   
- 第二步：取消CMD中F28335.cmd的编译屏蔽  
- 第三步：在main()函数中添加如下语句   

MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd, &RamfuncsRunStart);   
InitFlash();  

**上述两句话添加在InitPieVectTable();这句的下面的一行。**  

可以将Flash中函数搬移到raw中来提高运行速度  