
#ifndef  GLOBAL_H
#define  GLOBAL_H


#include <ADuC7024.h>
#include "wanlix.h"


#define TASKSTACK           400     /* 堆栈大小，单位: 字节 */


/* GPIO端口定义 */
#define GPIOPORT0           0
#define GPIOPORT1           1
#define GPIOPORT2           2
#define GPIOPORT3           3
#define GPIOPORT4           4

/* 灯连接的GPIO管脚定义 */
#define GPIO_MR             0x01
#define GPIO_MY             0x02
#define GPIO_MG             0x04
#define GPIO_SR             0x08
#define GPIO_SG             0x10


/* 中断宏定义 */
#define TIME1INTMASK        0x00000008  /* Timer1中断使能位 */
#define EXTIRQ0INTMASK      0x00008000  /* 外部Irq0中断使能位 */


/* 十字路口状态定义 */
typedef enum crossstate
{
    CROSSSTATE1 = 0,                /* 十字路口状态1 */
    CROSSSTATE2,                    /* 十字路口状态2 */
    CROSSSTATE3,                    /* 十字路口状态3 */
    CROSSSTATE4,                    /* 十字路口状态4 */
    CROSSSTATENUM                   /* 十字路口数目 */
}CROSSSTATE;


/*********************************** 变量声明 *************************************/
extern U8 gaucCrossStateStack[TASKSTACK];
extern U8 gaucLedDisplayStack[TASKSTACK];

extern W_TCB* gpstrCrossStateTcb;
extern W_TCB* gpstrLedDisplayTcb;

extern U32 guiSystemTick;
extern U32 guiCurSta;
extern U32 guiStaChange;


/*********************************** 函数声明 *************************************/
extern void DEV_SoftwareInit(void);
extern void DEV_HardwareInit(void);
extern void DEV_SetGpio(U8 ucPort, U8 ucPin);
extern void DEV_ClrGpio(U8 ucPort, U8 ucPin);

extern void TEST_LedSet(U32 uiLedNo, U32 uiLedSta);
extern void TEST_CrossVarInit(void);
extern void TEST_CrossStateTask(void);
extern void TEST_LedDisplayTask(void);

extern void ISR_IrqIsr(void);
extern void ISR_PassengerIntLock(void);
extern void ISR_PassengerIntUnlock(void);


#endif

