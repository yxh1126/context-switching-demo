
#ifndef  TEST_H
#define  TEST_H


#include "global.h"


#define STATE1TIME          300     /* 状态1的时间, 单位: Tick */
#define STATE2TIME          50      /* 状态2的时间, 单位: Tick */
#define STATE3TIME          100     /* 状态3的时间, 单位: Tick */
#define STATE4TIME          50      /* 状态4的时间, 单位: Tick */

#define FLASH1TIME          5       /* 闪烁的时间, 单位: Tick */


/* 灯状态定义 */
#define LEDSTATE_DARK       0       /* 常灭 */
#define LEDSTATE_LIGHT      1       /* 常亮 */
#define LEDSTATE_FLASH      2       /* 闪烁 */

#define LED_DARK            0       /* LED熄灭 */
#define LED_LIGHT           1       /* LED点亮 */


/* 灯定义 */
#define MASTER_RED          0       /* 主通道红灯 */
#define MASTER_YELLOW       1       /* 主通道黄灯 */
#define MASTER_GREEN        2       /* 主通道绿灯 */
#define SLAVE_RED           3       /* 从通道红灯 */
#define SLAVE_GREEN         4       /* 从通道绿灯 */
#define LEDNUM              5       /* 灯总数 */


/* 十字路口每种状态的初始值 */
#define CROSSINITVALUE \
{\
    {STATE1TIME, {{LEDSTATE_DARK, LED_DARK}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_DARK, LED_DARK}}},\
    {STATE2TIME, {{LEDSTATE_DARK, LED_DARK}, {LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_DARK, LED_DARK}}},\
    {STATE3TIME, {{LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_LIGHT, LED_LIGHT}}},\
    {STATE4TIME , {{LEDSTATE_LIGHT, LED_LIGHT}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_DARK, LED_DARK}, {LEDSTATE_FLASH, LED_DARK}}}\
}


/* LED灯状态 */
typedef struct ledstate
{
    U32 uiLedState;     /* 灯状态 */
    U32 uiBrightness;   /* 灯亮度 */
}LEDSTATE;

/* 路口状态结构体 */
typedef struct crossstatestr
{
    U32 uiRunTime;              /* 该状态运行时间, 单位: 秒 */
    LEDSTATE astrLed[LEDNUM];   /* 灯状态 */
}CROSSSTATESTR;


#endif

