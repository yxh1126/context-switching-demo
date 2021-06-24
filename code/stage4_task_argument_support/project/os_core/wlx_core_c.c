
#include "wlx_core_c.h"


// Static variable declaration for current task TCB pointer
static W_TCB* gpstrCurTcb; 

// Static function prototype
static W_TCB* WLX_TaskTcbInit(VFUNC vfFuncPointer, void* pvPara, U8* pucTaskStack, U32 uiStackSize);
static void WLX_TaskStackInit(W_TCB* pstrTcb, VFUNC vfFuncPointer, void* pvPara);


// OS create task function for user
W_TCB* WLX_TaskCreate(VFUNC vfFuncPointer, void* pvPara, U8* pucTaskStack, U32 uiStackSize)
{
    W_TCB* pstrTcb;

    // Check the validity of the function pointer used for create task
    if(NULL == vfFuncPointer)
    {
        return (W_TCB*)NULL;
    }

    // Check the validity of the stack created by OS
    if((NULL == pucTaskStack) || (0 == uiStackSize))
    {
        return (W_TCB*)NULL;
    }

    // Initialize TCB
    pstrTcb = WLX_TaskTcbInit(vfFuncPointer, pvPara, pucTaskStack, uiStackSize);

    return pstrTcb;
}


// Initialize the TCB for a task
// Calc the pointer of the TCB based on the Task Stack pointer
// Task stack pointer points to the global variable space
static W_TCB* WLX_TaskTcbInit(VFUNC vfFuncPointer, void* pvPara, U8* pucTaskStack, U32 uiStackSize)
{
    W_TCB* pstrTcb;
    U32 pucStackBy4;

    // The stack grows from high address to small address
    // Put the TCB at the bottom of the stack, and makes it 4 bytes aligned.
    // The unit of uiStackSize is byte, so uiStackSize = sizeof(U32) * TASKSTACK
    pucStackBy4 = ((U32)pucTaskStack + uiStackSize) & ALIGN4MASK;

    // TCB address is the place the stack starts, Cortex kernal uses 8 bytes align
    // puiTaskStack store the pointer points to the top of the stack
    // reserve the space at the top of stack for W_TCB
    pstrTcb = (W_TCB*)((pucStackBy4 - sizeof(W_TCB)) & ALIGN8MASK);

    // initialize the task stack
    WLX_TaskStackInit(pstrTcb, vfFuncPointer, pvPara);

    // Return the TCB pointer
    // Note: The reason can return a pointer here is due to: puiTaskStack is
    // is pointer points to the global variable space, and pstrTcb is derived
    // from this pointer
    return pstrTcb;
}


// Initialize the task Stack Register structure
static void WLX_TaskStackInit(W_TCB* pstrTcb, VFUNC vfFuncPointer, void* pvPara)
{
    STACKREG* pstrStackReg;

    // Get the register structure address
    pstrStackReg = &(pstrTcb->strStackReg);

    // Initialize the TCB structure
    pstrStackReg->uiXpsr = MODE_USR;
    pstrStackReg->uiR0 = (U32)pvPara;
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
}


// Run the assembly code at function WLX_SwitchToTask
// This function switch the code from system mode to OS mode.
void WLX_TaskStart(W_TCB* pstrTcb)
{
    STACKREG* pstrNextTaskStackRegAddr;

    // Next running task stack register address
    pstrNextTaskStackRegAddr = &(pstrTcb->strStackReg);

    // Save the TCB pointer of the next task
    gpstrCurTcb = pstrTcb;

    WLX_SwitchToTask(pstrNextTaskStackRegAddr);
}


// Call this function to save the state of current task
// and restore the previous task to let it run.
void WLX_TaskSwitch(W_TCB* pstrTcb)
{
    STACKREG* pstrCurTaskStackRegAddr;
    STACKREG* pstrNextTaskStackRegAddr;

    // Current task stack register address
    pstrCurTaskStackRegAddr = &(gpstrCurTcb->strStackReg);

    // Next task stack register address
    pstrNextTaskStackRegAddr = &(pstrTcb->strStackReg);

    // Update the current task pointer to the next task
    gpstrCurTcb = pstrTcb;

    /* Context switch the 2 tasks */
    WLX_ContextSwitch(pstrCurTaskStackRegAddr, pstrNextTaskStackRegAddr);
}

