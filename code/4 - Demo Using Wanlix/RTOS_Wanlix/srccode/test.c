
#include "test.h"

U8 gaucCrossStateStack[TASKSTACK];  /* ʮ��·��״̬����Ķ�ջ */
U8 gaucLedDisplayStack[TASKSTACK];  /* ʮ��·�ڵ���ʾ����Ķ�ջ */

W_TCB* gpstrCrossStateTcb;          /* ʮ��·��״̬�����TCBָ�� */
W_TCB* gpstrLedDisplayTcb;          /* ʮ��·�ڵ���ʾ�����TCBָ�� */


/* ʮ��·�ڸ���״̬ */
CROSSSTATESTR gastrCrossSta[CROSSSTATENUM] = CROSSINITVALUE;

/* ʮ��·�ڵ�ǰ״̬ */
CROSSSTATESTR gstrCurCrossSta;


U32 guiCurSta;          /* ʮ��·�ڵ�ǰ������״̬ */
U32 guiStaChange;       /*  0: ʮ��·��״̬δ�ı�, ����: ״̬�ı� */


/***********************************************************************************
��������: ʮ��·�ڱ�����ʼ������.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void TEST_CrossVarInit(void)
{
    guiSystemTick = 0;
    guiCurSta = CROSSSTATE1;
    guiStaChange = 1;   /* ��ʼ��Ϊ״̬δ�ı� */
}

/***********************************************************************************
��������: �ı�ʮ��·�ڵ�״̬����.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void TEST_CrossStateTask(void)
{
    U32 uiStaEndTick;
    U32 uiFlashEndTick;
    U32 i;

    /* Ϊ���θ澯, Ϊ��������ֵ */
    uiStaEndTick = 0;
    uiFlashEndTick = 0;

    while(1)
    {
        /* ���ж�, ��ֹ�����ж�Ӱ��״̬�ж� */
        ISR_PassengerIntLock();

        /* ״̬�ı� */
        if(0 != guiStaChange)
        {
            guiStaChange = 0;

            /* ��ȡ��״̬�Ĳ��� */
            gstrCurCrossSta = gastrCrossSta[guiCurSta];

            /* �����״̬����ʱ��Tick. Tick�������0���¿�ʼ */
            uiStaEndTick = guiSystemTick + gstrCurCrossSta.uiRunTime;

            /* ������˸״̬�������л���Tick. Tick�������0���¿�ʼ */
            uiFlashEndTick = guiSystemTick + FLASH1TIME;
        }

        /* ��ǰת��ʱ�䵽, ��Ҫ�л�����һ��״̬ */
        if(uiStaEndTick == guiSystemTick)
        {
            /* ��Ϊ״̬�ı� */
            guiStaChange = 1;

            /* Ѱ����һ��״̬ */
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
            /* ��˸״̬�������л�ʱ�䵽, ��Ҫ�л������� */
            if(uiFlashEndTick == guiSystemTick)
            {
                /* ѭ���жϸ����Ƶ���˸״̬ */
                for(i = 0; i < LEDNUM; i++)
                {
                    /* �õƲ�����˸״̬������¸��Ƶ��ж� */
                    if(LEDSTATE_FLASH != gstrCurCrossSta.astrLed[i].uiLedState)
                    {
                        continue;
                    }
                    else /* ��˸״̬ */
                    {
                        /* �ı�Ƶ�����, ����ת */
                        if(LED_DARK == gstrCurCrossSta.astrLed[i].uiBrightness)
                        {
                            gstrCurCrossSta.astrLed[i].uiBrightness = LED_LIGHT;
                        }
                        else
                        {
                            gstrCurCrossSta.astrLed[i].uiBrightness = LED_DARK;
                        }

                        /* �����¸���˸ʱ�� */
                        uiFlashEndTick = guiSystemTick + FLASH1TIME;
                    }
                }
            }
        }

        /* �����ж� */
        ISR_PassengerIntUnlock();

        /* �л������Ƶ����ȵ����� */
        WLX_TaskSwitch(gpstrLedDisplayTcb);

    }
}

/***********************************************************************************
��������: �ı�ʮ��·�ڵ���ʾ����.
��ڲ���: none.
�� �� ֵ: none.
***********************************************************************************/
void TEST_LedDisplayTask(void)
{
    U32 i;

    while(1)
    {
        /* ���ݸ����Ƶ�״̬���ƵƵ����� */
        for(i = 0; i < LEDNUM; i++)
        {
            /* ���õƵ����� */
            TEST_LedSet(i, gstrCurCrossSta.astrLed[i].uiBrightness);
        }

        /* �л������Ƶ�״̬������ */
        WLX_TaskSwitch(gpstrCrossStateTcb);
    }
}

/***********************************************************************************
��������: ����GPIO����.
��ڲ���: uiLedNo: Led�Ʊ��.
          uiLedSta: Led��״̬.
�� �� ֵ: none.
***********************************************************************************/
void TEST_LedSet(U32 uiLedNo, U32 uiLedSta)
{
    /* ����Ϩ�� */
    if(LED_DARK == uiLedSta)
    {
        /* ���ݵƱ�����ò�ͬ��GPIO�ܽ� */
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
    /* ���Ƶ��� */
    else //if(LED_LIGHT == uiLedSta)
    {
        /* ���ݵƱ�����ò�ͬ��GPIO�ܽ� */
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

