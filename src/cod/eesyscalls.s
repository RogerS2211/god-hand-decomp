# src/cod/eesyscalls.s — EE OSDsys / libsce.a syscall trampoline table.
# 138 stubs spanning 0x003AF880 – 0x003B0110. Hand-authored
# Each stub is exactly 16 B:
#   addiu  $v1, $zero, <num>
#   syscall 0
#   jr     $ra
#    nop

    .set noreorder
    .set noat

    # SYSCALL_STUB name, num: emit one 16-byte EE kernel syscall trampoline.
    # Each stub gets its own .text.<name> section so the build-time lcf
    # can place multiple stubs from this TU at distinct VMAs via per-
    # function (.text.<name>) references. Pattern matches the C-TU
    # per-function section convention (see compile.py _carve_obj_and_section).
    .macro SYSCALL_STUB name, num
    .section .text.\name, "ax"
    .align 3
    .globl \name
    .type \name, @function
\name:
    addiu  $v1, $zero, \num
    syscall 0
    jr     $ra
    nop
    .size \name, .-\name
    .endm

    SYSCALL_STUB EESyscall_0x00, 0x0
    SYSCALL_STUB ResetEE, 0x1
    SYSCALL_STUB SetGsCrt, 0x2
    SYSCALL_STUB EESyscall_0x03, 0x3
    SYSCALL_STUB KExit, 0x4
    SYSCALL_STUB ResumeIntrDispatch, 0x5
    SYSCALL_STUB LoadExecPS2, 0x6
    SYSCALL_STUB ExecPS2, 0x7
    SYSCALL_STUB ResumeT3IntrDispatch, 0x8
    SYSCALL_STUB RFU009, 0x9
    SYSCALL_STUB AddSbusIntcHandler, 0xA
    SYSCALL_STUB RemoveSbusIntcHandler, 0xB
    SYSCALL_STUB Interrupt2Iop, 0xC
    SYSCALL_STUB SetVTLBRefillHandler, 0xD
    SYSCALL_STUB SetVCommonHandler, 0xE
    SYSCALL_STUB SetVInterruptHandler, 0xF
    SYSCALL_STUB AddIntcHandler, 0x10
    SYSCALL_STUB AddIntcHandler2, 0x10
    SYSCALL_STUB RemoveIntcHandler, 0x11
    SYSCALL_STUB AddDmacHandler, 0x12
    SYSCALL_STUB AddDmacHandler2, 0x12
    SYSCALL_STUB RemoveDmacHandler, 0x13
    SYSCALL_STUB EnableIntc, 0x14
    SYSCALL_STUB DisableIntc, 0x15
    SYSCALL_STUB EnableDmac, 0x16
    SYSCALL_STUB DisableDmac, 0x17
    SYSCALL_STUB EESyscall_0xFC, 0xFC
    SYSCALL_STUB EESyscall_0xFD, 0xFD
    SYSCALL_STUB iEnableIntc, -0x1A
    SYSCALL_STUB iDisableIntc, -0x1B
    SYSCALL_STUB iEnableDmac, -0x1C
    SYSCALL_STUB iDisableDmac, -0x1D
    SYSCALL_STUB EESyscall_neg_0xFE, -0xFE
    SYSCALL_STUB EESyscall_neg_0xFF, -0xFF
    SYSCALL_STUB CreateThread, 0x20
    SYSCALL_STUB DeleteThread, 0x21
    SYSCALL_STUB StartThread, 0x22
    SYSCALL_STUB ExitThread, 0x23
    SYSCALL_STUB ExitDeleteThread, 0x24
    SYSCALL_STUB TerminateThread, 0x25
    SYSCALL_STUB iTerminateThread, -0x26
    SYSCALL_STUB DisableDispatchThread, 0x27
    SYSCALL_STUB EnableDispatchThread, 0x28
    SYSCALL_STUB ChangeThreadPriority, 0x29
    SYSCALL_STUB iChangeThreadPriority, -0x2A
    SYSCALL_STUB RotateThreadReadyQueue, 0x2B
    SYSCALL_STUB iRotateThreadReadyQueue, -0x2C
    SYSCALL_STUB ReleaseWaitThread, 0x2D
    SYSCALL_STUB iReleaseWaitThread, -0x2E
    SYSCALL_STUB GetThreadId, 0x2F
    SYSCALL_STUB ReferThreadStatus, 0x30
    SYSCALL_STUB iReferThreadStatus, -0x31
    SYSCALL_STUB SleepThread, 0x32
    SYSCALL_STUB WakeupThread, 0x33
    SYSCALL_STUB iWakeupThread, -0x34
    SYSCALL_STUB CancelWakeupThread, 0x35
    SYSCALL_STUB iCancelWakeupThread, -0x36
    SYSCALL_STUB SuspendThread, 0x37
    SYSCALL_STUB iSuspendThread, -0x38
    SYSCALL_STUB ResumeThread, 0x39
    SYSCALL_STUB iResumeThread, -0x3A
    SYSCALL_STUB RFU059, 0x3B
    SYSCALL_STUB SetupThread, 0x3C
    SYSCALL_STUB SetupHeap, 0x3D
    SYSCALL_STUB EndOfHeap, 0x3E
    SYSCALL_STUB EESyscall_0x3F, 0x3F
    SYSCALL_STUB CreateSema, 0x40
    SYSCALL_STUB DeleteSema, 0x41
    SYSCALL_STUB SignalSema, 0x42
    SYSCALL_STUB iSignalSema, -0x43
    SYSCALL_STUB WaitSema, 0x44
    SYSCALL_STUB PollSema, 0x45
    SYSCALL_STUB iPollSema, -0x46
    SYSCALL_STUB ReferSemaStatus, 0x47
    SYSCALL_STUB iReferSemaStatus, -0x48
    SYSCALL_STUB EESyscall_0x49, 0x49
    SYSCALL_STUB SetOsdConfigParam, 0x4A
    SYSCALL_STUB GetOsdConfigParam, 0x4B
    SYSCALL_STUB GetGsHParam, 0x4C
    SYSCALL_STUB GetGsVParam, 0x4D
    SYSCALL_STUB SetGsHParam, 0x4E
    SYSCALL_STUB SetGsVParam, 0x4F
    SYSCALL_STUB CreateEventFlag, 0x50
    SYSCALL_STUB DeleteEventFlag, 0x51
    SYSCALL_STUB SetEventFlag, 0x52
    SYSCALL_STUB EESyscall_neg_0x53, -0x53
    SYSCALL_STUB xlaunch, 0x54
    SYSCALL_STUB iPutTLBEntry, -0x55
    SYSCALL_STUB SetTLBEntry, 0x56
    SYSCALL_STUB GetTLBEntry, 0x57
    SYSCALL_STUB iProbeTLBEntry, -0x58
    SYSCALL_STUB ExpandScratchPad, 0x59
    SYSCALL_STUB EESyscall_neg_0x5A, -0x5A
    SYSCALL_STUB GetEntryAddress, 0x5B
    SYSCALL_STUB EnableIntcHandler, 0x5C
    SYSCALL_STUB iEnableIntcHandler, -0x5C
    SYSCALL_STUB DisableIntcHandler, 0x5D
    SYSCALL_STUB iDisableIntcHandler, -0x5D
    SYSCALL_STUB EnableDmacHandler, 0x5E
    SYSCALL_STUB iEnableDmacHandler, -0x5E
    SYSCALL_STUB DisableDmacHandler, 0x5F
    SYSCALL_STUB iDisableDmacHandler, -0x5F
    SYSCALL_STUB KSeg0, 0x60
    SYSCALL_STUB EnableCache, 0x61
    SYSCALL_STUB DisableCache, 0x62
    SYSCALL_STUB GetCop0, 0x63
    SYSCALL_STUB FlushCache, 0x64
    SYSCALL_STUB CpuConfig, 0x66
    SYSCALL_STUB iGetCop0, -0x67
    SYSCALL_STUB iFlushCache, -0x68
    SYSCALL_STUB iCpuConfig, -0x6A
    SYSCALL_STUB SifStopDma, 0x6B
    SYSCALL_STUB SetCPUTimerHandler, 0x6C
    SYSCALL_STUB SetCPUTimer, 0x6D
    SYSCALL_STUB SetOsdConfigParam2, 0x6E
    SYSCALL_STUB GetOsdConfigParam2, 0x6F
    SYSCALL_STUB GsGetIMR, 0x70
    SYSCALL_STUB iGsGetIMR, -0x70
    SYSCALL_STUB GsPutIMR, 0x71
    SYSCALL_STUB iGsPutIMR, -0x71
    SYSCALL_STUB SetPgifHandler, 0x72
    SYSCALL_STUB SetVSyncFlag, 0x73
    SYSCALL_STUB SetSyscall, 0x74
    SYSCALL_STUB ee_print, 0x75
    SYSCALL_STUB SifDmaStat, 0x76
    SYSCALL_STUB isceSifDmaStat, -0x76
    SYSCALL_STUB SifSetDma, 0x77
    SYSCALL_STUB isceSifSetDma, -0x77
    SYSCALL_STUB SifSetDChain, 0x78
    SYSCALL_STUB isceSifSetDChain, -0x78
    SYSCALL_STUB SifSetReg, 0x79
    SYSCALL_STUB SifGetReg, 0x7A
    SYSCALL_STUB ExecOSD, 0x7B
    SYSCALL_STUB Deci2Call, 0x7C
    SYSCALL_STUB PSMode, 0x7D
    SYSCALL_STUB MachineType, 0x7E
    SYSCALL_STUB GetMemorySize, 0x7F
    SYSCALL_STUB InitTLB, 0x82
