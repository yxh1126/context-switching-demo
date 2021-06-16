
#include "wlx_core_c.h"


U32 guiCurTask;                 /* 当前运行的任务 */
U32 guiNextTaskSp;              /* 将要运行的任务堆栈指针 */
U32* gpuiCurTaskSpAddr;         /* 存放当前运行任务堆栈指针的地址 */

U32 guiTask1CurSp;              /* 任务1当前的堆栈指针 */
U32 guiTask2CurSp;              /* 任务2当前的堆栈指针 */


/***********************************************************************************
函数功能: 创建任务运行前的状态.
入口参数: ucTask: 运行的任务, 1或者2.
          vfFuncPointer: 任务运行的函数指针.
          puiTaskStack: 任务使用的堆栈地址.
返 回 值: none.
***********************************************************************************/
void WLX_TaskInit(U8 ucTask, VFUNC vfFuncPointer, U32* puiTaskStack)
{
    U32* puiSp;

    /* 对堆栈初始化 */
    puiSp = puiTaskStack;               /* 获取堆栈指针 */

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

    /* 记录当前任务的堆栈指针, 下次运行这个任务时可根据该值恢复堆栈 */
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
函数功能: 调用该函数将发生任务切换.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void WLX_TaskSwitch(void)
{
    if(1 == guiCurTask)
    {
        /* 存入当前任务堆栈指针的地址 */
        gpuiCurTaskSpAddr = &guiTask1CurSp;

        /* 获取即将运行任务的堆栈指针 */
        guiNextTaskSp = guiTask2CurSp;

        /* 更新下次调度的任务 */
        guiCurTask = 2;
    }
    else //if(2 == guiCurTask)
    {
        gpuiCurTaskSpAddr = &guiTask2CurSp;

        guiNextTaskSp = guiTask1CurSp;

        guiCurTask = 1;
    }

    /* 切换任务 */
    WLX_ContextSwitch();
}

/***********************************************************************************
函数功能: 开始进入任务调度.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void WLX_TaskStart(void)
{
    /* 任务运行前不需要保存任务堆栈指针 */
    gpuiCurTaskSpAddr = (U32*)NULL;

    /* 获取即将运行任务的堆栈指针 */
    guiNextTaskSp = guiTask1CurSp;

    /* 更新下次调度的任务 */
    guiCurTask = 1;

    WLX_ContextSwitch();
}

