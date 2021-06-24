
#ifndef  WANLIX_H
#define  WANLIX_H


// Basic data type define
typedef unsigned char       U8;
typedef unsigned short      U16;
typedef unsigned int        U32;
typedef char                S8;
typedef short               S16;
typedef int                 S32;
typedef void                (*VFUNC)(void*);


// NULL pointer
#ifndef NULL
 #define NULL               ((void*)0)
#endif


// Task stack structure
typedef struct stackreg
{
    U32 uiR0;
    U32 uiR4;
    U32 uiR5;
    U32 uiR6;
    U32 uiR7;
    U32 uiR8;
    U32 uiR9;
    U32 uiR10;
    U32 uiR11;
    U32 uiR12;
    U32 uiR13;
    U32 uiR14;
    U32 uiXpsr;
} STACKREG;


// Task TCB structure
typedef struct w_tcb
{
    STACKREG strStackReg;
} W_TCB;


// ARM mode related code
#define MODE_USR            0x10
#define MODE_FIQ            0x11
#define MODE_IRQ            0x12
#define MODE_SVC            0x13
#define MODE_ABT            0x17
#define MODE_UND            0x1B
#define MODE_SYS            0x1F


// Function prototype
W_TCB* WLX_TaskCreate(VFUNC vfFuncPointer, void* pvPara, U8* pucTaskStack, U32 uiStackSize);
void WLX_TaskStart(W_TCB* pstrTcb);
void WLX_TaskSwitch(W_TCB* pstrTcb);


#endif

