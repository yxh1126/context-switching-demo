
#include "device.h"


U32 guiSystemTick;      /* 系统Tick */


/***********************************************************************************
函数功能: 初始化软件.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void DEV_SoftwareInit(void)
{
    /* 初始化十字路口变量 */
    TEST_CrossVarInit();
}

/***********************************************************************************
函数功能: 初始化硬件.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void DEV_HardwareInit(void)
{
    /* 设置GPIO管脚模式 */
    DEV_SetGpioMode();

    /* 设置Led所连接的IO为输出模式, 输出默认为低电平 */
    DEV_SetGpioDir(GPIOPORT3, GPIO_MR | GPIO_MY | GPIO_MG | GPIO_SR | GPIO_SG,
                   GPIO_MR | GPIO_MY | GPIO_MG | GPIO_SR | GPIO_SG,
                   (U8)(~(GPIO_MR | GPIO_MY | GPIO_MG | GPIO_SR | GPIO_SG)));

    DEV_TimerInit();

    DEV_IsrInit();
}

/***********************************************************************************
函数功能: 初始化中断.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void DEV_IsrInit(void)
{
    /* 挂接Tick中断处理函数 */
    IRQ = ISR_IrqIsr;

    /* 使能中断 */
    IRQEN = TIME1INTMASK | EXTIRQ0INTMASK;
}

/***********************************************************************************
函数功能: 初始化定时器.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void DEV_TimerInit(void)
{
    /* 设置Timer1, Timer1作为系统的tick时钟 */
    T1LD = TICK * CORECLOCKPMS; /* 设置tick时间 */
    T1CON = 0xC0;               /* 使能定时器1, 时钟频率41.78M, 周期循环向下计数  */
}

/***********************************************************************************
函数功能: 设置各个GPIO的工作模式.
入口参数: none.
返 回 值: none.
***********************************************************************************/
void DEV_SetGpioMode(void)
{
    /* 所有管脚默认为GPIO模式 */
    GP3CON = 0x00000000;
}

/***********************************************************************************
函数功能: 设置GPIO方向.
入口参数: ucPort: GPIO所在的端口: 0~4.
          ucDir: GPIO输入/输出方向, 0进1出, 每个bit对应一个pin.
          ucPin: GPIO管脚, 需要设置的bit为1, 否则为0, 每个bit对应一个pin.
          ucOutPut: 配置为输出模式时的初始值, 每个bit对应一个pin.
返 回 值: none.
***********************************************************************************/
void DEV_SetGpioDir(U8 ucPort, U8 ucDir, U8 ucPin, U8 ucOutPut)
{
    U32 uiGpioValue;

    if(GPIOPORT0 == ucPort)
    {
        uiGpioValue = GP0DAT;
        uiGpioValue &= (~(((U32)ucPin << 24) | ((U32)ucOutPut << 16)));
        uiGpioValue |= (((U32)(ucDir & ucPin) << 24)
                        | ((U32)(ucOutPut & ucPin) << 16));
        GP0DAT = uiGpioValue;
    }
    else if(GPIOPORT1 == ucPort)
    {
        uiGpioValue = GP1DAT;
        uiGpioValue &= (~(((U32)ucPin << 24) | ((U32)ucOutPut << 16)));
        uiGpioValue |= (((U32)(ucDir & ucPin) << 24)
                        | ((U32)(ucOutPut & ucPin) << 16));
        GP1DAT = uiGpioValue;
    }
    else if(GPIOPORT2 == ucPort)
    {
        uiGpioValue = GP2DAT;
        uiGpioValue &= (~(((U32)ucPin << 24) | ((U32)ucOutPut << 16)));
        uiGpioValue |= (((U32)(ucDir & ucPin) << 24)
                        | ((U32)(ucOutPut & ucPin) << 16));
        GP2DAT = uiGpioValue;
    }
    else if(GPIOPORT3 == ucPort)
    {
        uiGpioValue = GP3DAT;
        uiGpioValue &= (~(((U32)ucPin << 24) | ((U32)ucOutPut << 16)));
        uiGpioValue |= (((U32)(ucDir & ucPin) << 24)
                        | ((U32)(ucOutPut & ucPin) << 16));
        GP3DAT = uiGpioValue;
    }
    else //if(GPIOPORT4 == ucPort)
    {
        uiGpioValue = GP4DAT;
        uiGpioValue &= (~(((U32)ucPin << 24) | ((U32)ucOutPut << 16)));
        uiGpioValue |= (((U32)(ucDir & ucPin) << 24)
                        | ((U32)(ucOutPut & ucPin) << 16));
        GP4DAT = uiGpioValue;
    }
}

/***********************************************************************************
函数功能: 置GPIO管脚输出为1.
入口参数: ucPort: GPIO所在的端口: 0~4.
          ucPin: GPIO管脚, 需要设置的bit为1, 否则为0. 为0的bit并不清0而是保持原值.
返 回 值: none.
***********************************************************************************/
void DEV_SetGpio(U8 ucPort, U8 ucPin)
{
    if(0 == ucPort)
    {
        GP0SET = ((U32)ucPin << 16);
    }
    else if(1 == ucPort)
    {
        GP1SET = ((U32)ucPin << 16);
    }
    else if(2 == ucPort)
    {
        GP2SET = ((U32)ucPin << 16);
    }
    else if(3 == ucPort)
    {
        GP3SET = ((U32)ucPin << 16);
    }
    else //if(4 == ucPort)
    {
        GP4SET = ((U32)ucPin << 16);
    }
}

/***********************************************************************************
函数功能: 置GPIO管脚输出为0.
入口参数: ucPort: GPIO所在的端口: 0~4.
          ucPin: GPIO管脚, 需要清除的bit为1, 否则为0. 为0的bit并不清0而是保持原值.
返 回 值: none.
***********************************************************************************/
void DEV_ClrGpio(U8 ucPort, U8 ucPin)
{
    if(0 == ucPort)
    {
        GP0CLR = ((U32)ucPin << 16);
    }
    else if(1 == ucPort)
    {
        GP1CLR = ((U32)ucPin << 16);
    }
    else if(2 == ucPort)
    {
        GP2CLR = ((U32)ucPin << 16);
    }
    else if(3 == ucPort)
    {
        GP3CLR = ((U32)ucPin << 16);
    }
    else //if(4 == ucPort)
    {
        GP4CLR = ((U32)ucPin << 16);
    }
}

