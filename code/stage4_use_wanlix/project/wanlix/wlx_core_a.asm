
    .include "wlx_core_a.h"


    .text
    .arm

    .func WLX_SwitchToTask
    .func WLX_ContextSwitch



; Function prototype in C format:
; void WLX_SwitchToTask( STACKREG* pstrNextTaskStackRegAddr );

WLX_SwitchToTask:
     
    ; resume the stack information of a new task
    LDMIA R0!,  {R4 - R12}   ; resume R4 to R12 registers
    LDMIA R0,   {R13}        ; resume Stack Pointer register
    ADD   R0,   #8           ; move R0 to the value of XPSR
    LDMIA R0,   {R1}         ; copy XPSR to R1 temporarily
    MSR   XPSR, R1           ; resume XPSR register
    SUB   R0,   #4           ; move R0 to point to LR
    LDMIA R0,   {PC}         ; copy LR to PC to start the task

    .endfunc



; Function prototype in C format:
; void WLX_ContextSwitch( STACKREG* pstrCurTaskStackRegAddr, 
;                         STACKREG* pstrNextTaskStackRegAddr );

WLX_ContextSwitch:

    ; save current task stack info to structure
    STMIA R0!,  {R4 - R12}   ; save R4 to R12 registers value
    STMIA R0!,  {R13}        ; save Stack Pointer value
    STMIA R0!,  {R14}        ; save Link Register value
    MRS   R2,   XPSR         ; get XPSR register value
    STMIA R0,   {R2}         ; save XPSR value

    ; resume the stack information of the next task from structure
    LDMIA R1!,  {R4 - R12}   ; resume R4 to R12 registers
    LDMIA R1,   {R13}        ; resume Stack Pointer register
    ADD   R1,   #8           ; move R0 to the value of XPSR
    LDMIA R1,   {R0}         ; copy XPSR to R1 temporarily
    MSR   XPSR, R0           ; resume XPSR register
    SUB   R1,   #4           ; move R0 to point to LR
    LDMIA R1,   {PC}         ; copy LR to PC to start the task

    .endfunc


    .end

