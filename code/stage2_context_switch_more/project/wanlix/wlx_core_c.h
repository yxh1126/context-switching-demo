
#ifndef  WLX_CORE_C_H
#define  WLX_CORE_C_H


#include "wanlix.h"

// Function implemented in assembly code
void WLX_SwitchToTask(STACKREG* pstrNextTaskStackRegAddr);

// Function implemented in assembly code
void WLX_ContextSwitch(STACKREG* pstrCurTaskStackRegAddr, 
	                   STACKREG* pstrNextTaskStackRegAddr);

#endif

