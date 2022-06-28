/*
 * Dtube.h
 *
 *  Created on: 2022年6月27日
 *      Author: 10758
 */

#ifndef APP_DTUBE_H_
#define APP_DTUBE_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define SPICLKA_SETH (GpioDataRegs.GPBSET.bit.GPIO56=1)
#define SPICLKA_SETL (GpioDataRegs.GPBCLEAR.bit.GPIO56=1)
#define SPISIMOA_SETH (GpioDataRegs.GPBSET.bit.GPIO54=1)
#define SPISIMOA_SETL (GpioDataRegs.GPBCLEAR.bit.GPIO54=1)
#define SEG1_SETH (GpioDataRegs.GPCSET.bit.GPIO70=1)
#define SEG1_SETL (GpioDataRegs.GPCCLEAR.bit.GPIO70=1)
#define SEG2_SETH (GpioDataRegs.GPCSET.bit.GPIO71=1)
#define SEG2_SETL (GpioDataRegs.GPCCLEAR.bit.GPIO71=1)
#define SEG3_SETH (GpioDataRegs.GPCSET.bit.GPIO72=1)
#define SEG3_SETL (GpioDataRegs.GPCCLEAR.bit.GPIO72=1)
#define SEG4_SETH (GpioDataRegs.GPCSET.bit.GPIO73=1)
#define SEG4_SETL (GpioDataRegs.GPCCLEAR.bit.GPIO73=1)

void DtubeInit(void);
void HC146SendData(unsigned char data);
void DtubeDisplayInt(Uint16 num );
void DtubeDisplayFloat(float num, unsigned char dotnum);




#endif /* APP_DTUBE_H_ */
