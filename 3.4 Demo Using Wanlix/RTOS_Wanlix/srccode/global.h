
#ifndef  GLOBAL_H
#define  GLOBAL_H


#include <ADuC7024.h>
#include "wanlix.h"


#define TASKSTACK           400     /* ��ջ��С����λ: �ֽ� */


/* GPIO�˿ڶ��� */
#define GPIOPORT0           0
#define GPIOPORT1           1
#define GPIOPORT2           2
#define GPIOPORT3           3
#define GPIOPORT4           4

/* �����ӵ�GPIO�ܽŶ��� */
#define GPIO_MR             0x01
#define GPIO_MY             0x02
#define GPIO_MG             0x04
#define GPIO_SR             0x08
#define GPIO_SG             0x10


/* �жϺ궨�� */
#define TIME1INTMASK        0x00000008  /* Timer1�ж�ʹ��λ */
#define EXTIRQ0INTMASK      0x00008000  /* �ⲿIrq0�ж�ʹ��λ */


/* ʮ��·��״̬���� */
typedef enum crossstate
{
    CROSSSTATE1 = 0,                /* ʮ��·��״̬1 */
    CROSSSTATE2,                    /* ʮ��·��״̬2 */
    CROSSSTATE3,                    /* ʮ��·��״̬3 */
    CROSSSTATE4,                    /* ʮ��·��״̬4 */
    CROSSSTATENUM                   /* ʮ��·����Ŀ */
}CROSSSTATE;


/*********************************** �������� *************************************/
extern U8 gaucCrossStateStack[TASKSTACK];
extern U8 gaucLedDisplayStack[TASKSTACK];

extern W_TCB* gpstrCrossStateTcb;
extern W_TCB* gpstrLedDisplayTcb;

extern U32 guiSystemTick;
extern U32 guiCurSta;
extern U32 guiStaChange;


/*********************************** �������� *************************************/
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

