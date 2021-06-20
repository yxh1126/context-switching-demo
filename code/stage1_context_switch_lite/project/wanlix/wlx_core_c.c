
#include "wlx_core_c.h"


static U32 guiCurTaskID;        // Current task ID

W_TCB* gpstrTask1Tcb;           // TCB pointer of Task1
W_TCB* gpstrTask2Tcb;           // TCB pointer of Task2


// Calc the pointer of TCB based the Task Stack pointer
// Task stack pointer point to the global variable space
// Initialize the Stack Register Structure 
W_TCB* WLX_TaskInit(VFUNC vfFuncPointer, U32* puiTaskStack)
{
    W_TCB* pstrTcb;
    STACKREG* pstrStackReg;

    // puiTaskStack store the pointer points to the top of the stack
    // reserve the space at the top of stack for W_TCB
    pstrTcb = (W_TCB*)((U32)puiTaskStack - sizeof(W_TCB));

    // Get the register structure address
    pstrStackReg = &(pstrTcb->strStackReg);

    // Initialize the TCB structure
    pstrStackReg->uiR4 = 0;
    pstrStackReg->uiR5 = 0;
    pstrStackReg->uiR6 = 0;
    pstrStackReg->uiR7 = 0;
    pstrStackReg->uiR8 = 0;
    pstrStackReg->uiR9 = 0;
    pstrStackReg->uiR10 = 0;
    pstrStackReg->uiR11 = 0;
    pstrStackReg->uiR12 = 0;
    pstrStackReg->uiR13 = (U32)pstrTcb;
    pstrStackReg->uiR14 = (U32)vfFuncPointer;
    pstrStackReg->uiXpsr = MODE_USR;

    // Return the TCB pointer
    // Note: The reason can return a pointer here is due to: puiTaskStack is
    // is pointer points to the global variable space, and pstrTcb is derived
    // from this pointer
    return pstrTcb;
}


// Run the assembly code at function WLX_SwitchToTask
// This function switch the code from system mode to OS mode.
void WLX_TaskStart(void)
{
    STACKREG* pstrNextTaskStackRegAddr;

    // Next running task stack register address
    pstrNextTaskStackRegAddr = &(gpstrTask1Tcb->strStackReg);

    // Task ID of the next task
    guiCurTaskID = 1;

    WLX_SwitchToTask(pstrNextTaskStackRegAddr);
}


// Call this function to save the state of current task
// and restore the previous task to let it run.
void WLX_TaskSwitch(void)
{
    STACKREG* pstrCurTaskStackRegAddr;
    STACKREG* pstrNextTaskStackRegAddr;

    if(1 == guiCurTaskID)
    {
        // Current task stack register address
        pstrCurTaskStackRegAddr = &(gpstrTask1Tcb->strStackReg);

        // Next task stack register address
        pstrNextTaskStackRegAddr = &(gpstrTask2Tcb->strStackReg);

        // Task ID of next task
        guiCurTaskID = 2;
    }
    else //if(2 == guiCurTaskID)
    {
        pstrCurTaskStackRegAddr = &(gpstrTask2Tcb->strStackReg);
        pstrNextTaskStackRegAddr = &(gpstrTask1Tcb->strStackReg);
        guiCurTaskID = 1;
    }

    /* Context switch the 2 tasks */
    WLX_ContextSwitch(pstrCurTaskStackRegAddr, pstrNextTaskStackRegAddr);
}

