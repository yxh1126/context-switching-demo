
#include "wlx_userboot.h"


/***********************************************************************************
函数功能: 根任务, 用户代码从这个函数开始执行.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void WLX_RootTask(void)
{
    /* 初始化软件 */
    DEV_SoftwareInit();

    /* 初始化硬件 */
    DEV_HardwareInit();

    /* 创建任务 */
    gpstrCrossStateTcb = WLX_TaskCreate((VFUNC)TEST_CrossStateTask,
                                        gaucCrossStateStack, TASKSTACK);
    gpstrLedDisplayTcb = WLX_TaskCreate((VFUNC)TEST_LedDisplayTask,
                                        gaucLedDisplayStack, TASKSTACK);

    WLX_TaskSwitch(gpstrCrossStateTcb);      /* 任务切换 */
}

