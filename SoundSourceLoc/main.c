#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "Laser.h"
#include "adc_soc.h"
#include "motor.h"
#include "FPU.h"

#define data_len  256
#define Testdata_len    8

#pragma DATA_SECTION(SoundBuff1,"Sounddata1");
float32 SoundBuff1[data_len] = {0.0};

#pragma DATA_SECTION(SoundBuff2,"Sounddata2");
float32 SoundBuff2[data_len] = {0.0};

#pragma DATA_SECTION(R_COVBuff12,"R_COVBuffdata12");
float32 R_COVBuff12[2*data_len];
//测试变量
/*
int16 TestloopVar_1 = 0;
int16 TestloopVar_2 = 0;
int16 TestloopVar_3 = 0;
Uint16 Testindex;
*/
/*
float32 TestSoundBuff2[Testdata_len] = {17,9,1,5,6,7,29,33,};
float32 TestSoundBuff1[Testdata_len] = {9,1,5,6,7,29,33,17};
float32 TestR_COVBuff12[2*Testdata_len];
int Testindex;
*/
/*
#define CFFT_STAGES 4
#define CFFT_SIZE   (1 << CFFT_STAGES)

float   CFFTin1Buff[CFFT_SIZE*2] = {5,0,6,0,7,0,17,0,28,0,33,0,9,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};               //CFFT_f32u(optional), CFFT_f32(required)
                                                //Output of FFT overwrites input if
                                                //CFFT_STAGES is ODD
float   CFFTin2Buff[CFFT_SIZE*2];               //Additional Buffer used in Magnitude calc
float   CFFToutBuff[CFFT_SIZE*2];               //Output of FFT here if CFFT_STAGES is EVEN
float   CFFTF32Coef[CFFT_SIZE];                 //Twiddle buffer

float   YCFFTin1Buff[CFFT_SIZE*2] = {1,0,5,0,6,0,7,0,17,0,28,0,33,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};               //CFFT_f32u(optional), CFFT_f32(required)
                                                //Output of FFT overwrites input if
                                                //CFFT_STAGES is ODD
float   YCFFTin2Buff[CFFT_SIZE*2];               //Additional Buffer used in Magnitude calc
float   YCFFToutBuff[CFFT_SIZE*2];               //Output of FFT here if CFFT_STAGES is EVEN
float   YCFFTF32Coef[CFFT_SIZE];                 //Twiddle buffer

Uint16  conjSize = CFFT_SIZE*2;
CFFT_F32_STRUCT cfft;
CFFT_F32_STRUCT Ycfft;
complex_float Xw[CFFT_SIZE];
complex_float Yw[CFFT_SIZE];
complex_float Rw[CFFT_SIZE];
complex_float Outw[CFFT_SIZE];
float absRw[CFFT_SIZE];
complex_float RwFilter[CFFT_SIZE];
float output[CFFT_SIZE];
*/
void main()
{
    R_COVBuff12[2*data_len - 1] = 0.0;
    InitSysCtrl();
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    //float32 degHorizont = 90.0;
    //float32 degVertical = 10.0;
    InitPieVectTable();
    //初始化激光笔并关闭
    //LaserInit();
    /*
    DELAY_US(1000);
    xcorr(TestSoundBuff1, TestSoundBuff2, Testdata_len, TestR_COVBuff12);
    Testindex = maxidx_SP_RV_2(TestR_COVBuff12, 2*Testdata_len);
    Testindex = Testindex - (Testdata_len-1);
    */
    ADC_Init();
    for(;;);
    //EPwmSetup();
    //LaserOn();
    //LaserOff();

    /*
    cfft.CoefPtr = CFFTF32Coef;             //Twiddle factor table
    cfft.InPtr   = CFFTin1Buff;             //Input/output or middle stage of ping-pong buffer
    cfft.OutPtr  = CFFToutBuff;             //Output or middle stage of ping-pong buffer
    cfft.Stages  = CFFT_STAGES;             // FFT stages
    cfft.FFTSize = CFFT_SIZE;               // FFT size
    CFFT_f32_sincostable(&cfft);            // Calculate twiddle factor
    CFFT_f32(&cfft);                        // Calculate FFT

    Ycfft.CoefPtr = YCFFTF32Coef;             //Twiddle factor table
    Ycfft.InPtr   = YCFFTin1Buff;             //Input/output or middle stage of ping-pong buffer
    Ycfft.OutPtr  = YCFFToutBuff;             //Output or middle stage of ping-pong buffer
    Ycfft.Stages  = CFFT_STAGES;             // FFT stages
    Ycfft.FFTSize = CFFT_SIZE;               // FFT size
    CFFT_f32_sincostable(&Ycfft);            // Calculate twiddle factor
    CFFT_f32(&Ycfft);                        // Calculate FFT


    Uint16 i;
    Uint16 index;
    for(i=0;i<(CFFT_SIZE);i++)
    {
        Xw[i].dat[0] = CFFToutBuff[2*i];
        Xw[i].dat[1] = CFFToutBuff[2*i+1];
        Yw[i].dat[0] = YCFFToutBuff[2*i];
        Yw[i].dat[1] = YCFFToutBuff[2*i+1];
    }
    //求Xw与Yw的复共轭乘
    mpy_SP_CVxCVC(Rw, Xw, Yw, CFFT_SIZE);
    //取绝对值的倒数
    iabs_SP_CV_2(absRw, Rw, CFFT_SIZE);
    //滤波后向量
    mpy_SP_RVxCV(RwFilter, Rw, absRw, CFFT_SIZE);

    for(i=0;i<(CFFT_SIZE);i++)
    {
        CFFTin1Buff[2*i] = RwFilter[i].dat[0];
        CFFTin1Buff[2*i+1] = RwFilter[i].dat[1];
    }
    cfft.InPtr = CFFTin1Buff;              // ICFFT input pointer
    cfft.OutPtr = CFFToutBuff;             // ICFFT output pointer
    ICFFT_f32(&cfft);                      // Calculate the ICFFT
    for(i=0;i<(CFFT_SIZE);i++)
    {
        Outw[i].dat[0] = CFFToutBuff[2*i];
        Outw[i].dat[1] = CFFToutBuff[2*i+1];
    }
    abs_SP_CV_2(output, Outw, CFFT_SIZE);
    index = maxidx_SP_RV_2(output, CFFT_SIZE);
    DELAY_US(100000);
    */
}
