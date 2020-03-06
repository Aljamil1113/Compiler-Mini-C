/**

  Demonstration program for ICST252
  Author: Allan A. Sioson (asioson@gbox.adnu.edu.ph)

  Purpose: Reads a float x, then prints x

  To compile in MacOSX:
	
	gcc -Wl,-no_pie -o iof -m32 iof.s

  To compile in Linux

	gcc -o iof -m32 iof.s

*/

	.globl _main

input:
	# the address of var is in %eax
	pushl	%ebp
	movl	%esp, %ebp

	subl	$8, %esp		
	movl	%eax, 4(%esp)
	leal	fmt.flt, %eax
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
	movsd	%xmm0, 4(%esp)
	leal	fmt.fltnl, %eax
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

	cvtss2sd	-4(%ebp), %xmm0
	calll	output

	addl	$8, %esp

	popl	%ebp
	retl

fmt.flt:
	.asciz	"%g"

fmt.fltnl:
	.asciz	"%g\n"
