	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 10
	.globl	__Z9changeJamv
	.align	4, 0x90
__Z9changeJamv:                         ## @_Z9changeJamv
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	calll	L0$pb
L0$pb:
	popl	%eax
	movl	$10, _jam-L0$pb(%eax)
	popl	%ebp
	retl

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	calll	L1$pb
L1$pb:
	popl	%eax
	movl	$0, -4(%ebp)
	movl	-8(%ebp), %ecx
	cmpl	-12(%ebp), %ecx
	setg	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, -16(%ebp)
	cmpl	$0, -16(%ebp)
	movl	%eax, -20(%ebp)         ## 4-byte Spill
	je	LBB1_2
## BB#1:
	movl	$99, -16(%ebp)
	movl	-8(%ebp), %eax
	movl	-20(%ebp), %ecx         ## 4-byte Reload
	movl	%eax, _jam-L1$pb(%ecx)
	calll	__Z9changeJamv
LBB1_2:
	xorl	%eax, %eax
	addl	$24, %esp
	popl	%ebp
	retl

	.globl	_jam                    ## @jam
.zerofill __DATA,__common,_jam,4,2

.subsections_via_symbols
