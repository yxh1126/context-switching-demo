
    .include "wlx_core_a.h"


    .text
    .arm

    @��������: ʵ�������л�����, ���Ĵ������ݵ���ǰ�����ջ��, �ӽ�Ҫ���������ջ��
    @          ȡ���Ĵ�������ֵ����ת����Ҫ��������ִ��.
    @��ڲ���: none.
    @�� �� ֵ: none.
    .func WLX_ContextSwitch
WLX_ContextSwitch:

    @���浱ǰ����Ķ�ջ��Ϣ
    STMDB  R13, {R0-R14}
    SUB    R13, R13, #0x3C
    MRS    R0, CPSR
    STMDB  R13!, {R0}

    @���浱ǰ�����ָ��ֵ
    LDR    R0, =gpuiCurTaskSpAddr
    LDR    R1, [R0]
    STR    R13, [R1]

    @��ȡ��Ҫ���������ָ��
    LDR    R0, =guiNextTaskSp
    LDR    R13, [R0]

    @��ȡ��Ҫ��������Ķ�ջ��Ϣ������������
    LDMIA  R13!, {R0}
    MSR    CPSR, R0
    LDMIA  R13, {R0-R14}
    BX     R14

    .endfunc


    @��������: ʵ�ִ��޲���ϵͳ״̬�л�������ϵͳ״̬, ��Root�����ջ��ȡ���Ĵ�����
    @          ��ֵ����ת��Root����ִ��.
    @��ڲ���: none.
    @�� �� ֵ: none.
    .func WLX_SwitchToTask
WLX_SwitchToTask:

    @��ȡ��Ҫ���������ָ��
    LDR    R0, =guiNextTaskSp
    LDR    R13, [R0]

    @��ȡ��Ҫ��������Ķ�ջ��Ϣ������������
    LDMIA  R13!, {R0}
    MSR    CPSR, R0
    LDMIA  R13, {R0-R14}
    BX     R14

    .endfunc


    .end

