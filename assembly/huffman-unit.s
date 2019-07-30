decode:
	; args = 0, pretend = 0, frame = 8
	; frame_needed = 0, uses_anonymous_args = 0
	push  {r4, r5, r6, r7, r8, r9, lr}
	mov   r8, r0 ; copy of output argument
    mov   r2, r1 ; copy of input argument
	ldr   r9, [r8, #4]! ; r9 is code[pos]
	ldr   r5, [r0] ; r5 is buffer
	mov   r4, #0 ; r4 is seen 
	mov   r0, r5 ; set up functional unit argument
	sub   sp, sp, #12
.L12:
	bl    lookup_unit ; utilize functional unit
	ubfx  ip, r0, #8, #8 ; isolate entry.contrib
	lsr   r3, r9, r4 ; code[pos] >> seen
	rsb   r6, ip, #32 ; (CODE - entry.contrib)
	add   r4, r4, ip ; seen += entry.contrib
	uxtb  r7, r0 ; isolate entry.letter
	lsl   r3, r3, r6 ; temp << (CODE - entry.contrib)
	tst   r4, #32 ; if(seen & CODE)
	orr   r5, r3, r5, lsr ip ; buffer |= temp << (CODE - entry.contrib)
	strb  r7, [r1], #1 ; text[loc++] = entry.letter
	beq   .L11
	subs  r4, r4, #32 ; seen -= CODE
    ldr   r9, [r8, #4]! ; load new code[pos]
	rsbne r3, r4, #32 ; (CODE - seen)
	orrne r5, r5, r9, lsl r3 ; buffer |= code[pos] << (CODE - seen)
.L11:
	cmp   r7, #3 ; while(entry.letter != 0x03)
    mov   r0, r5 ; set up functional unit argument
	bne   .L12
	add   sp, sp, #12
	; sp needed
    sub   r0, r1, r2 ; set up return value
	pop   {r4, r5, r6, r7, r8, r9, pc}