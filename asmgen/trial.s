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
_main:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	main.a.A0, -4
	.equ	main.a.A1, -8
	.equ	main.t.1, -12
	.equ	main.t.2, -16
	.equ	main.t.3, -20
	subl	$24, %esp

	leal	main.t.1(%ebp), %eax
	calll	input

	movl	main.t.1(%ebp), %eax
	movl	%eax, main.a.A0(%ebp)

	movl	main.a.A0(%ebp), %eax
	movl	%eax, main.t.2(%ebp)

	movl	main.t.2(%ebp), %eax
	pushl	%eax

	popl	%eax
	calll	output
	movl	%eax, main.t.3(%ebp)
	addl	$24, %esp
	popl	%ebp
	retl