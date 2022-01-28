	.text

	.global sqrt

sqrt:
	push	%ebp
	mov	%esp, %ebp
	movsd	8(%ebp), %xmm0
	sqrtsd	%xmm0, %xmm0
	subl	$8, %esp
	movsd	%xmm0, (%esp)
	fldl	(%esp)
	addl	$8, %esp
	pop	%ebp
	ret

	.global	mul
mul:
	push	%ebp
	mov	%esp, %ebp
	movsd	8(%ebp), %xmm0
	movsd	16(%ebp), %xmm1
	mulsd	%xmm1, %xmm0
	subl	$8, %esp
	movsd	%xmm0, (%esp)
	fldl	(%esp)
	addl	$8, %esp
	pop	%ebp
	ret
