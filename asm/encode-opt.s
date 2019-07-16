encode:
	; args = 0, pretend = 0, frame = 0
	; frame_needed = 0, uses_anonymous_args = 0
	movw r2, #:lower16:DICT ; r2 is temp var storing DICT addr
	push {r4, r5, r6, r7, r8, r9, lr}
	ldrb r3, [r0] ; [zero_extendqisi2] load r3 (key) with first char in text
	movt r2, #:upper16:DICT ; r2 is temp var storing DICT addr
    mov  r4, #0 ; loc = 0
    mov  r5, #0 ; len = 0
    mov  r6, #0 ; buffer = 0
.L3
    cmp  r3, #0 ; text[i] == 0
    ldr  r7, [r2] ; copy DICT addr
    beq  .L4
    add	 r3, r3, r3, lsl #1 ; turn key into offset for DICT
    add  r0, r0, #1 ; text = text + 1
    add  r3, r7, r3 ; get DICT[key] addr
    ldrh r8, [r3] ; load DICT[key].code
	ldrb r9, [r3, #2] ; load DICT[key].len
    orr	 r6, r6, r8, lsl r5 ; buffer |= DICT[key].code << len
    add  r5, r5, r9 ; len += DICT[key].len
    ldrb r3, [r0] ; load text[i]
    tst	 r5, #32 ; len & CODE
    bne  .L3
    str  r6, [r1] ; code[loc] = buffer
    sub  r5, #32 ; len -= CODE
    add  r1, r1, #4 ; code = code + 1
    sub  r9, r5 ; DICT[key].len - len 
    add  r4, r4, #1 ; loc += 1
    asr  r6, r8, r9 ; buffer = DICT[key].code >> (DICT[key].len - len)
    b    .L3
.L4
    str  r6, [r1] ; store fence post buffer
    mov  r0, r4 ; return loc
    pop	 {r4, r5, r6, r7, r8, r9, pc}
