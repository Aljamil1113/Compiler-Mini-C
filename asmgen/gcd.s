.globl _main

gcd:
	pushl 	%ebp
	movl 	%esp, %ebp

	.equ 	main.x,8(%ebp)
	.equ 	main.y,12(%ebp)

	movl	main.x,%eax
	cmpl	main.y,%eax

	jge		L.1
	movl	main.x,%eax
	jmp		gcd.exit

L1:
	movl	main.x,%eax
	subl	main.y,%eax
	pushl	%eax
	movl	main.y,%eax
	pushl	%eax

	calll	gcd		

gcd.exit:


	popl %ebp
	retl $8
