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
	movw	r2, #:lower16:DICT
	push	{r4, r5, r6, r7, r8, r9, lr}
	ldrb	r3, [r0]	@ zero_extendqisi2
	movt	r2, #:upper16:DICT
	cmp	r3, #0
	ldr	r9, [r2]
	beq	.L6
	mov	lr, #0
	mov	r6, r0
	mov	r2, lr
	mov	r8, lr
	mov	r7, r1
	mov	r4, #1
.L3:
	add	r3, r3, r3, lsl #1
	add	r3, r9, r3
	ldrh	r5, [r3]	@ unaligned
	ldrb	ip, [r3, #2]	@ zero_extendqisi2
	orr	lr, lr, r5, lsl r2
	add	r2, r2, ip
	tst	r2, #32
	ldrb	r3, [r6, #1]!	@ zero_extendqisi2
	beq	.L4
	sub	r2, r2, #32
	sub	ip, ip, r2
	cmp	r3, #0
	str	lr, [r7]
	add	r0, r4, #1
	asr	lr, r5, ip
	add	r7, r1, r4, lsl #2
	beq	.L2
	mov	r8, r4
	mov	r4, r0
	b	.L3
.L4:
	cmp	r3, #0
	add	r7, r1, r8, lsl #2
	add	r4, r8, #1
	bne	.L3
	mov	r0, r4
.L2:
	str	lr, [r7]
	pop	{r4, r5, r6, r7, r8, r9, pc}
.L6:
	mov	r7, r1
	mov	lr, r3
	mov	r0, #1
	str	lr, [r7]
	pop	{r4, r5, r6, r7, r8, r9, pc}
	.size	encode, .-encode
	.align	2
	.global	decode
	.syntax unified
	.arm
	.fpu vfpv3-d16
	.type	decode, %function
decode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	r3, #:lower16:LOOKUP
	push	{r4, r5, r6, r7, r8, r9, lr}
	mov	ip, #0
	mov	r4, #1
	movt	r3, #:upper16:LOOKUP
	ldr	r5, [r3]
	ldr	r3, [r0]
	sub	lr, r1, #1
	rsb	r1, r1, #2
.L12:
	and	r2, r3, #7
	add	r2, r2, r2, lsl #2
	add	r2, r5, r2
	ldrb	r6, [r2, #4]	@ zero_extendqisi2
	ldr	r9, [r2]	@ unaligned
	lsr	r7, r3, #3
	and	r2, r6, r7
	add	r3, r9, r2, lsl #1
	ldrb	r6, [r3, #1]	@ zero_extendqisi2
	ldr	r3, [r0, r4, lsl #2]
	add	r8, r6, #3
	ldrb	r2, [r9, r2, lsl #1]	@ zero_extendqisi2
	lsr	r3, r3, ip
	rsb	r9, r8, #32
	add	ip, ip, r8
	lsl	r3, r3, r9
	tst	ip, #32
	orr	r3, r3, r7, lsr r6
	add	r7, r1, lr
	lsl	r6, r4, #2
	strb	r2, [lr, #1]!
	beq	.L11
	subs	ip, ip, #32
	addne	r6, r0, r6
	rsbne	r8, ip, #32
	ldrne	r9, [r6, #4]
	movne	r6, r8
	add	r4, r4, #1
	orrne	r3, r3, r9, lsl r6
.L11:
	cmp	r2, #3
	bne	.L12
	mov	r0, r7
	pop	{r4, r5, r6, r7, r8, r9, pc}
	.size	decode, .-decode
	.comm	LOOKUP,4,4
	.comm	DICT,4,4
	.ident	"GCC: (GNU) 8.2.1 20180801 (Red Hat 8.2.1-2)"
	.section	.note.GNU-stack,"",%progbits
