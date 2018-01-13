
//  Part of the Raspberry-Pi Bare Metal Tutorials
//  Copyright (c) 2013, Brian Sidebotham
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.

//	Reference: 
//		Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
//		Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
//		Trying Bare Metal on Raspberry Pi 2.
//		www.raspberrypi.org/forums/viewtopic.php?p=701773

// 	Huanle Zhang at UC Davis. www.huanlezhang.com 
//	Last Update: April 26, 2017


.section ".text.startup"

.global _start
//.global _get_stack_pointer
.global _enable_interrupts
.global _disable_interrupts
.global _core_1_main
.global _core_2_main
.global _core_3_main

_start:
    ldr pc, _reset_handler
    ldr pc, _undefined_handler
    ldr pc, _swi_handler
    ldr pc, _prefetch_handler
    ldr pc, _data_handler
    ldr pc, _hyp_handler
    ldr pc, _irq_handler
    ldr pc, _fiq_handler

_reset_handler:	    .word   _reset
_undefined_handler: .word   _undefined_vector
_swi_handler:	    .word   _swi_vector
_prefetch_handler:  .word   _prefetch_vector
_data_handler:	    .word   _data_vector
_hyp_handler:	    .word   _hyp_vector
_irq_handler:	    .word   _irq_vector
_fiq_handler:	    .word   _fiq_vector

_reset:
    mov r0,#0x8000
    MCR p15, 4, r0, c12, c0, 0

    mov sp, #(896 * 1024 * 1024)
    bl _cstartup

_fiq_vector:
    push    {r0,r1,r2,r3,r4,r5,r6,r7,lr}
    bl c_fiq_handler
    pop	    {r0,r1,r2,r3,r4,r5,r6,r7,lr}
    eret
 
_irq_vector:
    push    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    bl c_irq_handler
    pop	    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    eret
 
_hyp_vector:
    push    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    bl c_hyp_handler
    pop	    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    eret
 
_data_vector:
    push    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    bl c_data_handler
    pop	    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    eret
 
_prefetch_vector:
    push    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    bl c_prefetch_handler
    pop	    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    eret
 
_swi_vector:
    push    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    bl c_swi_handler
    pop	    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    eret

_undefined_vector:
    push    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    bl c_undefined_handler
    pop	    {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    eret

_inf_loop:
    b       _inf_loop

_enable_interrupts:
    mrs r0, cpsr
    bic r0, r0, #0xc0
    msr cpsr_c, r0
    bx lr

_disable_interrupts:
    mrs r0, cpsr
    orr r0, r0, #0xc0
    msr cpsr_c, r0
    bx lr

_core_1_main:
    mov sp, #(832 * 1024 * 1024)
    bl core_1_main

_core_2_main:
    mov sp, #(768 * 1024 * 1024)
    bl core_2_main

_core_3_main:
    mov sp, #(704 * 1024 * 1024)
    bl core_3_main


