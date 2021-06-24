
#include "user_task.h"


// The sample function for task1
// Currently the task funciton donot support input argment
void TEST_TestTask1(void* pvPara)
{
    U32 uiRunTime = *((U32*)pvPara);

    while(1)
    {
        // Put your task code here
        // DEV_TaskPrintMsg("Task 1");

        // Task last for uiRunTime
        // TEST_TaskRun(uiRunTime);

        // Call wlx function here to switch from this task to next
        WLX_TaskSwitch(gpstrTask3Tcb);
    }
}


// The sample function for task2
void TEST_TestTask2(void* pvPara)
{
    U32 uiRunTime = *((U32*)pvPara);

    while(1)
    {
        // Put your task code here
        // DEV_TaskPrintMsg("Task 2");

        // Task last for uiRunTime
        // TEST_TaskRun(uiRunTime);

        // Call wlx function here to switch from this task to next
        WLX_TaskSwitch(gpstrTask1Tcb);
    }
}


// The sample function for task3
void TEST_TestTask3(void* pvPara)
{
    U32 uiRunTime = *((U32*)pvPara);
    
    while(1)
    {
        // Put your task code here
        // DEV_TaskPrintMsg("Task 3");

        // Task last for uiRunTime
        // TEST_TaskRun(uiRunTime);

        // Call wlx function here to switch from this task to next
        WLX_TaskSwitch(gpstrTask2Tcb);
    }
}

