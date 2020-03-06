	.globl	_main
	.globl	minloc
	.globl	sort
	.globl	x
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
minloc:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	minloc.a(%ebp), 8
	.equ	minloc.low(%ebp), 12
	.equ	minloc.high(%ebp), 16
	.equ	minloc.i(%ebp), -4
	.equ	minloc.x(%ebp), -8
	.equ	minloc.k(%ebp), -12
	.equ	minloc.t.1(%ebp), -16
	.equ	minloc.t.2(%ebp), -20
	.equ	minloc.t.3(%ebp), -24
	.equ	minloc.t.4(%ebp), -28
	.equ	minloc.t.5(%ebp), -32
	.equ	minloc.t.6(%ebp), -36
	.equ	minloc.t.7(%ebp), -40
	subl	$40, %esp
	addl	$40, %esp
	popl	%ebp
	retl	$12

	movl	minloc.low(%ebp), %eax
	movl	%eax, minloc.k(%ebp)

	movl	main.minloc.a(%ebp).Ainloc.low(%ebp)(%ebp), %eax
	movl	%eax, minloc.t.1(%ebp)

	movl	minloc.t.1(%ebp), %eax
	movl	%eax, minloc.x(%ebp)

	movl	minloc.low(%ebp), %eax
	addl	$1, %eax
	movl	%eax, minloc.t.2(%ebp)

	movl	minloc.t.2(%ebp), %eax
	movl	%eax, minloc.i(%ebp)
L.1:

	movl	minloc.i(%ebp), %eax
	cmpl	minloc.high(%ebp), %eax
	setl	%cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movl	%eax, minloc.t.3(%ebp)

	movl	minloc.t.3(%ebp), %eax
	cmpl	$0, %eax
	je	L.2

	movl	main.minloc.a(%ebp).Ainloc.i(%ebp)(%ebp), %eax
	movl	%eax, minloc.t.4(%ebp)

	movl	minloc.t.4(%ebp), %eax
	cmpl	minloc.x(%ebp), %eax
	setl	%cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movl	%eax, minloc.t.5(%ebp)

	movl	minloc.t.5(%ebp), %eax
	cmpl	$0, %eax
	je	L.3

	movl	main.minloc.a(%ebp).Ainloc.i(%ebp)(%ebp), %eax
	movl	%eax, minloc.t.6(%ebp)

	movl	minloc.t.6(%ebp), %eax
	movl	%eax, minloc.x(%ebp)

	movl	minloc.i(%ebp), %eax
	movl	%eax, minloc.k(%ebp)
L.3:

	movl	minloc.i(%ebp), %eax
	addl	$1, %eax
	movl	%eax, minloc.t.7(%ebp)

	movl	minloc.t.7(%ebp), %eax
	movl	%eax, minloc.i(%ebp)

	jmp	L.1
L.2:

	movl	minloc.k(%ebp), %eax
	addl	$40, %esp
	popl	%ebp
	retl	$12
sort:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	sort.a(%ebp), 8
	.equ	sort.low(%ebp), 12
	.equ	sort.high(%ebp), 16
	.equ	sort.i(%ebp), -4
	.equ	sort.k(%ebp), -8
	.equ	sort.t.8(%ebp), -12
	.equ	sort.t.9(%ebp), -16
	.equ	sort.t(%ebp), -20
	.equ	sort.t.10(%ebp), -24
	.equ	sort.t.11(%ebp), -28
	.equ	sort.t.12(%ebp), -32
	.equ	sort.t.13(%ebp), -36
	subl	$40, %esp

	movl	sort.low(%ebp), %eax
	movl	%eax, sort.i(%ebp)
