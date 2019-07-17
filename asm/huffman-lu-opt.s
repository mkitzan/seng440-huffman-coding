    .arch armv7-a
    .eabi_attribute 28, 1
    .eabi_attribute 20, 1
    .eabi_attribute 21, 1
    .eabi_attribute 23, 3
    .eabi_attribute 24, 1
    .eabi_attribute 25, 1
    .eabi_attribute 26, 2
    .eabi_attribute 30, 2
    .eabi_attribute 34, 1
    .eabi_attribute 18, 4
    .file	"huffman.c"
    .text
    .align	2
    .global	encode
    .arch armv7-a
    .syntax unified
    .arm
    .fpu vfpv3-d16
    .type	encode, %function
encode:
    @ args = 0, pretend = 0, frame = 0
    @ frame_needed = 0, uses_anonymous_args = 0
    movw   r2, #:lower16:DICT @ r2 = DICT addr
    push   {r4, r5, r6, r7, r8, r9, lr}
    ldrb   r3, [r0] @ [zero_extendqisi2] load r3 (key) with first char in text
    movt   r2, #:upper16:DICT @ r2 = DICT addr
    mov    r4, r1, lsr #2 @ copy code addr
    mov    r5, #0 @ len = 0
    mov    r6, #0 @ buffer = 0
    ldr    r7, [r2] @ derefence DICT
.L3:
    cmp    r3, #0 @ text[i] == 0
    add    r3, r3, r3, lsl #1 @ turn key into index offset for DICT
    beq    .L4
    add    r3, r7, r3 @ get DICT[key] addr
    ldrh   r8, [r3] @ [unaligned] load DICT[key].code
    ldrb   r9, [r3, #2] @ [zero_extendisi2] load DICT[key].len
    orr	   r6, r6, r8, lsl r5 @ buffer |= DICT[key].code << len
    add    r5, r5, r9 @ len += DICT[key].len
    ldrb   r3, [r0, #1]! @ [zero_extendqisi2] load text[i]
    tst	   r5, #32 @ len & CODE
    strne  r6, [r1], #4 @ code[loc] = buffer, code = code + 1
    subne  r5, r5, #32 @ len -= CODE
    subne  r9, r9, r5 @ DICT[key].len - len 
    lsrne  r6, r8, r9 @ buffer = DICT[key].code >> (DICT[key].len - len)
    b      .L3
.L4:
    str    r6, [r1] @ store fence post buffer
    rsb    r0, r4, r1, lsr #2 @ return text[loc] - text
    pop    {r4, r5, r6, r7, r8, r9, pc}
    .size encode, .-encode
    .align	2
    .global	decode
    .syntax unified
    .arm
    .fpu vfpv3-d16
    .type decode, %function
decode:
    @ args = 0, pretend = 0, frame = 0
    @ frame_needed = 0, uses_anonymous_args = 0
    push  {r4, r5, r6, r7, r8, r9, lr}
    movw  r8, #:lower16:LOOKUP @ r8 is temp var storing LOOKUP addr
    mov   r7, r0 @ r7 = code addr
    mov   ip, #0 @ ip is seen
    ldr   r3, [r0] @ r3 is buffer
    mov   r2, r1 @ r2 = text addr
    mov   r9, r3
    movt  r8, #:upper16:LOOKUP @ r8 is temp var storing LOOKUP addr
.L12:
    and   lr, r9, #7 @ draw = buffer & 7
    ldr   r0, [r8] @ r0 = LOOKUP addr
    add   lr, lr, lr, lsl #2 @ turn draw into index offset for LOOKUP
    add   r0, r0, lr @ get LOOKUP[draw] addr
    lsr   r9, r9, #3 @ buffer >>= 3
    ldrb  r4, [r0, #4] @ load LOOKUP[draw].draw
    ldr   lr, [r0] @ load LOOKUP[draw].table
    and   r4, r4, r9 @ draw &= buffer
    add   lr, lr, r4, lsl #1 @ turn draw into index offset for LOOKUP[draw].table
    ldrb  r6, [lr] @ load table[draw].letter
    ldrb  lr, [lr, #1] @ load table[draw].contrib
    strb  r6, [r2], #1 @ text[loc] = temp@
    lsr   r9, r9, lr @ buffer >>= table[draw].contrib
    add   r0, lr, #3 @ bits = table[draw].contrib + 3
    lsr   r3, r3, ip @ draw = code[pos] >> seen
    rsb   r4, r0, #32 @ CODE - bits
    add   ip, ip, r0 @ seen += bits
    lsl   r3, r3, r4 @ draw << (CODE - bits) 
    tst   ip, #32 @ if(seen & CODE)
    orr   r9, r9, r3, lsr l4 @ buffer |= draw << (CODE - bits)
    beq   .L11
    subs  ip, ip, #32 @ seen -= CODE and if(seen)
    ldrne r3, [r7, #4]! @ if(seen) load code[pos]
    rsbne r4, ip, #32 @ if(seen) CODE - seen
    orrne r9, r9, r3, lsl r4 @ if(seen) buffer |= code[pos] << (CODE - seen)
.L11:
    cmp   r6, #3 @ letter != 0x03
    sub   r0, r2, r1 @ return loc = (text[loc] - text)
    bne   .L12
    pop   {r4, r5, r6, r7, r8, r9, pc}
    .size decode, .-decode
    .comm LOOKUP,4,4
    .comm DICT,4,4
    .ident "GCC: (GNU) 8.2.1 20180801 (Red Hat 8.2.1-2)"
    .section .note.GNU-stack,"",%progbits
