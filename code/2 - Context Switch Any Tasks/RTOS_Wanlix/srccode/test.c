
#include "test.h"

U8 gaucTask1Stack[TASKSTACK];       /* ����1�Ķ�ջ */
U8 gaucTask2Stack[TASKSTACK];       /* ����2�Ķ�ջ */
U8 gaucTask3Stack[TASKSTACK];       /* ����3�Ķ�ջ */

W_TCB* gpstrTask1Tcb;               /* ����1��TCBָ�� */
W_TCB* gpstrTask2Tcb;               /* ����2��TCBָ�� */
W_TCB* gpstrTask3Tcb;               /* ����3��TCBָ�� */



/***********************************************************************************
��������: ������, C����Ӵ˺�����ʼ����. �ú�������ϵͳ���񲢴ӷ�����״̬�л���Root
          ��������.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
S32 main(void)
{
    /* ��ʼ��Ӳ�� */
    DEV_HardwareInit();

    /* �������� */
    gpstrTask1Tcb = WLX_TaskCreate((VFUNC)TEST_TestTask1, gaucTask1Stack,
                                   TASKSTACK);
    gpstrTask2Tcb = WLX_TaskCreate((VFUNC)TEST_TestTask2, gaucTask2Stack,
                                   TASKSTACK);
    gpstrTask3Tcb = WLX_TaskCreate((VFUNC)TEST_TestTask3, gaucTask3Stack,
                                   TASKSTACK);

    /* ��ʼ�������, ������1��ʼִ�� */
    WLX_TaskStart(gpstrTask1Tcb);

    return 0;
}

/***********************************************************************************
��������: ���������л�����1, �򴮿ڴ�ӡ�ַ���.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void TEST_TestTask1(void)
{
    while(1)
    {
        DEV_PutString((U8*)"\r\nTask1 is running!");

        DEV_DelayMs(1000);              /* �ӳ�1s */

        WLX_TaskSwitch(gpstrTask3Tcb);  /* �����л� */
    }
}

/***********************************************************************************
��������: ���������л�����2, �򴮿ڴ�ӡ�ַ���.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void TEST_TestTask2(void)
{
    while(1)
    {
        DEV_PutString((U8*)"\r\nTask2 is running!");

        DEV_DelayMs(2000);              /* �ӳ�2s */

        WLX_TaskSwitch(gpstrTask1Tcb);  /* �����л� */
    }
}

/***********************************************************************************
��������: ���������л�����3, �򴮿ڴ�ӡ�ַ���.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void TEST_TestTask3(void)
{
    while(1)
    {
        DEV_PutString((U8*)"\r\nTask3 is running!");

        DEV_DelayMs(3000);              /* �ӳ�3s */

        WLX_TaskSwitch(gpstrTask2Tcb);  /* �����л� */
    }
}

