/*
 * motor.h
 *
 *  Created on: 2022��7��30��
 *      Author: 10758
 */

#ifndef APP_MOTOR_H_
#define APP_MOTOR_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define k   34.722
#define b   1563

void InitEPwm3Gpio(void);
void EPwmSetup(void);
//ˮƽ����-90�����ұߣ���ֱ����-90�����±�
void MotorConfig(Uint16 horizontal, Uint16 vertical);
void MotorDegreeConfig(float32 horizontalDeg, float32 verticalDeg);

#endif /* APP_MOTOR_H_ */
