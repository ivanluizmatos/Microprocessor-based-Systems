.global _start
_start:

.text

	ldr r0, .p_a
	ldr r1, .p_b
	ldr r2, .p_c

	ldr r3, [r2]
	ldr r4, [r0]
	add r4, r4, r3
	str r4, [r0]

	ldr r3, [r2]
	ldr r4, [r1]
	add r4, r4, r3
	str r4, [r1]

.data

	.p_a :
		.global a
		.word 0x00000000

	.p_b :
		.global b
		.word 0x00000004

	.p_c :
		.global c
		.word 0x00000008