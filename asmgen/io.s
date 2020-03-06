/**

  Demonstration program for ICST252
  Author: Allan A. Sioson (asioson@gbox.adnu.edu.ph)

  Purpose: Reads an integer x, then prints x

  To compile in MacOSX:
	
	gcc -Wl,-no_pie -o io -m32 io.s

  To compile in Linux

	gcc -o io -m32 io.s

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

_main:
	pushl	%ebp
	movl	%esp, %ebp

	subl	$8, %esp
	
	leal	-4(%ebp), %eax
	calll	input

	movl	-4(%ebp), %eax
	calll	output

	addl	$8, %esp

	popl	%ebp
	retl

fmt.int:
	.asciz	"%d"

fmt.intnl:
	.asciz	"%d\n"
