
huffman.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <encode>:
   0:	e92d4ff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
   4:	e5d03000 	ldrb	r3, [r0]
   8:	e3530000 	cmp	r3, #0
   c:	0a000037 	beq	f0 <encode+0xf0>
  10:	e3a0e000 	mov	lr, #0
  14:	e3002000 	movw	r2, #0
  18:	e1a07000 	mov	r7, r0
  1c:	e1a0400e 	mov	r4, lr
  20:	e1a0c00e 	mov	ip, lr
  24:	e1a0000e 	mov	r0, lr
  28:	e1a0600e 	mov	r6, lr
  2c:	e3a08001 	mov	r8, #1
  30:	e3402000 	movt	r2, #0
  34:	e5929000 	ldr	r9, [r2]
  38:	e0833183 	add	r3, r3, r3, lsl #3
  3c:	e0893003 	add	r3, r9, r3
  40:	e5932004 	ldr	r2, [r3, #4]
  44:	e5935000 	ldr	r5, [r3]
  48:	e5d3b008 	ldrb	fp, [r3, #8]
  4c:	e24ca020 	sub	sl, ip, #32
  50:	e1a02c12 	lsl	r2, r2, ip
  54:	e1822a15 	orr	r2, r2, r5, lsl sl
  58:	e18eec15 	orr	lr, lr, r5, lsl ip
  5c:	e26ca020 	rsb	sl, ip, #32
  60:	e08cc00b 	add	ip, ip, fp
  64:	e1822a35 	orr	r2, r2, r5, lsr sl
  68:	e31c0040 	tst	ip, #64	; 0x40
  6c:	e2865008 	add	r5, r6, #8
  70:	e1824004 	orr	r4, r2, r4
  74:	e081a006 	add	sl, r1, r6
  78:	0a000015 	beq	d4 <encode+0xd4>
  7c:	e781e006 	str	lr, [r1, r6]
  80:	e58a4004 	str	r4, [sl, #4]
  84:	e5d34008 	ldrb	r4, [r3, #8]
  88:	e593e000 	ldr	lr, [r3]
  8c:	e24cc040 	sub	ip, ip, #64	; 0x40
  90:	e044200c 	sub	r2, r4, ip
  94:	e5934004 	ldr	r4, [r3, #4]
  98:	e5f73001 	ldrb	r3, [r7, #1]!
  9c:	e2626020 	rsb	r6, r2, #32
  a0:	e1a0e23e 	lsr	lr, lr, r2
  a4:	e18ee614 	orr	lr, lr, r4, lsl r6
  a8:	e3530000 	cmp	r3, #0
  ac:	e2426020 	sub	r6, r2, #32
  b0:	e18ee634 	orr	lr, lr, r4, lsr r6
  b4:	e081a005 	add	sl, r1, r5
  b8:	e2800002 	add	r0, r0, #2
  bc:	e1a04234 	lsr	r4, r4, r2
  c0:	0a000007 	beq	e4 <encode+0xe4>
  c4:	e1a00008 	mov	r0, r8
  c8:	e1a06188 	lsl	r6, r8, #3
  cc:	e2888001 	add	r8, r8, #1
  d0:	eaffffd8 	b	38 <encode+0x38>
  d4:	e5f73001 	ldrb	r3, [r7, #1]!
  d8:	e3530000 	cmp	r3, #0
  dc:	1affffd5 	bne	38 <encode+0x38>
  e0:	e1a00008 	mov	r0, r8
  e4:	e58ae000 	str	lr, [sl]
  e8:	e58a4004 	str	r4, [sl, #4]
  ec:	e8bd8ff0 	pop	{r4, r5, r6, r7, r8, r9, sl, fp, pc}
  f0:	e1a0e003 	mov	lr, r3
  f4:	e1a0a001 	mov	sl, r1
  f8:	e1a04003 	mov	r4, r3
  fc:	e3a00001 	mov	r0, #1
 100:	eafffff7 	b	e4 <encode+0xe4>

00000104 <decode>:
 104:	e92d4ff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
 108:	e9900484 	ldmib	r0, {r2, r7, sl}
 10c:	e3a09000 	mov	r9, #0
 110:	e3a03001 	mov	r3, #1
 114:	e300c000 	movw	ip, #0
 118:	e1a08009 	mov	r8, r9
 11c:	e24dd014 	sub	sp, sp, #20
 120:	e58d3000 	str	r3, [sp]
 124:	e241b001 	sub	fp, r1, #1
 128:	e340c000 	movt	ip, #0
 12c:	e2611002 	rsb	r1, r1, #2
 130:	e5903000 	ldr	r3, [r0]
 134:	e58d000c 	str	r0, [sp, #12]
 138:	e58d1004 	str	r1, [sp, #4]
 13c:	e58dc008 	str	ip, [sp, #8]
 140:	e59d0008 	ldr	r0, [sp, #8]
 144:	e2031007 	and	r1, r3, #7
 148:	e5900000 	ldr	r0, [r0]
 14c:	e0811181 	add	r1, r1, r1, lsl #3
 150:	e7d0e001 	ldrb	lr, [r0, r1]
 154:	e1a031a3 	lsr	r3, r3, #3
 158:	e0801001 	add	r1, r0, r1
 15c:	e31e0080 	tst	lr, #128	; 0x80
 160:	e591c001 	ldr	ip, [r1, #1]
 164:	e1833e82 	orr	r3, r3, r2, lsl #29
 168:	e5910005 	ldr	r0, [r1, #5]
 16c:	e1a021a2 	lsr	r2, r2, #3
 170:	03a0c03d 	moveq	ip, #61	; 0x3d
 174:	03a01003 	moveq	r1, #3
 178:	0a00000e 	beq	1b8 <decode+0xb4>
 17c:	e3a01003 	mov	r1, #3
 180:	e1a05008 	mov	r5, r8
 184:	e2034001 	and	r4, r3, #1
 188:	e194e005 	orrs	lr, r4, r5
 18c:	e1a060a3 	lsr	r6, r3, #1
 190:	0a000030 	beq	258 <decode+0x154>
 194:	e5d0e000 	ldrb	lr, [r0]
 198:	e1863f82 	orr	r3, r6, r2, lsl #31
 19c:	e31e0080 	tst	lr, #128	; 0x80
 1a0:	e590c001 	ldr	ip, [r0, #1]
 1a4:	e1a020a2 	lsr	r2, r2, #1
 1a8:	e2811001 	add	r1, r1, #1
 1ac:	e5900005 	ldr	r0, [r0, #5]
 1b0:	1afffff2 	bne	180 <decode+0x7c>
 1b4:	e261c040 	rsb	ip, r1, #64	; 0x40
 1b8:	e24c6020 	sub	r6, ip, #32
 1bc:	e1a00c1a 	lsl	r0, sl, ip
 1c0:	e1800617 	orr	r0, r0, r7, lsl r6
 1c4:	e26c6020 	rsb	r6, ip, #32
 1c8:	e1800637 	orr	r0, r0, r7, lsr r6
 1cc:	e0899001 	add	r9, r9, r1
 1d0:	e1802002 	orr	r2, r0, r2
 1d4:	e59d0004 	ldr	r0, [sp, #4]
 1d8:	e3190040 	tst	r9, #64	; 0x40
 1dc:	e080000b 	add	r0, r0, fp
 1e0:	e1833c17 	orr	r3, r3, r7, lsl ip
 1e4:	e5ebe001 	strb	lr, [fp, #1]!
 1e8:	0a000010 	beq	230 <decode+0x12c>
 1ec:	e59d1000 	ldr	r1, [sp]
 1f0:	e59d700c 	ldr	r7, [sp, #12]
 1f4:	e2816001 	add	r6, r1, #1
 1f8:	e087c186 	add	ip, r7, r6, lsl #3
 1fc:	e2591040 	subs	r1, r9, #64	; 0x40
 200:	e59ca004 	ldr	sl, [ip, #4]
 204:	e7977186 	ldr	r7, [r7, r6, lsl #3]
 208:	e58d6000 	str	r6, [sp]
 20c:	12616040 	rsbne	r6, r1, #64	; 0x40
 210:	12469020 	subne	r9, r6, #32
 214:	11a0c61a 	lslne	ip, sl, r6
 218:	118cc917 	orrne	ip, ip, r7, lsl r9
 21c:	12669020 	rsbne	r9, r6, #32
 220:	118cc937 	orrne	ip, ip, r7, lsr r9
 224:	e1a09001 	mov	r9, r1
 228:	11833617 	orrne	r3, r3, r7, lsl r6
 22c:	118c2002 	orrne	r2, ip, r2
 230:	e261c020 	rsb	ip, r1, #32
 234:	e1a07137 	lsr	r7, r7, r1
 238:	e1877c1a 	orr	r7, r7, sl, lsl ip
 23c:	e35e0003 	cmp	lr, #3
 240:	e241c020 	sub	ip, r1, #32
 244:	e1877c3a 	orr	r7, r7, sl, lsr ip
 248:	e1a0a13a 	lsr	sl, sl, r1
 24c:	1affffbb 	bne	140 <decode+0x3c>
 250:	e28dd014 	add	sp, sp, #20
 254:	e8bd8ff0 	pop	{r4, r5, r6, r7, r8, r9, sl, fp, pc}
 258:	e5dce000 	ldrb	lr, [ip]
 25c:	e1863f82 	orr	r3, r6, r2, lsl #31
 260:	e31e0080 	tst	lr, #128	; 0x80
 264:	e1a020a2 	lsr	r2, r2, #1
 268:	e2811001 	add	r1, r1, #1
 26c:	e59c6001 	ldr	r6, [ip, #1]
 270:	e59c0005 	ldr	r0, [ip, #5]
 274:	0affffce 	beq	1b4 <decode+0xb0>
 278:	e1a0c006 	mov	ip, r6
 27c:	eaffffbf 	b	180 <decode+0x7c>
