
#ifndef  GLOBAL_H
#define  GLOBAL_H


#include <ADuC7024.h>
#include "wanlix.h"


#define TASKSTACK           400     /* ��ջ��С����λ: �ֽ� */


/*********************************** �������� *************************************/
extern U8 gaucTask1Stack[TASKSTACK];
extern U8 gaucTask2Stack[TASKSTACK];
extern U8 gaucTask3Stack[TASKSTACK];

extern W_TCB* gpstrTask1Tcb;
extern W_TCB* gpstrTask2Tcb;
extern W_TCB* gpstrTask3Tcb;


/*********************************** �������� *************************************/
extern void DEV_HardwareInit(void);
extern void DEV_DelayMs(U32 uiMs);
extern void DEV_PutString(U8* pucChar);

extern void TEST_TestTask1(void);
extern void TEST_TestTask2(void);
extern void TEST_TestTask3(void);


#endif

