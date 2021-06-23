
#ifndef  USER_TASK_H
#define  USER_TASK_H


#include "wanlix.h"

// Define stack size, the unit is 1 byte
#define TASKSTACK           400

// Global variable to extern
extern W_TCB* gpstrTask1Tcb;           // TCB pointer of Task1
extern W_TCB* gpstrTask2Tcb;           // TCB pointer of Task2
extern W_TCB* gpstrTask3Tcb;           // TCB pointer of Task3


// Function prototype define here
void TEST_TestTask1(void);
void TEST_TestTask2(void);
void TEST_TestTask3(void);


#endif

