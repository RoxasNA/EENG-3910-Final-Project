#include "coordinate_algorithm.h"
#include "time.h"
#include "stdlib.h"

static int current_x = 0;
static int current_y = 0;

static int maximum_x = 250;
static int minimum_x = 0;

static int maximum_y = 250;
static int minimum_y = 0;

static int new_point[2];
static int path_steps[2];

void Corrdinate_Algorithm_Init(void){
	srand(time(0));
}

int* Calculate_Path(void){

	new_point[0] = minimum_x + rand() % (maximum_x - minimum_x + 1);
	new_point[1] = minimum_y + rand() % (maximum_y - minimum_y + 1);

	int new_x = new_point[0];
	int new_y = new_point[1];

	path_steps[0] = new_point[0] - current_x;
	path_steps[1] = new_point[1] - current_y;

	current_x = new_x;
	current_y = new_y;

	return(path_steps);
}

