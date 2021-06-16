
#include "test.h"

U8 gaucTask1Stack[TASKSTACK];       /* 任务1的堆栈 */
U8 gaucTask2Stack[TASKSTACK];       /* 任务2的堆栈 */
U8 gaucTask3Stack[TASKSTACK];       /* 任务3的堆栈 */

W_TCB* gpstrTask1Tcb;               /* 任务1的TCB指针 */
W_TCB* gpstrTask2Tcb;               /* 任务2的TCB指针 */
W_TCB* gpstrTask3Tcb;               /* 任务3的TCB指针 */



/***********************************************************************************
函数功能: 主函数, C程序从此函数开始运行. 该函数创建系统任务并从非任务状态切换到Root
          任务运行.
入口参数: none.
返 回 值: none.
***********************************************************************************/
S32 main(void)
{
    /* 初始化硬件 */
    DEV_HardwareInit();

    /* 创建任务 */
    gpstrTask1Tcb = WLX_TaskCreate((VFUNC)TEST_TestTask1, gaucTask1Stack,
                                   TASKSTACK);
    gpstrTask2Tcb = WLX_TaskCreate((VFUNC)TEST_TestTask2, gaucTask2Stack,
                                   TASKSTACK);
    gpstrTask3Tcb = WLX_TaskCreate((VFUNC)TEST_TestTask3, gaucTask3Stack,
                                   TASKSTACK);

    /* 开始任务调度, 从任务1开始执行 */
    WLX_TaskStart(gpstrTask1Tcb);

    return 0;
}

/***********************************************************************************
函数功能: 测试任务切换函数1, 向串口打印字符串.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void TEST_TestTask1(void)
{
    while(1)
    {
        DEV_PutString((U8*)"\r\nTask1 is running!");

        DEV_DelayMs(1000);              /* 延迟1s */

        WLX_TaskSwitch(gpstrTask3Tcb);  /* 任务切换 */
    }
}

/***********************************************************************************
函数功能: 测试任务切换函数2, 向串口打印字符串.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void TEST_TestTask2(void)
{
    while(1)
    {
        DEV_PutString((U8*)"\r\nTask2 is running!");

        DEV_DelayMs(2000);              /* 延迟2s */

        WLX_TaskSwitch(gpstrTask1Tcb);  /* 任务切换 */
    }
}

/***********************************************************************************
函数功能: 测试任务切换函数3, 向串口打印字符串.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void TEST_TestTask3(void)
{
    while(1)
    {
        DEV_PutString((U8*)"\r\nTask3 is running!");

        DEV_DelayMs(3000);              /* 延迟3s */

        WLX_TaskSwitch(gpstrTask2Tcb);  /* 任务切换 */
    }
}

