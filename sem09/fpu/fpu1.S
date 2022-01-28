	.text

	.global sqrt
sqrt:
	push	%ebp
	mov	%esp, %ebp
	fldl	8(%ebp)
	fsqrt
	pop	%ebp
	ret

	.global	mul

mul:
	push	%ebp
	mov	%esp, %ebp
	fldt	8(%ebp)  // %st(1)
	fldt	20(%ebp) // %st(0)
	fmul	%st(1), %st
	pop	%ebp
	ret
