
#ifndef  TEST_H
#define  TEST_H


#include "global.h"


#define TASKSTACK           100     /* 堆栈大小, 单位: 4字节 */


/*********************************** 函数声明 *************************************/
extern void TEST_TestTask1(void);
extern void TEST_TestTask2(void);
extern U32* TEST_GetTaskInitSp(U8 ucTask);


#endif

