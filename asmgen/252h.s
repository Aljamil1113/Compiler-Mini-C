	.globl _main

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
fact:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	fact.x, 8
	.equ	fact.t.1, -4
	.equ	fact.t.2, -8
	.equ	fact.t.3, -12
	.equ	fact.t.4, -16
	subl	$24, %esp

	movl	fact.x(%ebp), %eax
	cmpl	$1, %eax
	setl	%cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movl	%eax, fact.t.1(%ebp)

	movl	fact.t.1(%ebp), %eax
	cmpl	$0, %eax
	je	L.1

	movl	$1, %eax

	jmp	L.2
L.1:

	movl	fact.x(%ebp), %eax
	subl	$1, %eax
	movl	%eax, fact.t.2(%ebp)

	movl	fact.t.2(%ebp), %eax
	pushl	%eax

	calll	fact
	movl	%eax, fact.t.3(%ebp)

	movl	fact.t.3(%ebp), %eax
	imul	fact.x(%ebp), %eax
	movl	%eax, fact.t.4(%ebp)

	movl	fact.t.4(%ebp), %eax
L.2:
	addl	$24, %esp
	popl	%ebp
	retl	$4
_main:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	main.x, -4
	.equ	main.y, -8
	.equ	main.t.5, -12
	.equ	main.t.6, -16
	.equ	main.t.7, -20
	subl	$24, %esp

	leal	main.t.5(%ebp), %eax
	calll	input

	movl	main.t.5(%ebp), %eax
	movl	%eax, main.x(%ebp)

	movl	main.x(%ebp), %eax
	pushl	%eax

	calll	fact
	movl	%eax, main.t.6(%ebp)

	movl	main.t.6(%ebp), %eax
	movl	%eax, main.y(%ebp)

	movl	main.y(%ebp), %eax
	pushl	%eax

	popl	%eax
	calll	output
	movl	%eax, main.t.7(%ebp)

	movl	$0, %eax
	addl	$24, %esp
	popl	%ebp
	retl
