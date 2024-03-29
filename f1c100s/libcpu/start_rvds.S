;/*
; * File      : start_rvds.S
; * This file is part of RT-Thread RTOS
; * COPYRIGHT (C) 2006, RT-Thread Development Team
; *
; *  This program is free software; you can redistribute it and/or modify
; *  it under the terms of the GNU General Public License as published by
; *  the Free Software Foundation; either version 2 of the License, or
; *  (at your option) any later version.
; *
; *  This program is distributed in the hope that it will be useful,
; *  but WITHOUT ANY WARRANTY; without even the implied warranty of
; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; *  GNU General Public License for more details.
; *
; *  You should have received a copy of the GNU General Public License along
; *  with this program; if not, write to the Free Software Foundation, Inc.,
; *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
; *
; * Change Logs:
; * Date           Author       Notes
; * 2011-08-14     weety      first version
; * 2015-04-15     ArdaFu     Split from AT91SAM9260 BSP
; * 2015-04-21     ArdaFu     Remove remap code. Using mmu to map vector table
; * 2015-06-04     aozima     Align stack address to 8 byte.
; */


S_FRAME_SIZE    EQU     (18*4)   ;72
;S_SPSR          EQU     (17*4)   ;SPSR
;S_CPSR          EQU     (16*4)   ;CPSR
S_PC            EQU     (15*4)   ;R15
;S_LR            EQU     (14*4)   ;R14
;S_SP            EQU     (13*4)   ;R13

;S_IP            EQU     (12*4)   ;R12
;S_FP            EQU     (11*4)   ;R11
;S_R10           EQU     (10*4)
;S_R9            EQU     (9*4)
;S_R8            EQU     (8*4)
;S_R7            EQU     (7*4)
;S_R6            EQU     (6*4)
;S_R5            EQU     (5*4)
;S_R4            EQU     (4*4)
;S_R3            EQU     (3*4)
;S_R2            EQU     (2*4)
;S_R1            EQU     (1*4)
;S_R0            EQU     (0*4)

MODE_USR        EQU     0x10
MODE_FIQ        EQU     0x11
MODE_IRQ        EQU     0x12
MODE_SVC        EQU     0x13
MODE_ABT        EQU     0x17
MODE_UND        EQU     0x1B
MODE_SYS        EQU     0x1F
MODEMASK        EQU     0x1F
I_BIT           EQU     0x80
F_BIT           EQU     0x40

NOINT           EQU     0xC0

UND_STACK_SIZE EQU 0x00000400
SVC_STACK_SIZE EQU  0x00000400
ABT_STACK_SIZE EQU  0x00000400
FIQ_STACK_SIZE EQU  0x00000400
IRQ_STACK_SIZE EQU  0x00000400
SYS_STACK_SIZE EQU  0x00000400
    
;----------------------- Stack and Heap Definitions ----------------------------
    AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem

    SPACE   UND_STACK_SIZE
    EXPORT UND_STACK_START
UND_STACK_START

    ALIGN 8
    SPACE   ABT_STACK_SIZE
    EXPORT ABT_STACK_START
ABT_STACK_START

    ALIGN 8
    SPACE   FIQ_STACK_SIZE
    EXPORT FIQ_STACK_START
FIQ_STACK_START

    ALIGN 8
    SPACE   IRQ_STACK_SIZE
    EXPORT IRQ_STACK_START
IRQ_STACK_START

    ALIGN 8
    SPACE   SYS_STACK_SIZE
    EXPORT SYS_STACK_START
SYS_STACK_START

    ALIGN 8
    SPACE   SVC_STACK_SIZE
    EXPORT SVC_STACK_START
SVC_STACK_START
Stack_Top
__initial_sp

__heap_base
Heap_Mem        SPACE   0x4000
__heap_limit

    PRESERVE8
;--------------Jump vector table------------------------------------------------
    EXPORT Entry_Point
    AREA    RESET, CODE, READONLY
    ARM
Entry_Point
    LDR     PC, vector_reset
    LDR     PC, vector_undef
    LDR     PC, vector_swi
    LDR     PC, vector_pabt
    LDR     PC, vector_dabt
    LDR     PC, vector_resv
    LDR     PC, vector_irq
    LDR     PC, vector_fiq

vector_reset
    DCD     Reset_Handler
vector_undef
    DCD     Undef_Handler
vector_swi
    DCD     SWI_Handler
