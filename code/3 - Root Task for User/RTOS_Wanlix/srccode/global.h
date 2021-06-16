
#ifndef  GLOBAL_H
#define  GLOBAL_H


#include <ADuC7024.h>
#include "wanlix.h"


#define TASKSTACK           400     /* 堆栈大小，单位: 字节 */


/*********************************** 变量声明 *************************************/
extern U8 gaucTask1Stack[TASKSTACK];
extern U8 gaucTask2Stack[TASKSTACK];
extern U8 gaucTask3Stack[TASKSTACK];

extern W_TCB* gpstrTask1Tcb;
extern W_TCB* gpstrTask2Tcb;
extern W_TCB* gpstrTask3Tcb;


/*********************************** 函数声明 *************************************/
extern void DEV_HardwareInit(void);
extern void DEV_DelayMs(U32 uiMs);
extern void DEV_PutString(U8* pucChar);

extern void TEST_TestTask1(void);
extern void TEST_TestTask2(void);
extern void TEST_TestTask3(void);


#endif

