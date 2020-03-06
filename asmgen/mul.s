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

amul:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp

	.equ 	amul.x, 8

	movl	amul.x(%ebp), %eax
	movl 	$4, %ebx
	sarl	$31, %edx
	idivl	%ebx


amul.exit:
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
	calll	amul

	# result is in %eax

	calll	output

	addl	$8, %esp

	popl	%ebp
	retl

fmt.int:
	.asciz	"%d"

fmt.intnl:
	.asciz	"%d\n"
