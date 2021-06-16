
#ifndef  DEVICE_H
#define  DEVICE_H


#include "global.h"


#define TICK                100         /* Tick时间, 单位: ms */
#define CORECLOCKPMS        41780       /* 芯片内核每ms振荡频率 */


/*********************************** 函数声明 *************************************/
extern void DEV_TimerInit(void);
extern void DEV_IsrInit(void);
extern void DEV_SetGpioMode(void);
extern void DEV_SetGpioDir(U8 ucPort, U8 ucDir, U8 ucPin, U8 ucOutPut);


#endif

