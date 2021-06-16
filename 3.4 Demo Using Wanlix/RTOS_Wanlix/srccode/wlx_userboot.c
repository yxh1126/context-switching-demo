
#include "wlx_userboot.h"


/***********************************************************************************
��������: ������, �û���������������ʼִ��.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void WLX_RootTask(void)
{
    /* ��ʼ����� */
    DEV_SoftwareInit();

    /* ��ʼ��Ӳ�� */
    DEV_HardwareInit();

    /* �������� */
    gpstrCrossStateTcb = WLX_TaskCreate((VFUNC)TEST_CrossStateTask,
                                        gaucCrossStateStack, TASKSTACK);
    gpstrLedDisplayTcb = WLX_TaskCreate((VFUNC)TEST_LedDisplayTask,
                                        gaucLedDisplayStack, TASKSTACK);

    WLX_TaskSwitch(gpstrCrossStateTcb);      /* �����л� */
}

