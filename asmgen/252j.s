	.globl	_main
	.globl	multiply
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
multiply:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	multiply.k(%ebp), 8
	.equ	multiply.x(%ebp), 12
	.equ	multiply.n(%ebp), 16
	.equ	multiply.i(%ebp), -4
	.equ	multiply.t.1(%ebp), -8
	.equ	multiply.t.2(%ebp), -12
	.equ	multiply.t.3(%ebp), -16
	.equ	multiply.t.4(%ebp), -20
	subl	$24, %esp

	movl	$0, %eax
	movl	%eax, multiply.i(%ebp)
L.1:

	movl	multiply.i(%ebp), %eax
	cmpl	multiply.n(%ebp), %eax
	setl	%cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movl	%eax, multiply.t.1(%ebp)

	movl	multiply.t.1(%ebp), %eax
	cmpl	$0, %eax
	je	L.2

	movl	main.multiply.x(%ebp).Aultiply.i(%ebp)(%ebp), %eax
	movl	%eax, multiply.t.2(%ebp)

	movl	multiply.k(%ebp), %eax
	imul	multiply.t.2(%ebp), %eax
	movl	%eax, multiply.t.3(%ebp)

	movl	multiply.t.3(%ebp), %eax
	movl	%eax, main.multiply.x(%ebp).Aultiply.i(%ebp)(%ebp)

	movl	multiply.i(%ebp), %eax
	addl	$1, %eax
	movl	%eax, multiply.t.4(%ebp)

	movl	multiply.t.4(%ebp), %eax
	movl	%eax, multiply.i(%ebp)

	jmp	L.1
L.2:
	addl	$24, %esp
	popl	%ebp
	retl	$12
_main:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	main.x.A0(%ebp), -4
	.equ	main.x.A1(%ebp), -8
	.equ	main.x.A2(%ebp), -12
	.equ	main.x.A3(%ebp), -16
	.equ	main.x.A4(%ebp), -20
	.equ	main.y(%ebp), -24
	.equ	main.t.5(%ebp), -28
	.equ	main.t.6(%ebp), -32
	.equ	main.t.7(%ebp), -36
	.equ	main.t.8(%ebp), -40
	.equ	main.t.9(%ebp), -44
	.equ	main.t.10(%ebp), -48
	.equ	main.t.11(%ebp), -52
	.equ	main.t.12(%ebp), -56
	.equ	main.t.13(%ebp), -60
	.equ	main.t.14(%ebp), -64
	.equ	main.t.15(%ebp), -68
	subl	$72, %esp

	movl	$3, %eax
	movl	%eax, main.x.A0(%ebp)

	movl	main.x.A0(%ebp), %eax
	movl	%eax, main.t.5(%ebp)

	movl	main.t.5(%ebp), %eax
	subl	$5, %eax
	movl	%eax, main.t.6(%ebp)

	movl	main.t.6(%ebp), %eax
	movl	%eax, main.x.A1(%ebp)

	movl	main.x.A1(%ebp), %eax
	movl	%eax, main.t.7(%ebp)

	movl	main.x.A0(%ebp), %eax
	movl	%eax, main.t.8(%ebp)

	movl	main.t.7(%ebp), %eax
	addl	main.t.8(%ebp), %eax
	movl	%eax, main.t.9(%ebp)

	movl	main.t.9(%ebp), %eax
	movl	%eax, main.x.A2(%ebp)

	movl	$10, %eax
	movl	%eax, main.x.A3(%ebp)

	movl	$1, %eax
	negl	%eax
	movl	%eax, main.t.10(%ebp)

	movl	main.t.10(%ebp), %eax
	movl	%eax, main.x.A4(%ebp)

	movl	$3, %eax
	pushl	%eax

	movl	x, %eax
	pushl	%eax

	movl	$5, %eax
	pushl	%eax

	calll	multiply
	movl	%eax, main.t.11(%ebp)

	movl	$0, %eax
	movl	%eax, main.y(%ebp)
L.3:

	movl	main.y(%ebp), %eax
	cmpl	$5, %eax
	setl	%cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movl	%eax, main.t.12(%ebp)

	movl	main.t.12(%ebp), %eax
	cmpl	$0, %eax
	je	L.4

	movl	main.x.Aain.y(%ebp)(%ebp), %eax
	movl	%eax, main.t.13(%ebp)

	movl	main.t.13(%ebp), %eax
	pushl	%eax

	popl	%eax
	calll	output
	movl	%eax, main.t.14(%ebp)

	movl	main.y(%ebp), %eax
	addl	$1, %eax
	movl	%eax, main.t.15(%ebp)

	movl	main.t.15(%ebp), %eax
	movl	%eax, main.y(%ebp)

	jmp	L.3
L.4:

	movl	$0, %eax
	addl	$72, %esp
	popl	%ebp
	retl	
