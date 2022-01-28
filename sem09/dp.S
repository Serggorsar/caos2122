	.global	dp
dp:
	push	%ebp
	mov	%esp, %ebp
	mov	8(%ebp), %eax // n
	mov	12(%ebp), %ecx // a
	mov	16(%ebp), %edx // b
	xorpd	%xmm0, %xmm0 // ans
loop:
	cmp	$2, %eax
	jl	last_digit
	movupd	(%ecx), %xmm1 // a[2i], a[2i+1]
	movupd	(%edx), %xmm2 // b[2i], b[2i+1]
	mulpd	%xmm2, %xmm1
	addpd	%xmm1, %xmm0
	subl	$2, %eax //n-=2
	add	$16, %ecx
	add	$16, %edx
	jmp	loop
last_digit:
	haddpd	%xmm0, %xmm0
	cmpl	$1, %eax
	jne	end

	movsd	(%ecx), %xmm1
	movsd	(%edx), %xmm2
	mulsd	%xmm2, %xmm1
	addsd	%xmm1, %xmm0

end:
	subl	$8, %esp
	movsd	%xmm0, (%esp)
	fldl	(%esp)
	add	$8, %esp

	mov	%ebp, %esp
	popl	%ebp
	ret
