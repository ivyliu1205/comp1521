# COMP1521 19t2 / Practice Prac Exam / Question 1
# int novowels (char *src, char *dest)

	.text
	.globl	novowels

# params: src=$a0, dest=$a1
novowels:
	# prologue
	addi	$sp, $sp, -4
	sw	$fp, ($sp)
	la	$fp, ($sp)
	addi	$sp, $sp, -4
	sw	$ra, ($sp)
	addi	$sp, $sp, -4
	sw	$s0, ($sp)
	addi	$sp, $sp, -4
	sw	$s1, ($sp)
	# if you need to save more $s? registers
	# add the code to save them here

# function body
# locals: ...

	# add code for your novowels function here

# epilogue
	# if you saved more than two $s? registers
	# add the code to restore them here
	lw	$s1, ($sp)
	addi	$sp, $sp, 4
	lw	$s0, ($sp)
	addi	$sp, $sp, 4
	lw	$ra, ($sp)
	addi	$sp, $sp, 4
	lw	$fp, ($sp)
	addi	$sp, $sp, 4
	jr	$ra


# a useful auxiliary function: int isvowel(char ch)
isvowel:
	addi	$sp, $sp, -4
	sw	$fp, ($sp)
	la	$fp, ($sp)
	addi	$sp, $sp, -4
	sw	$ra, ($sp)

	li	$t0, 'a'
	beq	$a0, $t0, isvowel_match
	li	$t0, 'A'
	beq	$a0, $t0, isvowel_match
	li	$t0, 'e'
	beq	$a0, $t0, isvowel_match
	li	$t0, 'E'
	beq	$a0, $t0, isvowel_match
	li	$t0, 'i'
	beq	$a0, $t0, isvowel_match
	li	$t0, 'I'
	beq	$a0, $t0, isvowel_match
	li	$t0, 'o'
	beq	$a0, $t0, isvowel_match
	li	$t0, 'O'
	beq	$a0, $t0, isvowel_match
	li	$t0, 'u'
	beq	$a0, $t0, isvowel_match
	li	$t0, 'U'
	beq	$a0, $t0, isvowel_match

	li	$v0, 0
	j	isvowel__epi

isvowel_match:
	li	$v0, 1

isvowel__epi:
	lw	$ra, ($sp)
	addi	$sp, $sp, 4
	lw	$fp, ($sp)
	addi	$sp, $sp, 4
	jr	$ra