vector_pabt
    DCD     PAbt_Handler
vector_dabt
    DCD     DAbt_Handler
vector_resv
    DCD     Resv_Handler
vector_irq
    DCD     IRQ_Handler
vector_fiq
    DCD     FIQ_Handler

;----------------- Reset Handler -----------------------------------------------
    IMPORT rt_low_level_init
    IMPORT  __main
    EXPORT  Reset_Handler
Reset_Handler
    ; set the cpu to SVC32 mode
    MRS     R0,CPSR
    BIC     R0,R0,#MODEMASK
    ORR     R0,R0,#MODE_SVC:OR:NOINT
    MSR     CPSR_cxsf,R0
    
    ;init cpu
    BL cpu_init_crit

    ;Copy vector to the correct address

    LDR R0, =Entry_Point
    LDREQ R1, =0x00000000
    LDMIA R0!, {R2-R8, R10}
    STMIA R1!, {R2-R8, R10}
    LDMIA R0!, {R2-R8, R10}
    STMIA R1!, {R2-R8, R10}

    ;turn off the watchdog

    LDR R0, =0x01C20CB8
    MOV     R1, #0x0
    STR     R1, [R0]

    ;mask all IRQs source 

    LDR R1, =0xffffffff
    LDR R0, =0x01C20430
    STR R1, [R0], #0x04
    STR R1, [R0]

    ; Set CO-Processor
    ; little-end，disbale I/D Cache MMU, vector table is 0x00000000
    ;MRC     p15, 0, R0, c1, c0, 0   ; Read CP15
    ;LDR     R1, =0x00003085         ; set clear bits
    ;BIC     R0, R0, R1
    ;MCR     p15, 0, R0, c1, c0, 0   ; Write CP15

    ; Call low level init function,
    ; disable and clear all IRQs, Init MMU, Init interrupt controller, etc.
    LDR     SP, =SVC_STACK_START
    LDR     R0, =rt_low_level_init
    BLX     R0

    BL Setup_Stack

cpu_init_crit
    ;invalidate I/D caches 
    mov r0, #0
    mcr p15, 0, r0, c7, c7, 0
    mcr p15, 0, r0, c8, c7, 0

    ;disable MMU stuff and caches
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #0x00002300
    bic r0, r0, #0x00000087
    orr r0, r0, #0x00000002
    orr r0, r0, #0x00001000
    mcr p15, 0, r0, c1, c0, 0

    bx lr
Setup_Stack
    ; Setup Stack for each mode
    MRS     R0, CPSR
    BIC     R0, R0, #MODEMASK

    ORR     R1, R0, #MODE_UND:OR:NOINT
    MSR     CPSR_cxsf, R1            ; Undef mode
    LDR     SP, =UND_STACK_START

    ORR     R1,R0,#MODE_ABT:OR:NOINT
    MSR     CPSR_cxsf,R1             ; Abort mode
    LDR     SP, =ABT_STACK_START

    ORR     R1,R0,#MODE_IRQ:OR:NOINT
    MSR     CPSR_cxsf,R1             ; IRQ mode
    LDR     SP, =IRQ_STACK_START

    ORR     R1,R0,#MODE_FIQ:OR:NOINT
    MSR     CPSR_cxsf,R1             ; FIQ mode
    LDR     SP, =FIQ_STACK_START

    ORR     R1,R0,#MODE_SYS:OR:NOINT
    MSR     CPSR_cxsf,R1             ; SYS/User mode
    LDR     SP, =SYS_STACK_START

    ORR     R1,R0,#MODE_SVC:OR:NOINT
    MSR     CPSR_cxsf,R1             ; SVC mode
    LDR     SP, =SVC_STACK_START

    ; Enter the C code
    LDR     R0, =__main
    BLX     R0

;----------------- Exception Handler -------------------------------------------
    IMPORT rt_hw_trap_udef
    IMPORT rt_hw_trap_swi
    IMPORT rt_hw_trap_pabt
    IMPORT rt_hw_trap_dabt
    IMPORT rt_hw_trap_resv
    IMPORT rt_hw_trap_irq
    IMPORT rt_hw_trap_fiq

    IMPORT rt_interrupt_enter
    IMPORT rt_interrupt_leave
    IMPORT rt_thread_switch_interrupt_flag
    IMPORT rt_interrupt_from_thread
    IMPORT rt_interrupt_to_thread

