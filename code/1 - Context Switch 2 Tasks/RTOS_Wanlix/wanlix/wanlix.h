
#ifndef  WANLIX_H
#define  WANLIX_H


/* 定义变量类型 */
typedef unsigned char       U8;
typedef unsigned short      U16;
typedef unsigned int        U32;
typedef char                S8;
typedef short               S16;
typedef int                 S32;
typedef void                (*VFUNC)(void);


#ifndef NULL
 #define NULL               ((void*)0)
#endif


/* ARM工作模式掩码 */
#define MODE_USR            0x10
#define MODE_FIQ            0x11
#define MODE_IRQ            0x12
#define MODE_SVC            0x13
#define MODE_ABT            0x17
#define MODE_UND            0x1B
#define MODE_SYS            0x1F


/*********************************** 函数声明 *************************************/
extern void WLX_TaskInit(U8 ucTask, VFUNC vfFuncPointer, U32* puiTaskStack);
extern void WLX_TaskSwitch(void);
extern void WLX_TaskStart(void);


#endif

