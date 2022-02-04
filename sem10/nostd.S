	.global _start

_start:
	pop	%eax // argc 0x74
	mov	%esp, %ecx  // argv 
	leal	4(%esp, %eax, 4), %edx // envp
	and	$-16, %esp // 0xFFFFFFF0 0x70
	push	%eax
	push	%edx
	push	%ecx
	push	%eax
	call	main
	add	$16, %esp
	mov	$1, %eax
	mov	$0, %ebx
	int	$0x80

main:
	ret
