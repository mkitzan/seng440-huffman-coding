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
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L6
	mov	lr, #0
	movw	r2, #:lower16:DICT
	mov	r7, r0
	mov	r4, lr
	mov	ip, lr
	mov	r0, lr
	mov	r6, lr
	mov	r8, #1
	movt	r2, #:upper16:DICT
	ldr	r9, [r2]
.L3:
	add	r3, r3, r3, lsl #3
	add	r3, r9, r3
	ldr	r2, [r3, #4]	@ unaligned
	ldr	r5, [r3]	@ unaligned
	ldrb	fp, [r3, #8]	@ zero_extendqisi2
	sub	r10, ip, #32
	lsl	r2, r2, ip
	orr	r2, r2, r5, lsl r10
	orr	lr, lr, r5, lsl ip
	rsb	r10, ip, #32
	add	ip, ip, fp
	orr	r2, r2, r5, lsr r10
	tst	ip, #64
	add	r5, r6, #8
	orr	r4, r2, r4
	add	r10, r1, r6
	beq	.L4
	str	lr, [r1, r6]
	str	r4, [r10, #4]
	ldrb	r4, [r3, #8]	@ zero_extendqisi2
	ldr	lr, [r3]	@ unaligned
	sub	ip, ip, #64
	sub	r2, r4, ip
	ldr	r4, [r3, #4]	@ unaligned
	ldrb	r3, [r7, #1]!	@ zero_extendqisi2
	rsb	r6, r2, #32
	lsr	lr, lr, r2
	orr	lr, lr, r4, lsl r6
	cmp	r3, #0
	sub	r6, r2, #32
	orr	lr, lr, r4, lsr r6
	add	r10, r1, r5
	add	r0, r0, #2
	lsr	r4, r4, r2
	beq	.L2
	mov	r0, r8
	lsl	r6, r8, #3
	add	r8, r8, #1
	b	.L3
.L4:
	ldrb	r3, [r7, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3
	mov	r0, r8
.L2:
	str	lr, [r10]
	str	r4, [r10, #4]
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L6:
	mov	lr, r3
	mov	r10, r1
	mov	r4, r3
	mov	r0, #1
	b	.L2
	.size	encode, .-encode
	.align	2
	.global	decode
	.syntax unified
	.arm
	.fpu vfpv3-d16
	.type	decode, %function
decode:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	ldmib	r0, {r2, r7, r10}
	mov	r9, #0
	mov	r3, #1
	movw	ip, #:lower16:TREE
	mov	r8, r9
	sub	sp, sp, #20
	str	r3, [sp]
	sub	fp, r1, #1
	movt	ip, #:upper16:TREE
	rsb	r1, r1, #2
	ldr	r3, [r0]
	str	r0, [sp, #12]
	str	r1, [sp, #4]
	str	ip, [sp, #8]
.L17:
	ldr	r0, [sp, #8]
	and	r1, r3, #7
	ldr	r0, [r0]
	add	r1, r1, r1, lsl #3
	ldrb	lr, [r0, r1]	@ zero_extendqisi2
	lsr	r3, r3, #3
	add	r1, r0, r1
	tst	lr, #128
	ldr	ip, [r1, #1]	@ unaligned
	orr	r3, r3, r2, lsl #29
	ldr	r0, [r1, #5]	@ unaligned
	lsr	r2, r2, #3
	moveq	ip, #61
	moveq	r1, #3
	beq	.L12
	mov	r1, #3
.L11:
	mov	r5, r8
	and	r4, r3, #1
	orrs	lr, r4, r5
	lsr	r6, r3, #1
	beq	.L13
	ldrb	lr, [r0]	@ zero_extendqisi2
	orr	r3, r6, r2, lsl #31
	tst	lr, #128
	ldr	ip, [r0, #1]	@ unaligned
	lsr	r2, r2, #1
	add	r1, r1, #1
	ldr	r0, [r0, #5]	@ unaligned
	bne	.L11
.L15:
	rsb	ip, r1, #64
.L12:
	sub	r6, ip, #32
	lsl	r0, r10, ip
	orr	r0, r0, r7, lsl r6
	rsb	r6, ip, #32
	orr	r0, r0, r7, lsr r6
	add	r9, r9, r1
	orr	r2, r0, r2
	ldr	r0, [sp, #4]
	tst	r9, #64
	add	r0, r0, fp
	orr	r3, r3, r7, lsl ip
	strb	lr, [fp, #1]!
	beq	.L16
	ldr	r1, [sp]
	ldr	r7, [sp, #12]
	add	r6, r1, #1
	add	ip, r7, r6, lsl #3
	subs	r1, r9, #64
	ldr	r10, [ip, #4]
	ldr	r7, [r7, r6, lsl #3]
	str	r6, [sp]
	rsbne	r6, r1, #64
	subne	r9, r6, #32
	lslne	ip, r10, r6
	orrne	ip, ip, r7, lsl r9
	rsbne	r9, r6, #32
	orrne	ip, ip, r7, lsr r9
	mov	r9, r1
	orrne	r3, r3, r7, lsl r6
	orrne	r2, ip, r2
.L16:
	rsb	ip, r1, #32
	lsr	r7, r7, r1
	orr	r7, r7, r10, lsl ip
	cmp	lr, #3
	sub	ip, r1, #32
	orr	r7, r7, r10, lsr ip
	lsr	r10, r10, r1
	bne	.L17
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L13:
	ldrb	lr, [ip]	@ zero_extendqisi2
	orr	r3, r6, r2, lsl #31
	tst	lr, #128
	lsr	r2, r2, #1
	add	r1, r1, #1
	ldr	r6, [ip, #1]	@ unaligned
	ldr	r0, [ip, #5]	@ unaligned
	beq	.L15
	mov	ip, r6
	b	.L11
	.size	decode, .-decode
	.comm	TREE,4,4
	.comm	DICT,4,4
	.ident	"GCC: (GNU) 8.2.1 20180801 (Red Hat 8.2.1-2)"
	.section	.note.GNU-stack,"",%progbits
