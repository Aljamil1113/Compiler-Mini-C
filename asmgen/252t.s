	.globl	gcd
	.globl	_main
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
gcd:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	gcd.u(%ebp), 8
	.equ	gcd.v(%ebp), 12
	.equ	gcd.t.1(%ebp), -4
	.equ	gcd.t.2(%ebp), -8
	.equ	gcd.t.3(%ebp), -12
	subl	$8, %esp

	movl	gcd.v(%ebp), %eax
	cmpl	$0, %eax
	sete	%cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movl	%eax, gcd.t.1(%ebp)

	movl	gcd.t.1(%ebp), %eax
	cmpl	$0, %eax
	je	L.1

	movl	gcd.u(%ebp), %eax

	jmp	L.2
L.1:

	movl	gcd.v(%ebp), %eax
	pushl	%eax

	movl	gcd.u(%ebp), %eax
	movl	gcd.v(%ebp), %ebx
	sarl	$31, %edx
	idivl	%ebx
	movl	%edx, gcd.t.2(%ebp)

	movl	gcd.t.2(%ebp), %eax
	pushl	%eax

	calll	gcd
	movl	%eax, gcd.t.3(%ebp)

	movl	gcd.t.3(%ebp), %eax
L.2:
	addl	$8, %esp
	popl	%ebp
	retl	$8
_main:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	main.x(%ebp), -4
	.equ	main.y(%ebp), -8
	.equ	main.t.4(%ebp), -12
	.equ	main.t.5(%ebp), -16
	.equ	main.t.6(%ebp), -20
	.equ	main.t.7(%ebp), -24
	subl	$24, %esp

	leal	main.t.4(%ebp), %eax
	calll	input

	movl	main.t.4(%ebp), %eax
	movl	%eax, main.x(%ebp)

	leal	main.t.5(%ebp), %eax
	calll	input

	movl	main.t.5(%ebp), %eax
	movl	%eax, main.y(%ebp)

	movl	main.x(%ebp), %eax
	pushl	%eax

	movl	main.y(%ebp), %eax
	pushl	%eax

	calll	gcd
	movl	%eax, main.t.6(%ebp)

	movl	main.t.6(%ebp), %eax
	pushl	%eax

	popl	%eax
	calll	output
	movl	%eax, main.t.7(%ebp)

	movl	$0, %eax
	addl	$24, %esp
	popl	%ebp
	retl	
