
    .include "wlx_core_a.h"


    .text
    .arm

    .func WLX_SwitchToTask
    .func WLX_ContextSwitch



; Function prototype in C format:
; void WLX_SwitchToTask( STACKREG* pstrNextTaskStackRegAddr );

WLX_SwitchToTask:
     
    ; resume the stack information of a new task
    MOV   R2,   R0           ; copy R0 to R2, since R0 value will be update by info from structure
    LDMIA R2!,  {R0, R4-R12} ; resume R0 and R4 to R12 registers
    LDMIA R2,   {R13}        ; resume Stack Pointer register
    ADD   R2,   #8           ; move R2 point to the value of XPSR
    LDMIA R2,   {R1}         ; copy XPSR to R1 temporarily
    MSR   XPSR, R1           ; resume XPSR register
    SUB   R2,   #4           ; move R2 to point to LR
    LDMIA R2,   {PC}         ; copy LR to PC to start the task

    .endfunc



; Function prototype in C format:
; void WLX_ContextSwitch( STACKREG* pstrCurTaskStackRegAddr, 
;                         STACKREG* pstrNextTaskStackRegAddr );

WLX_ContextSwitch:

    ; save current task stack info to structure
    MOV   R3,   R0           ; copy R0 to R3, save space for R0 restore
    STMIA R3!,  {R0, R4-R12} ; save R0 and R4 to R12 registers value
    STMIA R3!,  {R13}        ; save Stack Pointer value
    STMIA R3!,  {R14}        ; save Link Register value
    MRS   R2,   XPSR         ; get XPSR register value
    STMIA R3,   {R2}         ; save XPSR value

    ; resume the stack information of the next task from structure
    LDMIA R1!,  {R0, R4-R12} ; resume R0 and R4 to R12 registers
    LDMIA R1,   {R13}        ; resume Stack Pointer register
    ADD   R1,   #8           ; move R1 points to the value of XPSR
    LDMIA R1,   {R2}         ; copy XPSR to R2 temporarily
    MSR   XPSR, R2           ; resume XPSR register
    SUB   R1,   #4           ; move R1 to point to LR
    LDMIA R1,   {PC}         ; copy LR to PC to start the task

    .endfunc


    .end

