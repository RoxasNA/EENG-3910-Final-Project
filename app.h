#ifndef SRC_APP_H_
#define SRC_APP_H_

#include "stm32l4xx_hal.h"


void App_Init(void);
void App_MainLoop(void);
int* Get_New_Path(void);
void Run_Path(int* steps);


#endif /* SRC_APP_H_ */
