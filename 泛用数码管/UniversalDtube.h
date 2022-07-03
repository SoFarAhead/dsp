/*
 * UniversalDtube.h
 *
 *  Created on: 2022年7月3日
 *      Author: 10758
 */

#ifndef APP_UNIVERSALDTUBE_H_
#define APP_UNIVERSALDTUBE_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#define SPICLKA_SETH (GpioDataRegs.GPCSET.bit.GPIO71=1)
#define SPICLKA_SETL (GpioDataRegs.GPCCLEAR.bit.GPIO71=1)
#define SPISIMOA_SETH (GpioDataRegs.GPCSET.bit.GPIO70=1)
#define SPISIMOA_SETL (GpioDataRegs.GPCCLEAR.bit.GPIO70=1)

void UniveralDtubeInit(void);
void HC585SendData(unsigned char data);
void DtubeDisplayInt(Uint16 num);
void DtubeDisplayFloat(float num, unsigned char dotnum);




#endif /* APP_UNIVERSALDTUBE_H_ */
