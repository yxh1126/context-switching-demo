
    .include "wlx_core_a.h"


    .text
    .arm

    @函数功能: 实现任务切换功能, 将寄存器备份到当前任务堆栈中, 从将要运行任务堆栈中
    @          取出寄存器保存值并跳转到将要运行任务执行.
    @入口参数: none.
    @返 回 值: none.
    .func WLX_ContextSwitch
WLX_ContextSwitch:

    @保存当前任务的堆栈信息
    STMDB  R13, {R0-R14}
    SUB    R13, R13, #0x3C
    MRS    R0, CPSR
    STMDB  R13!, {R0}

    @保存当前任务的指针值
    LDR    R0, =gpuiCurTaskSpAddr
    LDR    R1, [R0]
    STR    R13, [R1]

    @获取将要运行任务的指针
    LDR    R0, =guiNextTaskSp
    LDR    R13, [R0]

    @获取将要运行任务的堆栈信息并运行新任务
    LDMIA  R13!, {R0}
    MSR    CPSR, R0
    LDMIA  R13, {R0-R14}
    BX     R14

    .endfunc


    @函数功能: 实现从无操作系统状态切换到操作系统状态, 从Root任务堆栈中取出寄存器保
    @          存值并跳转到Root任务执行.
    @入口参数: none.
    @返 回 值: none.
    .func WLX_SwitchToTask
WLX_SwitchToTask:

    @获取将要运行任务的指针
    LDR    R0, =guiNextTaskSp
    LDR    R13, [R0]

    @获取将要运行任务的堆栈信息并运行新任务
    LDMIA  R13!, {R0}
    MSR    CPSR, R0
    LDMIA  R13, {R0-R14}
    BX     R14

    .endfunc


    .end

