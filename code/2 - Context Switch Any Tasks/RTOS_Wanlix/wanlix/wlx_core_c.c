
#include "wlx_core_c.h"


W_TCB* gpstrCurTcb;             /* 当前运行的任务的TCB */
U32 guiNextTaskSp;              /* 将要运行的任务堆栈指针 */
U32* gpuiCurTaskSpAddr;         /* 存放当前运行任务堆栈指针的地址 */


/***********************************************************************************
函数功能: 创建一个任务.
入口参数: vfFuncPointer: 创建任务所使用函数的指针.
          pucTaskStack: 任务所使用堆栈的最低起始地址.
          uiStackSize: 堆栈大小, 单位: 字节.
返 回 值: NULL: 创建任务失败.
          其它: 任务的TCB指针.
***********************************************************************************/
W_TCB* WLX_TaskCreate(VFUNC vfFuncPointer, U8* pucTaskStack, U32 uiStackSize)
{
    W_TCB* pstrTcb;

    /* 对创建任务所使用函数的指针合法性进行检查 */
    if(NULL == vfFuncPointer)
    {
        /* 指针为空, 返回失败 */
        return (W_TCB*)NULL;
    }

    /* 对任务堆栈合法性进行检查 */
    if((NULL == pucTaskStack) || (0 == uiStackSize))
    {
        /* 堆栈不合法, 返回失败 */
        return (W_TCB*)NULL;
    }

    /* 初始化TCB */
    pstrTcb = WLX_TaskTcbInit(pucTaskStack, uiStackSize);

    /* 初始化任务堆栈 */
    WLX_TaskStackInit(pstrTcb, vfFuncPointer);

    return pstrTcb;
}

/***********************************************************************************
函数功能: 初始化任务TCB, 用来创建任务运行前TCB的状态.
入口参数: pucTaskStack: 任务所使用的堆栈地址.
          uiStackSize: 堆栈大小, 单位: 字节.
返 回 值: 任务TCB的指针.
***********************************************************************************/
W_TCB* WLX_TaskTcbInit(U8* pucTaskStack, U32 uiStackSize)
{
    W_TCB* pstrTcb;
    U8* pucStackBy4;

    /* 堆栈满地址, 需要4字节对齐 */
    pucStackBy4 = (U8*)(((U32)pucTaskStack + uiStackSize) & 0xFFFFFFFC);

    /* TCB结构存放的地址, 需要4字节对齐 */
    pstrTcb = (W_TCB*)(((U32)pucStackBy4 - sizeof(W_TCB)) & 0xFFFFFFFC);

    /* 初始化TCB结构 */
    pstrTcb->uiTaskCurSp = (U32)pstrTcb;

    return pstrTcb;
}

/***********************************************************************************
函数功能: 初始化任务堆栈函数, 用来创建任务运行前的堆栈状态.
入口参数: pstrTcb: 任务的TCB指针.
          vfFuncPointer: 任务运行的函数.
返 回 值: none.
***********************************************************************************/
void WLX_TaskStackInit(W_TCB* pstrTcb, VFUNC vfFuncPointer)
{
    U32* puiSp;

    /* 对堆栈初始化 */
    puiSp = (U32*)pstrTcb->uiTaskCurSp; /* 获取存放变量的堆栈指针 */

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

    /* 记录当前任务的堆栈指针, 下次运行这个任务时可根据该值恢复堆栈 */
    pstrTcb->uiTaskCurSp = (U32)puiSp;
}

/***********************************************************************************
函数功能: 调用该函数将发生任务切换.
入口参数: pstrTcb: 即将运行的任务的TCB指针.
返 回 值: none.
***********************************************************************************/
void WLX_TaskSwitch(W_TCB* pstrTcb)
{
    /* 保存当前任务堆栈指针的地址, 在汇编语言可以通过这个变量写入任务切换前最后时刻
       的堆栈地址 */
    gpuiCurTaskSpAddr = &gpstrCurTcb->uiTaskCurSp;

    /* 保存即将运行任务的堆栈指针 */
    guiNextTaskSp = pstrTcb->uiTaskCurSp;

    /* 保存即将运行任务的TCB */
    gpstrCurTcb = pstrTcb;

    WLX_ContextSwitch();
}

/***********************************************************************************
函数功能: 开始进入任务调度.
入口参数: pstrTcb: 即将运行的任务的TCB指针.
返 回 值: none.
***********************************************************************************/
void WLX_TaskStart(W_TCB* pstrTcb)
{
    /* 保存即将运行任务的堆栈指针 */
    guiNextTaskSp = pstrTcb->uiTaskCurSp;

    /* 保存即将运行任务的TCB */
    gpstrCurTcb = pstrTcb;

    WLX_SwitchToTask();
}