Undef_Handler PROC
    SUB     SP, SP, #S_FRAME_SIZE
    STMIA   SP, {R0 - R12}          ; Calling R0-R12
    ADD     R8, SP, #S_PC
    STMDB   R8, {SP, LR}            ; Calling SP, LR
    STR     LR, [R8, #0]            ; Save calling PC
    MRS     R6, SPSR
    STR     R6, [R8, #4]            ; Save CPSR
    STR     R0, [R8, #8]            ; Save SPSR
    MOV     R0, SP
    BL      rt_hw_trap_udef
    ENDP

SWI_Handler PROC
    BL      rt_hw_trap_swi
    ENDP

PAbt_Handler PROC
    BL      rt_hw_trap_pabt
    ENDP

DAbt_Handler PROC
    SUB     SP, SP, #S_FRAME_SIZE
    STMIA   SP, {R0 - R12}          ; Calling R0-R12
    ADD     R8, SP, #S_PC
    STMDB   R8, {SP, LR}            ; Calling SP, LR
    STR     LR, [R8, #0]            ; Save calling PC
    MRS     R6, SPSR
    STR     R6, [R8, #4]            ; Save CPSR
    STR     R0, [R8, #8]            ; Save SPSR
    MOV     R0, SP
    BL      rt_hw_trap_dabt
    ENDP

Resv_Handler PROC
    BL      rt_hw_trap_resv
    ENDP

FIQ_Handler PROC
    STMFD   SP!, {R0-R7,LR}
    BL      rt_hw_trap_fiq
    LDMFD   SP!, {R0-R7,LR}
    SUBS    PC, LR, #4
    ENDP

IRQ_Handler PROC
    STMFD   SP!, {R0-R12,LR}
    BL      rt_interrupt_enter
    BL      rt_hw_trap_irq
    BL      rt_interrupt_leave

    ; If rt_thread_switch_interrupt_flag set,
    ; jump to rt_hw_context_switch_interrupt_do and don't return
    LDR     R0, =rt_thread_switch_interrupt_flag
    LDR     R1, [R0]
    CMP     R1, #1
    BEQ     rt_hw_context_switch_interrupt_do

    LDMFD   SP!, {R0-R12,LR}
    SUBS    PC, LR, #4
    ENDP

;------ void rt_hw_context_switch_interrupt_do(rt_base_t flag) -----------------
rt_hw_context_switch_interrupt_do PROC
    MOV     R1,  #0                 ; Clear flag
    STR     R1,  [R0]               ; Save to flag variable

    LDMFD   SP!, {R0-R12,LR}        ; Reload saved registers
    STMFD   SP, {R0-R2}             ; Save R0-R2
    SUB     R1,  SP, #4*3           ; Save old task's SP to R1
    SUB     R2,  LR, #4             ; Save old task's PC to R2

    MRS     R0,  SPSR               ; Get CPSR of interrupt thread

    MSR     CPSR_c, #MODE_SVC:OR:NOINT  ; Switch to SVC mode and no interrupt

    STMFD   SP!, {R2}               ; Push old task's PC
    STMFD   SP!, {R3-R12,LR}        ; Push old task's LR,R12-R3
    LDMFD   R1, {R1-R3}
    STMFD   SP!, {R1-R3}            ; Push old task's R2-R0
    STMFD   SP!, {R0}               ; Push old task's CPSR

    LDR     R4,  =rt_interrupt_from_thread
    LDR     R5,  [R4]               ; R5 = stack ptr in old tasks's TCB
    STR     SP,  [R5]               ; Store SP in preempted tasks's TCB

    LDR     R6,  =rt_interrupt_to_thread
    LDR     R6,  [R6]               ; R6 = stack ptr in new tasks's TCB
    LDR     SP,  [R6]               ; Get new task's stack pointer

    LDMFD   SP!, {R4}               ; Pop new task's SPSR
    MSR     SPSR_cxsf, R4

    LDMFD   SP!, {R0-R12,LR,PC}^    ; pop new task's R0-R12,LR & PC SPSR to CPSR
    ENDP

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, = Heap_Mem                         ; heap base
                 LDR     R1, = SVC_STACK_START                  ; stack base (top-address)
                 LDR     R2, = (Heap_Mem +  0x4000)          ; heap limit
                 LDR     R3, = (SVC_STACK_START - 0x400) ; stack limit (low-address)
                 BX      LR

                 ALIGN

                 ENDIF

    END
