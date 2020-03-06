	.globl	_main
	.globl	x
_main:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	main.t.1(%ebp), -4
	.equ	main.t.2(%ebp), -8
	.equ	main.t.3(%ebp), -12
	.equ	main.t.4(%ebp), -16
	.equ	main.t.5(%ebp), -20
	.equ	main.t.6(%ebp), -24
	.equ	main.t.7(%ebp), -28
	subl	$24, %esp
	addl	$24, %esp
	popl	%ebp
	retl	$0

	movl	$5, %eax
	movl	%eax, x

	movl	x, %eax
	subl	$7, %eax
	movl	%eax, main.t.1(%ebp)

	movl	main.t.1(%ebp), %eax
	negl	%eax
	movl	%eax, main.t.2(%ebp)

	movl	main.t.2(%ebp), %eax
	negl	%eax
	movl	%eax, main.t.3(%ebp)

	movl	main.t.3(%ebp), %eax
	negl	%eax
	movl	%eax, main.t.4(%ebp)

	movl	main.t.4(%ebp), %eax
	negl	%eax
	movl	%eax, main.t.5(%ebp)

	movl	main.t.5(%ebp), %eax
	negl	%eax
	movl	%eax, main.t.6(%ebp)

	movl	main.t.6(%ebp), %eax
	negl	%eax
	movl	%eax, main.t.7(%ebp)

	movl	main.t.7(%ebp), %eax
	movl	%eax, x

	movl	$1, %eax
	addl	$24, %esp
	popl	%ebp
	retl	
