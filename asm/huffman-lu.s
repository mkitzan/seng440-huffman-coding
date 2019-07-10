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
	beq	.L4
	str	lr, [r7]
	ldrb	r3, [r6, #1]!	@ zero_extendqisi2
	sub	r2, r2, #32
	sub	ip, ip, r2
	cmp	r3, #0
	asr	lr, r5, ip
	add	r7, r1, r4, lsl #2
	add	r0, r4, #1
	beq	.L2
	mov	r8, r4
	mov	r4, r0
	b	.L3
.L4:
	ldrb	r3, [r6, #1]!	@ zero_extendqisi2
	add	r7, r1, r8, lsl #2
	cmp	r3, #0
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
	push	{r4, r5, r6, r7, r8, r9, lr}
	movw	r8, #:lower16:LOOKUP
	mov	r7, r0
	mov	ip, #0
	mov	r5, #1
	ldr	r3, [r0]
	sub	r2, r1, #1
	movt	r8, #:upper16:LOOKUP
.L12:
	and	lr, r3, #7
	ldr	r0, [r8]
	add	lr, lr, lr, lsl #2
	add	r0, r0, lr
	ldrb	r4, [r0, #4]	@ zero_extendqisi2
	ldr	lr, [r0]	@ unaligned
	lsr	r9, r3, #3
	and	r4, r4, r9
	ldrb	r6, [lr, r4, lsl #1]	@ zero_extendqisi2
	add	lr, lr, r4, lsl #1
	ldrb	lr, [lr, #1]	@ zero_extendqisi2
	strb	r6, [r2, #1]
	ldr	r3, [r7, r5, lsl #2]
	add	r0, lr, #3
	lsr	r3, r3, ip
	rsb	r4, r0, #32
	add	ip, ip, r0
	lsl	r3, r3, r4
	tst	ip, #32
	add	r0, r2, #2
	orr	r3, r3, r9, lsr lr
	add	r2, r2, #1
	lsl	lr, r5, #2
	beq	.L11
	subs	ip, ip, #32
	addne	lr, r7, lr
	rsbne	r4, ip, #32
	ldrne	r9, [lr, #4]
	movne	lr, r4
	add	r5, r5, #1
	orrne	r3, r3, r9, lsl lr
.L11:
	cmp	r6, #3
	sub	r0, r0, r1
	bne	.L12
	pop	{r4, r5, r6, r7, r8, r9, pc}
	.size	decode, .-decode
	.comm	LOOKUP,4,4
	.comm	DICT,4,4
	.ident	"GCC: (GNU) 8.2.1 20180801 (Red Hat 8.2.1-2)"
	.section	.note.GNU-stack,"",%progbits
