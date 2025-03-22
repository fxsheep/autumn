.section vectors

.global rv_start
rv_start:
    ldr pc, .Lreset_handler
    ldr pc, .Lundef_handler
    ldr pc, .Lswi_handler
    ldr pc, .Lprefetch_abort_handler
    ldr pc, .Ldata_abort_handler
    ldr pc, .Lreserved_handler
    ldr pc, .Lirq_handler
    ldr pc, .Lfiq_handler

.Lreset_handler:
    .long reset_handler
.Lundef_handler:
    .long undef_handler
.Lswi_handler:
    .long swi_handler
.Lprefetch_abort_handler:
    .long prefetch_abort_handler
.Ldata_abort_handler:
    .long data_abort_handler
.Lreserved_handler:
    .long reserved_handler
.Lirq_handler:
    .long irq_handler
.Lfiq_handler:
    .long fiq_handler

reset_handler:
    ldr r0, =0xE0003FFC  // Set stack to top of SRAM
    mov sp, r0
    mov r2, #0x0
    ldr r1, =0xE0000000  // Start of stack initialization

clear_stack:
    cmp r1, r0
    str r2, [r0]
    sub r0, r0, #4
    bcc clear_stack

    // Copy data section from ROM to SRAM
    ldr r0, =_sdata  // SRAM start
    ldr r1, =_eronly // ROM start (data section in ROM)
    ldr r2, =_edata  // SRAM end

copy_data:
    cmp r0, r2
    ldrcc r3, [r1], #4
    strcc r3, [r0], #4
    bcc copy_data

    // Zero-initialize .bss
    ldr r0, =_sbss
    ldr r1, =_ebss

clear_bss:
    cmp r0, r1
    movcc r2, #0
    strcc r2, [r0], #4
    addcc r0, r0, #4
    bcc clear_bss

    // Jump to main
    ldr r0, =main
    mov pc, r0
