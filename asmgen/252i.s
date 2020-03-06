	.globl	count
	.globl	_main
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
count:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	count.x(%ebp), 8
	.equ	count.i(%ebp), -4
	.equ	count.t.1(%ebp), -8
	.equ	count.t.2(%ebp), -12
	.equ	count.t.3(%ebp), -16
	.equ	count.t.4(%ebp), -20
	subl	$24, %esp

	movl	$0, %eax
	movl	%eax, count.i(%ebp)
L.1:

	movl	main.count.x(%ebp).Aount.i(%ebp)(%ebp), %eax
	movl	%eax, count.t.1(%ebp)

	movl	$1, %eax
	negl	%eax
	movl	%eax, count.t.2(%ebp)

	movl	count.t.1(%ebp), %eax
	cmpl	count.t.2(%ebp), %eax
	setne	%cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movl	%eax, count.t.3(%ebp)

	movl	count.t.3(%ebp), %eax
	cmpl	$0, %eax
	je	L.2

	movl	count.i(%ebp), %eax
	addl	$1, %eax
	movl	%eax, count.t.4(%ebp)

	movl	count.t.4(%ebp), %eax
	movl	%eax, count.i(%ebp)

	jmp	L.1
L.2:

	movl	count.i(%ebp), %eax
	addl	$24, %esp
	popl	%ebp
	retl	$4
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
	subl	$56, %esp

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

	movl	x, %eax
	pushl	%eax

	calll	count
	movl	%eax, main.t.11(%ebp)

	movl	main.t.11(%ebp), %eax
	movl	%eax, main.y(%ebp)

	movl	main.y(%ebp), %eax
	pushl	%eax

	popl	%eax
	calll	output
	movl	%eax, main.t.12(%ebp)

	movl	$0, %eax
	addl	$56, %esp
	popl	%ebp
	retl	
