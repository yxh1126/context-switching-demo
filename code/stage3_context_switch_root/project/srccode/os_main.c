
#include "os_task.h"


// The entry point of the test code
// Based on the hardware do the software and hardware initialization first
// Then initialize the TCB structure and start the task managed by OS
S32 main(void)
{
    // Software and hardware init code goes here
    // As a sample here...

    // DEV_SoftwareInit();
    // DEV_HardwareInit();

    // Create task here
    gpstrTask1Tcb = WLX_TaskInit(TEST_TestTask1, TEST_GetTaskInitSp(1));
    gpstrTask2Tcb = WLX_TaskInit(TEST_TestTask2, TEST_GetTaskInitSp(2));

    // Enter the OS state from here
    // Start to run the first task at the OS managed stack
    WLX_TaskStart();

    return 0;
}

