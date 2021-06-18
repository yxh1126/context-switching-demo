
#ifndef  WLX_CORE_C_H
#define  WLX_CORE_C_H


#include "wanlix.h"


/*********************************** º¯ÊýÉùÃ÷ *************************************/
extern void WLX_TaskStackInit(W_TCB* pstrTcb, VFUNC vfFuncPointer);
extern W_TCB* WLX_TaskTcbInit(U8* pucTaskStack, U32 uiStackSize);
extern void WLX_ContextSwitch(void);
extern void WLX_SwitchToTask(void);

extern void WLX_TaskStart(W_TCB* pstrTcb);
extern void WLX_RootTask(void);


#endif

