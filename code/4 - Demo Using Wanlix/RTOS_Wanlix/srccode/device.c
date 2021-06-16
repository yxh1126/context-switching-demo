
#include "device.h"


U32 guiSystemTick;      /* ϵͳTick */


/***********************************************************************************
��������: ��ʼ�����.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void DEV_SoftwareInit(void)
{
    /* ��ʼ��ʮ��·�ڱ��� */
    TEST_CrossVarInit();
}

/***********************************************************************************
��������: ��ʼ��Ӳ��.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void DEV_HardwareInit(void)
{
    /* ����GPIO�ܽ�ģʽ */
    DEV_SetGpioMode();

    /* ����Led�����ӵ�IOΪ���ģʽ, ���Ĭ��Ϊ�͵�ƽ */
    DEV_SetGpioDir(GPIOPORT3, GPIO_MR | GPIO_MY | GPIO_MG | GPIO_SR | GPIO_SG,
                   GPIO_MR | GPIO_MY | GPIO_MG | GPIO_SR | GPIO_SG,
                   (U8)(~(GPIO_MR | GPIO_MY | GPIO_MG | GPIO_SR | GPIO_SG)));

    DEV_TimerInit();

    DEV_IsrInit();
}

/***********************************************************************************
��������: ��ʼ���ж�.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void DEV_IsrInit(void)
{
    /* �ҽ�Tick�жϴ����� */
    IRQ = ISR_IrqIsr;

    /* ʹ���ж� */
    IRQEN = TIME1INTMASK | EXTIRQ0INTMASK;
}

/***********************************************************************************
��������: ��ʼ����ʱ��.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void DEV_TimerInit(void)
{
    /* ����Timer1, Timer1��Ϊϵͳ��tickʱ�� */
    T1LD = TICK * CORECLOCKPMS; /* ����tickʱ�� */
    T1CON = 0xC0;               /* ʹ�ܶ�ʱ��1, ʱ��Ƶ��41.78M, ����ѭ�����¼���  */
}

/***********************************************************************************
��������: ���ø���GPIO�Ĺ���ģʽ.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void DEV_SetGpioMode(void)
{
    /* ���йܽ�Ĭ��ΪGPIOģʽ */
    GP3CON = 0x00000000;
}

/***********************************************************************************
��������: ����GPIO����.
��ڲ���: ucPort: GPIO���ڵĶ˿�: 0~4.
          ucDir: GPIO����/�������, 0��1��, ÿ��bit��Ӧһ��pin.
          ucPin: GPIO�ܽ�, ��Ҫ���õ�bitΪ1, ����Ϊ0, ÿ��bit��Ӧһ��pin.
          ucOutPut: ����Ϊ���ģʽʱ�ĳ�ʼֵ, ÿ��bit��Ӧһ��pin.
�� �� ֵ: none.
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
��������: ��GPIO�ܽ����Ϊ1.
��ڲ���: ucPort: GPIO���ڵĶ˿�: 0~4.
          ucPin: GPIO�ܽ�, ��Ҫ���õ�bitΪ1, ����Ϊ0. Ϊ0��bit������0���Ǳ���ԭֵ.
�� �� ֵ: none.
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
��������: ��GPIO�ܽ����Ϊ0.
��ڲ���: ucPort: GPIO���ڵĶ˿�: 0~4.
          ucPin: GPIO�ܽ�, ��Ҫ�����bitΪ1, ����Ϊ0. Ϊ0��bit������0���Ǳ���ԭֵ.
�� �� ֵ: none.
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

