/* Includes ------------------------------------------------------------------*/
#include "app.h"
#include "stepper_driver.h"
#include "coordinate_algorithm.h"
/* Private define ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

int new_path[2] = {0,0};

void App_Init(void)
{
	Stepper_Driver_Init();
	Corrdinate_Algorithm_Init();
}

void App_MainLoop(void)
{

	for (int i = 0; i < 15; i++){
		int steps[2];
		int* generated_path = Get_New_Path();
		steps[0] = generated_path[0];
		steps[1] = generated_path[1];
		Run_Path(steps);
		HAL_Delay(5000);
	}
	//Delay_Mins(30);
}

void Delay_Mins(int num_mins){
	for (int i = 0; i < (60 * num_mins); i++){
		HAL_Delay(1000);
	}
}

int* Get_New_Path(void){

	/*int new_point[2];
	int* generated_point = Generate_Random_Point();
	new_point[0] = generated_point[0];
	new_point[1] = generated_point[0];
*/

	int* generated_path = Calculate_Path();
	new_path[0] = generated_path[0];
	new_path[1] = generated_path[1];

	return(new_path);
}

void Run_Path(int* steps){

	int steps_x = steps[0];
	int steps_y = steps[1];

	while ((steps_x != 0) || (steps_y != 0)){

		if (steps_x > 0){
			Step_Forward(0);
			steps_x--;
		}
		else if (steps_x < 0){
			Step_Backward(0);
			steps_x++;
		}

		if (steps_y > 0){
			Step_Forward(1);
			steps_y--;
		}
		else if (steps_y < 0){
			Step_Backward(1);
			steps_y++;
		}

	}
}
