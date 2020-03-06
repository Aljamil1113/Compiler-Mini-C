	.globl	_main
	.globl	summation
input: 
	pushl	%ebp
	movl	%esp, %ebp

	subl	$8, %esp
	movl	%eax, 4(%esp)
	leal	fmt.int, %eax
	movl	%eax, (%esp)
	calll	_scanf
	addl	$8, %esp

	popl	%ebp
	retl	
fmt.int: 
	.asciz	"%d"
output: 
	pushl	%ebp
	movl	%esp, %ebp

	subl	$8, %esp
	movl	%eax, 4(%esp)
	leal	fmt.intnl, %eax
	movl	%eax, (%esp)
	calll	_printf
	addl	$8, %esp

	popl	%ebp
	retl	
fmt.intnl: 
	.asciz	"%d\n"
summation:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	summation.x(%ebp), 8
	.equ	summation.t.1(%ebp), -4
	.equ	summation.t.2(%ebp), -8
	.equ	summation.t.3(%ebp), -12
	.equ	summation.t.4(%ebp), -16
	subl	$24, %esp

	movl	summation.x(%ebp), %eax
	cmpl	$0, %eax
	sete	%cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movl	%eax, summation.t.1(%ebp)

	movl	summation.t.1(%ebp), %eax
	cmpl	$0, %eax
	je	L.1

	movl	$0, %eax

	jmp	L.2
L.1:

	movl	summation.x(%ebp), %eax
	subl	$1, %eax
	movl	%eax, summation.t.2(%ebp)

	movl	summation.t.2(%ebp), %eax
	pushl	%eax

	calll	summation
	movl	%eax, summation.t.3(%ebp)

	movl	summation.x(%ebp), %eax
	addl	summation.t.3(%ebp), %eax
	movl	%eax, summation.t.4(%ebp)

	movl	summation.t.4(%ebp), %eax
L.2:
	addl	$24, %esp
	popl	%ebp
	retl	$4
_main:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	main.a(%ebp), -4
	.equ	main.res(%ebp), -8
	.equ	main.t.5(%ebp), -12
	.equ	main.t.6(%ebp), -16
	.equ	main.t.7(%ebp), -20
	subl	$24, %esp

	leal	main.t.5(%ebp), %eax
	calll	input

	movl	main.t.5(%ebp), %eax
	movl	%eax, main.a(%ebp)

	movl	main.a(%ebp), %eax
	pushl	%eax

	calll	summation
	movl	%eax, main.t.6(%ebp)

	movl	main.t.6(%ebp), %eax
	pushl	%eax

	popl	%eax
	calll	output
	movl	%eax, main.t.7(%ebp)
	addl	$24, %esp
	popl	%ebp
	retl	
