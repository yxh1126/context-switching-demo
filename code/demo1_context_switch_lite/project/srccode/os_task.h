
#ifndef  OS_TASK_H
#define  OS_TASK_H


#include "wanlix.h"

// Define stack size, the unit is 4 bytes
#define TASKSTACK           100


// Function prototype define here
void TEST_TestTask1(void);
void TEST_TestTask2(void);

U32* TEST_GetTaskInitSp(U8 ucTask);


#endif

