
#include "user_task.h"


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
        WLX_TaskSwitch(gpstrTask3Tcb);
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
        WLX_TaskSwitch(gpstrTask1Tcb);
    }
}


// The sample function for task3
void TEST_TestTask3(void)
{
    while(1)
    {
        // Put your task code here
        // DEV_TaskPrintMsg("Task 3");

        // Task last for 3s
        // TEST_TaskRun(3000);

        // Call wlx function here to switch from this task to next
        WLX_TaskSwitch(gpstrTask2Tcb);
    }
}

