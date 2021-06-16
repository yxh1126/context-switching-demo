
#include "global.h"


/***********************************************************************************
函数功能: 延迟ms函数, 采用死循环延迟时间, 该函数的延迟时间与编译选项及芯片时钟相关.
入口参数: uiMs: 要延迟的时间, 单位ms.
返 回 值: none.
***********************************************************************************/
void DEV_DelayMs(U32 uiMs)
{
    U32 i;
    U32 j;

    j = 1265 * uiMs;

    for(i = 0; ; i++)
    {
        if(i == j)
        {
            break;
        }
    }
}

