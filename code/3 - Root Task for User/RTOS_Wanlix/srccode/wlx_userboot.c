
#include "wlx_userboot.h"


/***********************************************************************************
��������: ������, �û���������������ʼִ��.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void WLX_RootTask(void)
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

    WLX_TaskSwitch(gpstrTask1Tcb);      /* �����л� */
}

