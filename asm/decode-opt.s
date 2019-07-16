decode:
    ; args = 0, pretend = 0, frame = 0
    ; frame_needed = 0, uses_anonymous_args = 0
    push  {r4, r5, r6, r7, r8, r9, lr}
    movw  r8, #:lower16:LOOKUP ; r8 is temp var storing LOOKUP addr
    mov   r7, r0 ; r7 = code addr
    mov   ip, #0 ; ip is seen
    ldr   r3, [r0] ; r3 is buffer
    mov   r2, r1 ; r2 = text addr
    movt  r8, #:upper16:LOOKUP ; r8 is temp var storing LOOKUP addr
.L12:
    and   lr, r3, #7 ; draw = buffer & 7
    mov   r0, r8 ; r0 = LOOKUP addr
    add   lr, lr, lr, lsl #2 ; turn draw into index offset for LOOKUP
    add   r0, r0, lr ; get LOOKUP[draw] addr
    lsr   r9, r3, #3 ; buffer >>= 3
    ldrb  r4, [r0, #4] ; load LOOKUP[draw].draw
    ldr   lr, [r0] ; load LOOKUP[draw].table
    and   r4, r4, r9 ; draw &= buffer
    add   lr, lr, r4, lsl #1 ; turn draw into index offset for LOOKUP[draw].table
    ldrb  r6, [lr] ; load table[draw].letter
    ldrb  lr, [lr, #1] ; load table[draw].contrib
    strb  r6, [r2], #1 ; text[loc] = temp;
    ldr	  r3, [r7, #4]! ; load code[pos]
    add	  r0, lr, #3 ; bits = table[draw].contrib + 3
    lsr   r3, r3, ip ; draw = code[pos] >> seen
    rsb   r4, r0, #32 ; CODE - bits
    add   ip, ip, r0 ; seen += bits
    lsl   r3, r3, r4 ; draw << (CODE - bits) 
    tst   ip, #32 ; if(seen & CODE)
    orr   r3, r3, r9, lsr lr ; buffer |= draw << (CODE - bits)
    beq   .L11
    subs  ip, ip, #32 ; seen -= CODE and if(seen)
    rsbne r4, ip, #32 ; if(seen) CODE - seen
    ldrne r9, [lr, #4]! ; if(seen) load code[pos]
    orrne r3, r3, r9, lsl r4 ; if(seen) buffer |= code[pos] << (CODE - seen)
.L11:
    cmp   r6, #3 ; letter != 0x03
    sub   r0, r2, r1 ; return loc = (text[loc] - text)
    bne   .L12
    pop   {r4, r5, r6, r7, r8, r9, pc}
