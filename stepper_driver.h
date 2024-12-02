#ifndef STEPPER_DRIVER_H_
#define STEPPER_DRIVER_H_

#include "stm32l4xx_hal.h" // Adjust based on your STM32 series

// Define the GPIO pins for each input (match these to your actual wiring)

void Stepper_Driver_Init(void);
void Step_Forward(int phase);
void Step_Backward(int phase);

#endif // STEPPER_DRIVER_H
