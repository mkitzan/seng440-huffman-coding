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
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, lr}
	mov	r8, r0
	mov	r4, #0
	mov	r9, #1
	ldr	r5, [r0]
	sub	sp, sp, #12
	sub	r7, r1, #1
	rsb	r6, r1, #2
.L12:
	mov	r0, r5
	bl	lookup_unit
	ldr	r2, [r8, r9, lsl #2]
	ubfx	ip, r0, #8, #8
	lsr	r2, r2, r4
	rsb	r1, ip, #32
	add	r4, r4, ip
	uxtb	r3, r0
	lsl	r2, r2, r1
	tst	r4, #32
	orr	r5, r2, r5, lsr ip
	add	r0, r6, r7
	lsl	r2, r9, #2
	strb	r3, [r7, #1]!
	beq	.L11
	subs	r4, r4, #32
	addne	r2, r8, r2
	rsbne	r1, r4, #32
	ldrne	ip, [r2, #4]
	movne	r2, r1
	add	r9, r9, #1
	orrne	r5, r5, ip, lsl r2
.L11:
	cmp	r3, #3
	bne	.L12
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, pc}
	.size	decode, .-decode
	.comm	LOOKUP,4,4
	.comm	DICT,4,4
	.ident	"GCC: (GNU) 8.2.1 20180801 (Red Hat 8.2.1-2)"
	.section	.note.GNU-stack,"",%progbits
