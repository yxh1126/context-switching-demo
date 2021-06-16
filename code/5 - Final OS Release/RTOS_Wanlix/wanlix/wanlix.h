
#ifndef  WANLIX_H
#define  WANLIX_H


/* Wanlix�汾�� */
#define WANLIX_VER          "001.001.001.000"



/* ����������� */
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


/* ARM����ģʽ���� */
#define MODE_USR            0x10
#define MODE_FIQ            0x11
#define MODE_IRQ            0x12
#define MODE_SVC            0x13
#define MODE_ABT            0x17
#define MODE_UND            0x1B
#define MODE_SYS            0x1F


#define ROOTTASKSTACK       400     /* �������ջ��С, ��λ: �ֽ� */


typedef struct w_tcb
{
    U32 uiTaskCurSp;                /* ����ǰ��ջָ�� */
}W_TCB;


/*********************************** �������� *************************************/
extern W_TCB* WLX_TaskCreate(VFUNC vfFuncPointer, U8* pucTaskStack,
                             U32 uiStackSize);
extern void WLX_TaskSwitch(W_TCB* pstrTcb);


#endif

