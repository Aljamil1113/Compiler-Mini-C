	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 10
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%eax
	calll	L0$pb
L0$pb:
	popl	%eax
	movl	$1, %ecx
	xorl	%edx, %edx
	movl	$0, -8(%ebp)
	movl	$5, _x-L0$pb(%eax)
	movl	_x-L0$pb(%eax), %esi
	subl	$7, %esi
	subl	%esi, %edx
	movl	%edx, _x-L0$pb(%eax)
	movl	%ecx, %eax
	addl	$4, %esp
	popl	%esi
	popl	%ebp
	retl

	.globl	_x                      ## @x
.zerofill __DATA,__common,_x,4,2

.subsections_via_symbols
