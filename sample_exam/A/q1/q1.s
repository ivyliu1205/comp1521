# COMP1521 19t2 / Practice Prac Exam / Question 1
# int rmOdd (int *src, int n, int *dest)

	.text
	.globl	rmOdd

# params: src=$a0, n=$a1, dest=$a2
rmOdd:
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
	addi	$sp, $sp, -4
	sw	$s2, ($sp)
	addi	$sp, $sp, -4
	sw	$s3, ($sp)
	addi	$sp, $sp, -4
	sw	$s4, ($sp)
	# if you need to save more $s? registers
	# add the code to save them here

# function body
# locals: ...
    li  $s0, $a0    # s0 = src
    li  $s1, $a1    # s1 = n
    li  $s2, $a2    # s2 = dest
    
	li  $s3, 0  # s3 = i = 0
	li  $s4, 0  # s4 = j = 0
i_cond:
    bge $s3, $s1, i_finish

if_cond:
    move    $t0, $s3
    mul	$t0, $t0, 4
	add	$t0, $t0, $s0
    lw	$t1, ($t0)  # t1 = src[i]
    
    rem $t2, $t1, 2 # t2 = src[i] % 2
    
    bne $t2, 0, i_add
    
    move    $t0, $s4
    mul	$t0, $t0, 4
	add	$t0, $t0, $s2
    lw	$t3, ($t0)  # t3 = dest[j]
    sw  $t2, ($t3)
    
    add $s4, $s4, 1
    
i_add: 
    add $s3, $s3, 1
    j   i_cond
i_finish:   


# epilogue
	# if you saved more than two $s? registers
	# add the code to restore them here
	lw	$s4, ($sp)
	addi	$sp, $sp, 4
	lw	$s3, ($sp)
	addi	$sp, $sp, 4
	lw	$s2, ($sp)
	addi	$sp, $sp, 4
	lw	$s1, ($sp)
	addi	$sp, $sp, 4
	lw	$s0, ($sp)
	addi	$sp, $sp, 4
	lw	$ra, ($sp)
	addi	$sp, $sp, 4
	lw	$fp, ($sp)
	addi	$sp, $sp, 4
	jr	$ra
