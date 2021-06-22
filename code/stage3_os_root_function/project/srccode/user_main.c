
#include "wlx_userroot.h"
#include "wanlix.h"


static W_TCB* gpstrRootTaskTcb;           // TCB pointer of Root Task

// The key idea is here, pay attention!!!
// Use the global array as the stack for each task using by the OS
// The global array space is located at global area
static U8 gaucRootTaskStack[ROOTTASKSTACK];      // Root Task stack


// The entry point of the test code
// Based on the hardware do the software and hardware initialization first
// Then initialize the TCB structure and start the task managed by OS
S32 main(void)
{
    // Create root task here
    gpstrRootTaskTcb = WLX_TaskCreate(WLX_RootTask, gaucRootTaskStack, ROOTTASKSTACK);

    // Enter the OS state from here
    // Start to run the root task at the OS managed stack
    WLX_TaskStart(gpstrRootTaskTcb);

    return 0;
}

