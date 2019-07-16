encode:
    ; args = 0, pretend = 0, frame = 0
    ; frame_needed = 0, uses_anonymous_args = 0
    movw   r2, #:lower16:DICT ; r2 = DICT addr
    push   {r4, r5, r6, r7, r8, r9, lr}
    ldrb   r3, [r0] ; [zero_extendqisi2] load r3 (key) with first char in text
    movt   r2, #:upper16:DICT ; r2 = DICT addr
    mov    r4, r1 ; loc = 0
    mov    r5, #0 ; len = 0
    mov    r6, #0 ; buffer = 0
.L3
    cmp    r3, #0 ; text[i] == 0
    add	   r3, r3, r3, lsl #1 ; turn key into index offset for DICT
    beq    .L4
    add    r3, r2, r3 ; get DICT[key] addr
    add    r0, r0, #1 ; text = text + 1
    ldrh   r8, [r3] ; load DICT[key].code
    ldrb   r9, [r3, #2] ; load DICT[key].len
    orr	   r6, r6, r8, lsl r5 ; buffer |= DICT[key].code << len
    add    r5, r5, r9 ; len += DICT[key].len
    ldrb   r3, [r0] ; load text[i]
    tst	   r5, #32 ; len & CODE
    streq  r6, [r1], #4 ; code[loc] = buffer, code = code + 1
    subeq  r5, #32 ; len -= CODE
    subeq  r9, r5 ; DICT[key].len - len 
    lsreq  r6, r8, r9 ; buffer = DICT[key].code >> (DICT[key].len - len)
    b      .L3
.L4
    str    r6, [r1], #1 ; store fence post buffer
    sub    r0, r1, r4 ; return text[loc] - text
    pop    {r4, r5, r6, r7, r8, r9, pc}
