#ifndef STEPPER_CONTROLLER_H_
#define STEPPER_CONTROLLER_H_

#include "stm32l4xx_hal.h"

void Stepper_Controller_Init(void);
void Stepper_Controller_MainLoop(void);
int* Get_New_Path();
void Run_Path(int* steps);

#endif // STEPPER_CONTROLLER_H
