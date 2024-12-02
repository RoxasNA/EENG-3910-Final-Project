#include "stepper_driver.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"

static const IN_GPIO_PORT[] = {GPIOA, GPIOB};       // Adjust this to the correct GPIO port
static const IN1_PIN[] = {GPIO_PIN_6, GPIO_PIN_1};  // Replace X with the actual pin number
static const IN2_PIN[] = {GPIO_PIN_7, GPIO_PIN_15};  // Replace Y with the actual pin number
static const IN3_PIN[] = {GPIO_PIN_8, GPIO_PIN_14}; // Replace Z with the actual pin number
static const IN4_PIN[] = {GPIO_PIN_9, GPIO_PIN_13};  // Replace W with the actual pin number

static const int stepSequence[8][4] = {
		{0,0,0,1},
		{0,0,1,1},
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0},
		{1,1,0,0},
		{1,0,0,0},
		{1,0,0,1}
		/*
    0b0001,  // Phase 0: IN1 = LOW, IN2 = LOW, IN3 = LOW, IN4 = HIGH
    0b0011,  // Phase 1: IN1 = LOW, IN2 = LOW, IN3 = HIGH, IN4 = HIGH
    0b0010,  // Phase 2: IN1 = LOW, IN2 = LOW, IN3 = HIGH, IN4 = LOW
    0b0110,  // Phase 3: IN1 = LOW, IN2 = HIGH, IN3 = HIGH, IN4 = LOW
    0b0100,  // Phase 4: IN1 = LOW, IN2 = HIGH, IN3 = LOW, IN4 = LOW
    0b1100,  // Phase 5: IN1 = HIGH, IN2 = HIGH, IN3 = LOW, IN4 = LOW
    0b1000,  // Phase 6: IN1 = HIGH, IN2 = LOW, IN3 = LOW, IN4 = LOW
    0b1001   // Phase 7: IN1 = HIGH, IN2 = LOW, IN3 = LOW, IN4 = HIGH
	*/
};

void Stepper_Driver_Init(void) {
}


void Stepper_Write_Phase(int phase, int phaseValue) {
// Set each phase pin according to the 4-bit phase value
	HAL_GPIO_WritePin(IN_GPIO_PORT[phase], IN1_PIN[phase], (stepSequence[phaseValue][1]) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN_GPIO_PORT[phase], IN2_PIN[phase], (stepSequence[phaseValue][2]) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN_GPIO_PORT[phase], IN3_PIN[phase], (stepSequence[phaseValue][3]) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN_GPIO_PORT[phase], IN4_PIN[phase], (stepSequence[phaseValue][4]) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Stepper_Write_Off(phase){
	HAL_GPIO_WritePin(IN_GPIO_PORT[phase], IN4_PIN[phase], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN_GPIO_PORT[phase], IN3_PIN[phase], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN_GPIO_PORT[phase], IN2_PIN[phase], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN_GPIO_PORT[phase], IN1_PIN[phase], GPIO_PIN_RESET);
}

void Step_Forward(int phase){
	for (int i = 0; i < 7; i++) {
		Stepper_Write_Phase(phase, i);
		HAL_Delay(1);
	}

	Stepper_Write_Off(phase);
}

void Step_Backward(int phase){
	for (int i = 7; i > 0; i--) {
		Stepper_Write_Phase(phase, i);
		HAL_Delay(1);
	}
	Stepper_Write_Off(phase);
}
