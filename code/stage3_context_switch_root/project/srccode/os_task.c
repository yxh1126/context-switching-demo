
#include "os_task.h"


// The key idea is here, pay attention!!!
// Use the global array as the stack for each task using by the OS
// The global array space is located at global area

U32 gauiTask1Stack[TASKSTACK];      // Task 1 stack
U32 gauiTask2Stack[TASKSTACK];      // Task 2 stack


// The sample function for task1
// Currently the task funciton donot support input argment
void TEST_TestTask1(void)
{
    while(1)
    {
        // Put your task code here
        // DEV_TaskPrintMsg("Task 1");

        // Task last for 1s
        // TEST_TaskRun(1000);

        // Call wlx function here to switch from this task to next
        WLX_TaskSwitch();
    }
}


// The sample function for task2
void TEST_TestTask2(void)
{
    while(1)
    {
        // Put your task code here
        // DEV_TaskPrintMsg("Task 2");

        // Task last for 2s
        // TEST_TaskRun(2000);

        // Call wlx function here to switch from this task to next
        WLX_TaskSwitch();
    }
}


// Get the task initiate Stack Pointer address
U32* TEST_GetTaskInitSp(U8 ucTask)
{
    if(1 == ucTask)
    {
        return (gauiTask1Stack + TASKSTACK);
    }
    else //if(2 == ucTask)
    {
        return (gauiTask2Stack + TASKSTACK);
    }
}

