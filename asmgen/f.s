/**

  Demonstration program for ICST252
  Author: Allan A. Sioson (asioson@gbox.adnu.edu.ph)

  Purpose: Reads a number n, then prints fib(n)


  To compile in MacOSX:
	
	gcc -Wl,-no_pie -o f -m32 f.s

  To compile in Linux

	gcc -o f -m32 f.s

*/

	.globl _main

input:
	# the address of var is in %eax
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

output:
	# the value to be printed is in %eax
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

fib:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp

	.equ	fib.x, 8
	.equ	fib.t1, -4

	movl	fib.x(%ebp), %eax
	cmpl	$0, %eax
	jg	L.1
	movl	$0, %eax
	jmp	fib.exit
L.1:
	movl	fib.x(%ebp), %eax
	cmpl	$1, %eax
	jne	L.2
	movl	$1, %eax
	jmp	fib.exit
L.2:
	movl	fib.x(%ebp), %eax
	subl	$1, %eax
	pushl	%eax
	calll	fib
	movl	%eax, fib.t1(%ebp)
	
	movl	fib.x(%ebp), %eax
	subl	$2, %eax
	pushl	%eax
	calll	fib
	
	addl	fib.t1(%ebp), %eax

fib.exit:
	addl	$4, %esp
	popl	%ebp
	retl	$4


_main:
	pushl	%ebp
	movl	%esp, %ebp

	subl	$8, %esp
	
	leal	-4(%ebp), %eax
	calll	input

	movl	-4(%ebp), %eax
	pushl	%eax
	calll	fib

	# result is in %eax

	calll	output

	addl	$8, %esp

	popl	%ebp
	retl

fmt.int:
	.asciz	"%d"

fmt.intnl:
	.asciz	"%d\n"
