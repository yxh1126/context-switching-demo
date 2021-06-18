
#ifndef  TEST_H
#define  TEST_H


#include "global.h"


#define STATE1TIME          300     /* ״̬1��ʱ��, ��λ: Tick */
#define STATE2TIME          50      /* ״̬2��ʱ��, ��λ: Tick */
#define STATE3TIME          100     /* ״̬3��ʱ��, ��λ: Tick */
#define STATE4TIME          50      /* ״̬4��ʱ��, ��λ: Tick */

#define FLASH1TIME          5       /* ��˸��ʱ��, ��λ: Tick */


/* ��״̬���� */
#define LEDSTATE_DARK       0       /* ���� */
#define LEDSTATE_LIGHT      1       /* ���� */
#define LEDSTATE_FLASH      2       /* ��˸ */

#define LED_DARK            0       /* LEDϨ�� */
#define LED_LIGHT           1       /* LED���� */


/* �ƶ��� */
#define MASTER_RED          0       /* ��ͨ����� */
#define MASTER_YELLOW       1       /* ��ͨ���Ƶ� */
#define MASTER_GREEN        2       /* ��ͨ���̵� */
#define SLAVE_RED           3       /* ��ͨ����� */
#define SLAVE_GREEN         4       /* ��ͨ���̵� */
#define LEDNUM              5       /* ������ */


/* ʮ��·��ÿ��״̬�ĳ�ʼֵ */
#define CROSSINITVALUE \
{\
    {STATE1TIME, {{LEDSTATE_DARK, LED_DARK}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_DARK, LED_DARK}}},\
    {STATE2TIME, {{LEDSTATE_DARK, LED_DARK}, {LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_DARK, LED_DARK}}},\
    {STATE3TIME, {{LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_LIGHT, LED_LIGHT}}},\
    {STATE4TIME , {{LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_FLASH, LED_DARK}}}\
}


/* LED��״̬ */
typedef struct ledstate
{
    U32 uiLedState;     /* ��״̬ */
    U32 uiBrightness;   /* ������ */
}LEDSTATE;

/* ·��״̬�ṹ�� */
typedef struct crossstatestr
{
    U32 uiRunTime;              /* ��״̬����ʱ��, ��λ: �� */
    LEDSTATE astrLed[LEDNUM];   /* ��״̬ */
}CROSSSTATESTR;


#endif

