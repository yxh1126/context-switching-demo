
#include "user_task.h"


W_TCB* gpstrTask1Tcb;           // TCB pointer of Task1
W_TCB* gpstrTask2Tcb;           // TCB pointer of Task2
W_TCB* gpstrTask3Tcb;           // TCB pointer of Task3

// The key idea is here, pay attention!!!
// Use the global array as the stack for each task using by the OS
// The global array space is located at global area

static U8 gaucTask1Stack[TASKSTACK];      // Task 1 stack
static U8 gaucTask2Stack[TASKSTACK];      // Task 2 stack
static U8 gaucTask3Stack[TASKSTACK];      // Task 3 stack


// The entry point of the test code
// Based on the hardware do the software and hardware initialization first
// Then initialize the TCB structure and start the task managed by OS
void WLX_RootTask(void)
{
    // Software and hardware init code goes here
    // As a sample here...

    // DEV_SoftwareInit();
    // DEV_HardwareInit();

    // Create user tasks here
    gpstrTask1Tcb = WLX_TaskCreate(TEST_TestTask1, gaucTask1Stack, TASKSTACK);
    gpstrTask2Tcb = WLX_TaskCreate(TEST_TestTask2, gaucTask2Stack, TASKSTACK);
    gpstrTask3Tcb = WLX_TaskCreate(TEST_TestTask3, gaucTask3Stack, TASKSTACK);

    // Switch the task from Root Task to user defined task
    WLX_TaskSwitch(gpstrTask1Tcb);
}

