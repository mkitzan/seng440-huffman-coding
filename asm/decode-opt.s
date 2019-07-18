decode:
    ; args = 0, pretend = 0, frame = 0
    ; frame_needed = 0, uses_anonymous_args = 0
    push  {r4, r5, r6, r7, r8, r9, lr}
    movw  r8, #:lower16:LOOKUP ; r8 is temp var storing LOOKUP addr
    mov   r5, #0 ; r5 is seen
    ldr   r9, [r0] ; buffer = code[pos]
    ldr   r3, [r0, #4]! ; r3 is code[++pos]
    mov   r2, r1 ; r2 is text addr
    movt  r8, #:upper16:LOOKUP ; r8 is temp var storing LOOKUP addr
.L12:
    and   lr, r9, #7 ; draw = buffer & 7
    ldr   r7, [r8] ; r7 is LOOKUP addr
    add   lr, lr, lr, lsl #2 ; turn draw into index offset for LOOKUP
    add   r7, r7, lr ; get LOOKUP[draw] addr
    lsr   r9, r9, #3 ; buffer >>= 3
    ldrb  r4, [r7, #4] ; load LOOKUP[draw].draw
    ldr   lr, [r7] ; load LOOKUP[draw].table
    and   r4, r4, r9 ; draw &= buffer
    add   lr, lr, r4, lsl #1 ; turn draw into index offset for LOOKUP[draw].table
    ldrb  r6, [lr] ; load table[draw].letter
    ldrb  lr, [lr, #1] ; load table[draw].contrib
    strb  r6, [r1], #1 ; text[loc] = temp;
    lsr   r9, r9, lr ; buffer >>= table[draw].contrib
    add   r7, lr, #3 ; bits = table[draw].contrib + 3
    lsr   r3, r3, r5 ; draw = code[pos] >> seen
    rsb   r4, r7, #32 ; CODE - bits
    add   r5, r5, r7 ; seen += bits
    lsl   r3, r3, r4 ; draw << (CODE - bits) 
    tst   r5, #32 ; if(seen & CODE)
    orr   r9, r9, r3, lsr r4 ; buffer |= draw << (CODE - bits)
    beq   .L11
    subs  r5, r5, #32 ; seen -= CODE and if(seen)
    ldrne r3, [r0, #4]! ; if(seen) load code[++pos]
    rsbne r4, r5, #32 ; if(seen) CODE - seen
    orrne r9, r9, r3, lsl r4 ; if(seen) buffer |= code[pos] << (CODE - seen)
.L11:
    cmp   r6, #3 ; letter != 0x03
    sub   r0, r1, r2 ; return loc = (text[loc] - text)
    bne   .L12
    pop   {r4, r5, r6, r7, r8, r9, pc}
