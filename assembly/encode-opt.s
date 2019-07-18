encode:
    ; args = 0, pretend = 0, frame = 0
    ; frame_needed = 0, uses_anonymous_args = 0
    movw  r2, #:lower16:DICT ; r2 = DICT addr
    push  {r4, r5, r6, r7, r8, r9, lr}
    ldrb  r3, [r0] ; [zero_extendqisi2] load r3 (key) with first char in text
    movt  r2, #:upper16:DICT ; r2 = DICT addr
    cmp   r3, #0 ; text[i] == 0
    mov   r4, r1, lsr #2 ; copy code addr
    mov   r6, #0 ; buffer = 0
    beq   .L4
    ldr   r7, [r2] ; deference DICT
    add   r3, r3, r3, lsl #1 ; turn key into index offset for DICT
    mov   r5, #0 ; len = 0
    add   r3, r7, r3 ; get DICT[key] addr
.L3:
    ldrh  r8, [r3] ; [unaligned] load DICT[key].code
    ldrb  r9, [r3, #2] ; [zero_extendisi2] load DICT[key].len
    orr	  r6, r6, r8, lsl r5 ; buffer |= DICT[key].code << len
    add   r5, r5, r9 ; len += DICT[key].len
    ldrb  r3, [r0, #1]! ; [zero_extendqisi2] load text[i]
    tst	  r5, #32 ; len & CODE
    subne r5, r5, #32 ; len -= CODE
    strne r6, [r1], #4 ; code[loc] = buffer, code = code + 1
    subne r9, r9, r5 ; DICT[key].len - len 
    lsrne r6, r8, r9 ; buffer = DICT[key].code >> (DICT[key].len - len)
    cmp   r3, #0 ; text[i] == 0
    add   r3, r3, r3, lsl #1 ; turn key into index offset for DICT
    add   r3, r7, r3 ; get DICT[key] addr
    bne   .L3
.L4:
    str   r6, [r1], #4 ; store fence post buffer
    rsb   r0, r4, r1, lsr #2 ; return text[loc] - text
    pop   {r4, r5, r6, r7, r8, r9, pc}