L.4:

	movl	sort.high(%ebp), %eax
	subl	$1, %eax
	movl	%eax, sort.t.8(%ebp)

	movl	sort.i(%ebp), %eax
	cmpl	sort.t.8(%ebp), %eax
	setl	%cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movl	%eax, sort.t.9(%ebp)

	movl	sort.t.9(%ebp), %eax
	cmpl	$0, %eax
	je	L.5

	movl	sort.a(%ebp), %eax
	pushl	%eax

	movl	sort.i(%ebp), %eax
	pushl	%eax

	movl	sort.high(%ebp), %eax
	pushl	%eax

	calll	minloc
	movl	%eax, sort.t.10(%ebp)

	movl	sort.t.10(%ebp), %eax
	movl	%eax, sort.k(%ebp)

	movl	main.sort.a(%ebp).Aort.k(%ebp)(%ebp), %eax
	movl	%eax, sort.t.11(%ebp)

	movl	sort.t.11(%ebp), %eax
	movl	%eax, sort.t(%ebp)

	movl	main.sort.a(%ebp).Aort.i(%ebp)(%ebp), %eax
	movl	%eax, sort.t.12(%ebp)

	movl	sort.t.12(%ebp), %eax
	movl	%eax, main.sort.a(%ebp).Aort.k(%ebp)(%ebp)

	movl	sort.t(%ebp), %eax
	movl	%eax, main.sort.a(%ebp).Aort.i(%ebp)(%ebp)

	movl	sort.i(%ebp), %eax
	addl	$1, %eax
	movl	%eax, sort.t.13(%ebp)

	movl	sort.t.13(%ebp), %eax
	movl	%eax, sort.i(%ebp)

	jmp	L.4
L.5:

	movl	$0, %eax
	addl	$40, %esp
	popl	%ebp
	retl	$12
_main:
	pushl	%ebp
	movl	%esp, %ebp

	.equ	main.i(%ebp), -4
	.equ	main.t.14(%ebp), -8
	.equ	main.t.15(%ebp), -12
	.equ	main.t.16(%ebp), -16
	.equ	main.t.17(%ebp), -20
	.equ	main.t.18(%ebp), -24
	.equ	main.t.19(%ebp), -28
	.equ	main.t.20(%ebp), -32
	.equ	main.t.21(%ebp), -36
	subl	$40, %esp

	movl	$0, %eax
	movl	%eax, main.i(%ebp)
L.6:

	movl	main.i(%ebp), %eax
	cmpl	$10, %eax
	setl	%cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movl	%eax, main.t.14(%ebp)

	movl	main.t.14(%ebp), %eax
	cmpl	$0, %eax
	je	L.7

	leal	main.t.15(%ebp), %eax
	calll	input

	movl	main.t.15(%ebp), %eax
	movl	%eax, main.x.Aain.i(%ebp)(%ebp)

	movl	main.i(%ebp), %eax
	addl	$1, %eax
	movl	%eax, main.t.16(%ebp)

	movl	main.t.16(%ebp), %eax
	movl	%eax, main.i(%ebp)

	jmp	L.6
L.7:

	movl	x, %eax
	pushl	%eax

	movl	$0, %eax
	pushl	%eax

	movl	$10, %eax
	pushl	%eax

	calll	sort
	movl	%eax, main.t.17(%ebp)

	movl	$0, %eax
	movl	%eax, main.i(%ebp)
L.8:

	movl	main.i(%ebp), %eax
	cmpl	$10, %eax
	setl	%cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movl	%eax, main.t.18(%ebp)

	movl	main.t.18(%ebp), %eax
	cmpl	$0, %eax
	je	L.9

	movl	main.x.Aain.i(%ebp)(%ebp), %eax
	movl	%eax, main.t.19(%ebp)

	movl	main.t.19(%ebp), %eax
	pushl	%eax

	popl	%eax
	calll	output
	movl	%eax, main.t.20(%ebp)

	movl	main.i(%ebp), %eax
	addl	$1, %eax
	movl	%eax, main.t.21(%ebp)

	movl	main.t.21(%ebp), %eax
	movl	%eax, main.i(%ebp)

	jmp	L.8
L.9:

	movl	$0, %eax
	addl	$40, %esp
	popl	%ebp
	retl	
