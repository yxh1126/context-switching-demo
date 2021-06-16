
#include "wlx_core_c.h"


W_TCB* gpstrCurTcb;             /* ��ǰ���е������TCB */
U32 guiNextTaskSp;              /* ��Ҫ���е������ջָ�� */
U32* gpuiCurTaskSpAddr;         /* ��ŵ�ǰ���������ջָ��ĵ�ַ */
W_TCB* gpstrRootTaskTcb;        /* �������TCBָ�� */

U8 gaucRootTaskStack[ROOTTASKSTACK];    /* ������Ķ�ջ */


/***********************************************************************************
��������: ������, C����Ӵ˺�����ʼ����. �ú�������ϵͳ���񲢴ӷ�����״̬�л���Root
          ��������.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
S32 main(void)
{
    /* ���������� */
    gpstrRootTaskTcb = WLX_TaskCreate((VFUNC)WLX_RootTask, gaucRootTaskStack,
                                      ROOTTASKSTACK);

    /* ��ʼ�������, �Ӹ�����ʼִ�� */
    WLX_TaskStart(gpstrRootTaskTcb);

    return 0;
}

/***********************************************************************************
��������: ����һ������.
��ڲ���: vfFuncPointer: ����������ʹ�ú�����ָ��.
          pucTaskStack: ������ʹ�ö�ջ�������ʼ��ַ.
          uiStackSize: ��ջ��С, ��λ: �ֽ�.
�� �� ֵ: NULL: ��������ʧ��.
          ����: �����TCBָ��.
***********************************************************************************/
W_TCB* WLX_TaskCreate(VFUNC vfFuncPointer, U8* pucTaskStack, U32 uiStackSize)
{
    W_TCB* pstrTcb;

    /* �Դ���������ʹ�ú�����ָ��Ϸ��Խ��м�� */
    if(NULL == vfFuncPointer)
    {
        /* ָ��Ϊ��, ����ʧ�� */
        return (W_TCB*)NULL;
    }

    /* �������ջ�Ϸ��Խ��м�� */
    if((NULL == pucTaskStack) || (0 == uiStackSize))
    {
        /* ��ջ���Ϸ�, ����ʧ�� */
        return (W_TCB*)NULL;
    }

    /* ��ʼ��TCB */
    pstrTcb = WLX_TaskTcbInit(pucTaskStack, uiStackSize);

    /* ��ʼ�������ջ */
    WLX_TaskStackInit(pstrTcb, vfFuncPointer);

    return pstrTcb;
}

/***********************************************************************************
��������: ��ʼ������TCB, ����������������ǰTCB��״̬.
��ڲ���: pucTaskStack: ������ʹ�õĶ�ջ��ַ.
          uiStackSize: ��ջ��С, ��λ: �ֽ�.
�� �� ֵ: ����TCB��ָ��.
***********************************************************************************/
W_TCB* WLX_TaskTcbInit(U8* pucTaskStack, U32 uiStackSize)
{
    W_TCB* pstrTcb;
    U8* pucStackBy4;

    /* ��ջ����ַ, ��Ҫ4�ֽڶ��� */
    pucStackBy4 = (U8*)(((U32)pucTaskStack + uiStackSize) & 0xFFFFFFFC);

    /* TCB�ṹ��ŵĵ�ַ, ��Ҫ4�ֽڶ��� */
    pstrTcb = (W_TCB*)(((U32)pucStackBy4 - sizeof(W_TCB)) & 0xFFFFFFFC);

    /* ��ʼ��TCB�ṹ */
    pstrTcb->uiTaskCurSp = (U32)pstrTcb;

    return pstrTcb;
}

/***********************************************************************************
��������: ��ʼ�������ջ����, ����������������ǰ�Ķ�ջ״̬.
��ڲ���: pstrTcb: �����TCBָ��.
          vfFuncPointer: �������еĺ���.
�� �� ֵ: none.
***********************************************************************************/
void WLX_TaskStackInit(W_TCB* pstrTcb, VFUNC vfFuncPointer)
{
    U32* puiSp;

    /* �Զ�ջ��ʼ�� */
    puiSp = (U32*)pstrTcb->uiTaskCurSp; /* ��ȡ��ű����Ķ�ջָ�� */

    *(--puiSp) = (U32)vfFuncPointer;    /* R14 */
    *(--puiSp) = pstrTcb->uiTaskCurSp;  /* R13 */
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
    pstrTcb->uiTaskCurSp = (U32)puiSp;
}

/***********************************************************************************
��������: ���øú��������������л�.
��ڲ���: pstrTcb: �������е������TCBָ��.
�� �� ֵ: none.
***********************************************************************************/
void WLX_TaskSwitch(W_TCB* pstrTcb)
{
    /* ���浱ǰ�����ջָ��ĵ�ַ, �ڻ�����Կ���ͨ���������д�������л�ǰ���ʱ��
       �Ķ�ջ��ַ */
    gpuiCurTaskSpAddr = &gpstrCurTcb->uiTaskCurSp;

    /* ���漴����������Ķ�ջָ�� */
    guiNextTaskSp = pstrTcb->uiTaskCurSp;

    /* ���漴�����������TCB */
    gpstrCurTcb = pstrTcb;

    WLX_ContextSwitch();
}

/***********************************************************************************
��������: ��ʼ�����������.
��ڲ���: pstrTcb: �������е������TCBָ��.
�� �� ֵ: none.
***********************************************************************************/
void WLX_TaskStart(W_TCB* pstrTcb)
{
    /* ���漴����������Ķ�ջָ�� */
    guiNextTaskSp = pstrTcb->uiTaskCurSp;

    /* ���漴�����������TCB */
    gpstrCurTcb = pstrTcb;

    WLX_SwitchToTask();
}

