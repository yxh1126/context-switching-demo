
#include "test.h"

U8 gaucCrossStateStack[TASKSTACK];  /* 十字路口状态任务的堆栈 */
U8 gaucLedDisplayStack[TASKSTACK];  /* 十字路口灯显示任务的堆栈 */

W_TCB* gpstrCrossStateTcb;          /* 十字路口状态任务的TCB指针 */
W_TCB* gpstrLedDisplayTcb;          /* 十字路口灯显示任务的TCB指针 */


/* 十字路口各种状态 */
CROSSSTATESTR gastrCrossSta[CROSSSTATENUM] = CROSSINITVALUE;

/* 十字路口当前状态 */
CROSSSTATESTR gstrCurCrossSta;


U32 guiCurSta;          /* 十字路口当前所处的状态 */
U32 guiStaChange;       /*  0: 十字路口状态未改变, 其它: 状态改变 */


/***********************************************************************************
函数功能: 十字路口变量初始化函数.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void TEST_CrossVarInit(void)
{
    guiSystemTick = 0;
    guiCurSta = CROSSSTATE1;
    guiStaChange = 1;   /* 初始化为状态未改变 */
}

/***********************************************************************************
函数功能: 改变十字路口灯状态任务.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void TEST_CrossStateTask(void)
{
    U32 uiStaEndTick;
    U32 uiFlashEndTick;
    U32 i;

    /* 为屏蔽告警, 为变量赋初值 */
    uiStaEndTick = 0;
    uiFlashEndTick = 0;

    while(1)
    {
        /* 锁中断, 防止行人中断影响状态判断 */
        ISR_PassengerIntLock();

        /* 状态改变 */
        if(0 != guiStaChange)
        {
            guiStaChange = 0;

            /* 获取新状态的参数 */
            gstrCurCrossSta = gastrCrossSta[guiCurSta];

            /* 计算该状态结束时的Tick. Tick溢出后会从0重新开始 */
            uiStaEndTick = guiSystemTick + gstrCurCrossSta.uiRunTime;

            /* 计算闪烁状态灯亮度切换的Tick. Tick溢出后会从0重新开始 */
            uiFlashEndTick = guiSystemTick + FLASH1TIME;
        }

        /* 当前转该时间到, 需要切换到下一个状态 */
        if(uiStaEndTick == guiSystemTick)
        {
            /* 置为状态改变 */
            guiStaChange = 1;

            /* 寻找下一个状态 */
            if(guiCurSta < CROSSSTATENUM - 1)
            {
                guiCurSta++;
            }
            else
            {
                guiCurSta = 0;
            }
        }
        else
        {
            /* 闪烁状态灯亮度切换时间到, 需要切换灯亮度 */
            if(uiFlashEndTick == guiSystemTick)
            {
                /* 循环判断各个灯的闪烁状态 */
                for(i = 0; i < LEDNUM; i++)
                {
                    /* 该灯不是闪烁状态则进行下个灯的判断 */
                    if(LEDSTATE_FLASH != gstrCurCrossSta.astrLed[i].uiLedState)
                    {
                        continue;
                    }
                    else /* 闪烁状态 */
                    {
                        /* 改变灯的亮度, 亮灭互转 */
                        if(LED_DARK == gstrCurCrossSta.astrLed[i].uiBrightness)
                        {
                            gstrCurCrossSta.astrLed[i].uiBrightness = LED_LIGHT;
                        }
                        else
                        {
                            gstrCurCrossSta.astrLed[i].uiBrightness = LED_DARK;
                        }

                        /* 更新下个闪烁时间 */
                        uiFlashEndTick = guiSystemTick + FLASH1TIME;
                    }
                }
            }
        }

        /* 解锁中断 */
        ISR_PassengerIntUnlock();

        /* 切换到控制灯亮度的任务 */
        WLX_TaskSwitch(gpstrLedDisplayTcb);

    }
}

/***********************************************************************************
函数功能: 改变十字路口灯显示任务.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void TEST_LedDisplayTask(void)
{
    U32 i;

    while(1)
    {
        /* 根据各个灯的状态控制灯的亮度 */
        for(i = 0; i < LEDNUM; i++)
        {
            /* 设置灯的亮度 */
            TEST_LedSet(i, gstrCurCrossSta.astrLed[i].uiBrightness);
        }

        /* 切换到控制灯状态的任务 */
        WLX_TaskSwitch(gpstrCrossStateTcb);
    }
}

/***********************************************************************************
函数功能: 设置GPIO方向.
入口参数: uiLedNo: Led灯编号.
          uiLedSta: Led灯状态.
返 回 值: none.
***********************************************************************************/
void TEST_LedSet(U32 uiLedNo, U32 uiLedSta)
{
    /* 将灯熄灭 */
    if(LED_DARK == uiLedSta)
    {
        /* 根据灯编号设置不同的GPIO管脚 */
        switch(uiLedNo)
        {
            case MASTER_RED:

                DEV_ClrGpio(GPIOPORT3, GPIO_MR);

                break;

            case MASTER_YELLOW:

                DEV_ClrGpio(GPIOPORT3, GPIO_MY);

                break;

            case MASTER_GREEN:

                DEV_ClrGpio(GPIOPORT3, GPIO_MG);

                break;

            case SLAVE_RED:

                DEV_ClrGpio(GPIOPORT3, GPIO_SR);

                break;

            case SLAVE_GREEN:

                DEV_ClrGpio(GPIOPORT3, GPIO_SG);

                break;
        }
    }
    /* 将灯点亮 */
    else //if(LED_LIGHT == uiLedSta)
    {
        /* 根据灯编号设置不同的GPIO管脚 */
        switch(uiLedNo)
        {
            case MASTER_RED:

                DEV_SetGpio(GPIOPORT3, GPIO_MR);

                break;

            case MASTER_YELLOW:

                DEV_SetGpio(GPIOPORT3, GPIO_MY);

                break;

            case MASTER_GREEN:

                DEV_SetGpio(GPIOPORT3, GPIO_MG);

                break;

            case SLAVE_RED:

                DEV_SetGpio(GPIOPORT3, GPIO_SR);

                break;

            case SLAVE_GREEN:

                DEV_SetGpio(GPIOPORT3, GPIO_SG);

                break;
        }
    }
}

