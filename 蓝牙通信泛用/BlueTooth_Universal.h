/*
 * BlueTooth_Universal.h
 *
 *  Created on: 2022年7月7日
 *      Author: 10758
 */

#ifndef APP_BLUETOOTH_UNIVERSAL_H_
#define APP_BLUETOOTH_UNIVERSAL_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

void InitScibGpio();
void InitScibConfigure();
void InitScibFIFOConfigre();
void scibXmit(int a);
void scibMsg(char * msg);



#endif /* APP_BLUETOOTH_UNIVERSAL_H_ */
