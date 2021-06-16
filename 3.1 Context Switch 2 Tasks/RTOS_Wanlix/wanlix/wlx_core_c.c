
#include "wlx_core_c.h"


U32 guiCurTask;                 /* ��ǰ���е����� */
U32 guiNextTaskSp;              /* ��Ҫ���е������ջָ�� */
U32* gpuiCurTaskSpAddr;         /* ��ŵ�ǰ���������ջָ��ĵ�ַ */

U32 guiTask1CurSp;              /* ����1��ǰ�Ķ�ջָ�� */
U32 guiTask2CurSp;              /* ����2��ǰ�Ķ�ջָ�� */


/***********************************************************************************
��������: ������������ǰ��״̬.
��ڲ���: ucTask: ���е�����, 1����2.
          vfFuncPointer: �������еĺ���ָ��.
          puiTaskStack: ����ʹ�õĶ�ջ��ַ.
�� �� ֵ: none.
***********************************************************************************/
void WLX_TaskInit(U8 ucTask, VFUNC vfFuncPointer, U32* puiTaskStack)
{
    U32* puiSp;

    /* �Զ�ջ��ʼ�� */
    puiSp = puiTaskStack;               /* ��ȡ��ջָ�� */

    *(--puiSp) = (U32)vfFuncPointer;    /* R14 */
    *(--puiSp) = (U32)puiTaskStack;     /* R13 */
    *(--puiSp) = 0;                     /* R12 */
    *(--puiSp) = 0;                     /* R11 */
    *(--puiSp) = 0;                     /* R10 */
    *(--puiSp) = 0;                     /* R9 */
    *(--puiSp) = 0;                     /* R8 */
    *(--puiSp) = 0;                     /* R7 */
    *(--puiSp) = 0;                     /* R6 */
    *(--puiSp) = 0;                     /* R5 */
    *(--puiSp) = 0;                     /* R4 */
    *(--puiSp) = 0;                     /* R3 */
    *(--puiSp) = 0;                     /* R2 */
    *(--puiSp) = 0;                     /* R1 */
    *(--puiSp) = 0;                     /* R0 */
    *(--puiSp) = MODE_USR;              /* CPSR */

    /* ��¼��ǰ����Ķ�ջָ��, �´������������ʱ�ɸ��ݸ�ֵ�ָ���ջ */
    if(1 == ucTask)
    {
        guiTask1CurSp = (U32)puiSp;
    }
    else //if(2 == ucTask)
    {
        guiTask2CurSp = (U32)puiSp;
    }
}

/***********************************************************************************
��������: ���øú��������������л�.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void WLX_TaskSwitch(void)
{
    if(1 == guiCurTask)
    {
        /* ���뵱ǰ�����ջָ��ĵ�ַ */
        gpuiCurTaskSpAddr = &guiTask1CurSp;

        /* ��ȡ������������Ķ�ջָ�� */
        guiNextTaskSp = guiTask2CurSp;

        /* �����´ε��ȵ����� */
        guiCurTask = 2;
    }
    else //if(2 == guiCurTask)
    {
        gpuiCurTaskSpAddr = &guiTask2CurSp;

        guiNextTaskSp = guiTask1CurSp;

        guiCurTask = 1;
    }

    /* �л����� */
    WLX_ContextSwitch();
}

/***********************************************************************************
��������: ��ʼ�����������.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void WLX_TaskStart(void)
{
    /* ��������ǰ����Ҫ���������ջָ�� */
    gpuiCurTaskSpAddr = (U32*)NULL;

    /* ��ȡ������������Ķ�ջָ�� */
    guiNextTaskSp = guiTask1CurSp;

    /* �����´ε��ȵ����� */
    guiCurTask = 1;

    WLX_ContextSwitch();
}

