.equ STACK_SIZE, 8192

.section .text
.global _entry

_entry:
	li t0, STACK_SIZE
	csrr t1, mhartid
	la sp, stacks

	add sp, sp, t0
	mul t0, t0, t1
	add sp, sp, t0

	bnez t1, spin
	call start

spin:
	wfi
	j spin

stacks:
	.space STACK_SIZE * 4
