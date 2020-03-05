# board2.s ... Game of Life on a 15x15 grid

	.data

N:	.word 15  # gives board dimensions

board:
	.byte 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0
	.byte 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0
	.byte 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0
	.byte 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0
	.byte 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1
	.byte 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0
	.byte 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0

newBoard: .space 225
# COMP1521 19t2 ... Game of Life on a NxN grid
#
# Written by <<Yiting Liu>>, June 2019

## Requires (from `boardX.s'):
# - N (word): board dimensions
# - board (byte[][]): initial board state
# - newBoard (byte[][]): next board state

## Global data
	.data
one:    .byte 1
zer:    .byte 0
msg1:   .asciiz "# Iterations: "
msg2:   .asciiz "=== After iteration "
msg3:   .asciiz " ===\n"

## Requires (from `boardX.s'):
# - N (word): board dimensions
# - board (byte[][]): initial board state
# - newBoard (byte[][]): next board state

## Provides:
	.globl	main
	.globl	decideCell
	.globl	neighbours
	.globl	copyBackAndShow

########################################################################
# .TEXT <main>
	.text
main:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3
# Uses:		$a0, $a1, $t1, $t2, $s0, $s1, $s2, $s3, $v0
# Clobbers:	$a0, $a1

# Locals:
#   - 'n' in $s0
#   - 'i' in $s1
#   - 'j' in $s2
#   - 'N' in $s3
#   - 'maxiters' in $s4
#   - 'nn' in $s5
#   - 'board[i][j]' in $t1

# Structure:
#	main
#	-> [prologue]
#   -> n_init_main
#	-> n_cond_main
#	    -> i_init_main
#	    -> i_cond_main
#	        -> j_init_main
#	        -> j_cond_main
#	        -> j_step_main
#           -> j_finish_main
#	    -> i_step_main
#       -> i_finish_main
#	-> n_step_main
#   -> n_finish_main
#	-> [epilogue]

# Code:

    ## set up stack frame
    sw  $fp, -4($sp)    # push $fp onto stack
    la  $fp, -4($sp)    # set up $fp for this function
    sw  $ra, -4($fp)    # save return address
    sw  $s0, -8($fp)    # save $s0 to use as int n
    sw  $s1, -12($fp)   # save $s1 to use as int i
    sw  $s2, -16($fp)   # save $s2 to use as int j
    sw  $s3, -20($fp)   # save $s3 to use as N
    sw  $s4, -24($fp)   # save $s4 to use as maxiters
    sw  $s5, -28($fp)   # save $s5 to use as nn
    addi    $sp, $sp, -32   # reset $sp to last pushed item
    
    ## Code for main() 
    la	$a0, msg1
	li	$v0, 4
	syscall			# printf ("# Iterations: ")
    
    li  $v0, 5
	syscall			    # scanf("%d", into $v0)
    move    $s4, $v0    # $s4 = maxiters

    lw  $s3, N      # store N in s3
    
    ######
    #move	$a0, $s3
	#li	$v0, 4
	#syscall
	######
    
n_init_main:
    li  $s0, 1  # int n = 1
n_cond_main:
	bgt $s0, $s4, n_finish_main  # if (n > maxiters) end the loop
	nop
	
i_init_main:
    li  $s1, 0  # int i = 0
i_cond_main:
    bge $s1, $s3, i_finish_main  # if (i >= N) end the loop
    nop
    
j_init_main:
    li  $s2, 0  # int j = 0
j_cond_main:
    bge $s2, $s3, j_finish_main  # if (j >= N) end the loop
    nop
     
    li  $s5, 0          # int nn = 0
    
    move  $a0, $s1      # a0 = i
    move  $a1, $s2      # a1 = j
    jal neighbours
    nop    
    move    $s5, $v0    # nn = neighbour (i, j) 
    
    # board[i][j] = *(&board[0][0] + (i * N) + j)
    la  $a0, board  # a0 = %board[0][0] 
    mul	$t2, $s1, $s3	# % <- i * N
    add	$t2, $t2, $s2	#    + j
	addu $t1, $t2, $a0 	#    + &board[0][0]
    lb  $t1, ($t1)      # t1 = board[i][j]
    
    move  $a0, $t1      # a0 = board[i][j]
    move  $a1, $s5      # a1 = nn
    jal decideCell
    
    sb  $v0, newBoard($t2)  # newboard[i][j] = decideCell (board[i][j], nn)
        
j_step_main:
    addi    $s2, $s2, 1 # j++
    j   j_cond_main
    nop
j_finish_main:
    

i_step_main:
    addi    $s1, $s1, 1 # i++
    j   i_cond_main
    nop
i_finish_main:
       
    la  $a0, msg2
    li  $v0, 4
    syscall         # printf("=== After iteration")
    
    move  $a0, $s0
    li  $v0, 1
    syscall         # printf("%d", n)
    
    la  $a0, msg3
    li  $v0, 4
    syscall         # printf(" ===\n")
    
    jal copyBackAndShow     # copyBackAndShow()
    nop
    
n_step_main:
    add $s0, $s0, 1 # n++
    j   n_cond_main
    nop
n_finish_main:   
    
	# tear down stack frame
	lw  $s5, -28($fp)   # restore s5 value
	lw  $s4, -24($fp)   # restore s4 value
	lw  $s3, -20($fp)   # restore s3 value
	lw  $s2, -16($fp)   # restore s2 value
	lw  $s1, -12($fp)   # restore s1 value
	lw  $s0, -8($fp)    # restore s0 value
	lw  $ra, -4($fp)    # restore $ra for return
	la	$sp, 4($fp)	# restore $sp (remove stack frame)
	lw	$fp, ($fp)	# restore $fp (remove stack frame)
	
	jr	$ra # return

######################################################################
# .TEXT <decideCell>
	.text
decideCell:

# Frame:	$fp, $ra, $s0, $s1
# Uses:		$a0, $a1, $t0, $s0, $s1
# Clobbers:	$t0

# Locals:	
#   - 'old' in $s0(from $a0)
#   - 'nn' in $s1(from $a1)
#   - 'ret' in $t0

# Structure:
#   decideCell
#	-> [prologue]
#   -> if_cond_fun1
#	    -> ret_zero
#       -> ret_one
#   -> end_decideCell_fun1
#	-> [epilogue]

# Code:
    
    

    ## set up stack frame
    sw	$fp, -4($sp)	# push $fp onto stack
	la	$fp, -4($sp)	# set up $fp for this function
	sw	$ra, -4($fp)	# save return address
	sw  $s0, -8($fp)    # save old
	sw  $s1, -12($fp)   # save nn
	addi	$sp, $sp, -16	# reset $sp to last pushed item
    
    move    $s0, $a0    # int old
    move    $s1, $a1    # int nn
    
    beq $s0, 1, if_cond_fun1     # if (old == 1) goto if_vond_fun1
    beq $s1, 3, ret_one          # if (nn == 3)   ret = 1
    j   ret_zero                 # else  ret = 0
    
if_cond_fun1:
    blt $s1, 2, ret_zero  # if (nn < 2)
   
    beq $s1, 2, ret_one
    beq $s1, 3, ret_one  # if (nn == 2 || nn == 3) 
    
    j    ret_zero       # else

ret_zero:
    lb  $t0, zer      # ret = 0
    j    end_decideCell_fun1
    
ret_one:
    lb  $t0, one      # ret = 1

end_decideCell_fun1:  
    
    move    $v0, $t0    # return t0
    
    # tear down stack frame
	lw  $s1, -12($fp)   # restore s1 value
	lw  $s0, -8($fp)    # restore s0 value
	lw  $ra, -4($fp)    # restore $ra for return
	la	$sp, 4($fp)	# restore $sp (remove stack frame)
	lw	$fp, ($fp)	# restore $fp (remove stack frame)
	
	jr	$ra # return

####################################################################
# .TEXT <neighbours>
	.text
neighbours:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3, $s4, $s5
# Uses:		$t0, $t1, $t2, $a2, $s0, $s1, $s2, $s3, $s4, $s5, $t3
# Clobbers:	$t3

# Locals:
#   - 'i' in $s0(from $a0)
#   - 'j' in $s1(from $a1)
#   - 'x' in $s2
#   - 'y' in $s3
#   - 'nn' in $s4
#   - 'N' in $s5
#   - 'i + x' in $t0
#   - 'N - 1' in $t1
#   - 'j + y' in $t2
#   - 'board[i + x][j + y]' in $t3

# Structure:
#   neighbours
#	-> [prologue]
#   -> x_init_fun2
#	-> x_cond_fun2
#	    -> y_init_fun2
#	    -> y_cond_fun2
#	        -> first_if_fun2
#	        -> second_if_fun2
#	        -> third_if_part1_fun2
#           -> third_if_part2_fun2
#           -> end_third_if_fun2
#           -> end_if_fun2
#	    -> y_step_func2
#       -> y_finish_fun2
#	-> x_step_fun2
#   -> x_finish_fun2
#	-> [epilogue]

# Code:

    ## set up stack frame
    sw	$fp, -4($sp)	# push $fp onto stack
	la	$fp, -4($sp)	# set up $fp for this function
	sw	$ra, -4($fp)	# save return address
	sw  $s0, -8($fp)    # save i
	sw  $s1, -12($fp)   # save j
	sw  $s2, -16($fp)   # save x
	sw  $s3, -20($fp)   # save y
	sw  $s4, -24($fp)   # save nn
	sw  $s5, -28($fp)   # save N
	addi	$sp, $sp, -32	# reset $sp to last pushed item
    
    move    $s0, $a0    # int i
    move    $s1, $a1    # int j
    li  $s4, 0          # int nn = 0
    lw  $s5, N          # store N in s5
    
x_init_fun2:
    li  $s2, -1    # int x = -1
x_cond_fun2:
    bgt $s2, 1, x_finish_fun2    # if x > 1, end loop
    nop
  
y_init_fun2:
    li  $s3, -1     # int y = -1
y_cond_fun2:
    bgt $s3, 1, y_finish_fun2    # if y > 1, end loop
    nop
    
    
    add $t0, $s0, $s2    # t0 = i + x
    add $t1, $s5, -1     # t1 = N - 1
    add $t2, $s1, $s3    # t2 = j + y
    
first_if_fun2:
    blt $t0, 0, y_step_fun2      # if ((i + x) < 0) continue
    bgt $t0, $t1, y_step_fun2    # if ((i + x) > (N - 1)) continue

second_if_fun2:
    blt $t2, 0, y_step_fun2      # if ((j + y) < 0) continue;
    bgt $t2, $t1, y_step_fun2    # if ((j + y) > (N - 1)) continue
    
third_if_part1_fun2:
    beq $s2, 0, third_if_part2_fun2  # if (x == 0) goto third_if_part2
    j   end_third_if_fun2            # else skip third_if
third_if_part2_fun2:
    beq $s3, 0, y_step_fun2          # if (x == 0 && y == 0) continue;
end_third_if_fun2:
         
    # board[i + x][j + y] = *(&board[0][0] + ([i + x] * N) + [j + y])
    la  $a2, board          # a2 = &board[0][0]
    mul $t3, $t0, $s5       # temp <- [i + x] * N
    add $t3, $t3, $t2       # + [i + y]
    addu    $t3, $t3, $a2   # = &board[0][0]
    lb  $t3, ($t3)          # t3 = board[i + x][j + y]
    
    bne $t3, 1, end_if_fun2 # if (board[i + x][j + y] != 1) 
    add $s4, $s4, 1         # else nn++
end_if_fun2:
    
y_step_fun2:
    add $s3, $s3, 1     # y++
    j   y_cond_fun2
    nop
y_finish_fun2:

x_step_fun2:
    add $s2, $s2, 1     # x++
    j   x_cond_fun2
    nop
x_finish_fun2:
    
    move    $v0, $s4    # return nn
    
    # tear down stack frame
    lw  $s5, -28($fp)   # restore s5 value
    lw  $s4, -24($fp)   # restore s4 value
    lw  $s3, -20($fp)   # restore s3 value
    lw  $s2, -16($fp)   # restore s2 value
	lw  $s1, -12($fp)   # restore s1 value
	lw  $s0, -8($fp)    # restore s0 value
	lw  $ra, -4($fp)    # restore $ra for return
	la	$sp, 4($fp)	# restore $sp (remove stack frame)
	lw	$fp, ($fp)	# restore $fp (remove stack frame)
	
	jr	$ra # return

####################################################################
# .TEXT <copyBackAndShow>
	.text
copyBackAndShow:

# Frame:	$fp, $ra, $s0, $s1, $s2
# Uses:		$a0, $t0, $t1, $t2, $s0, $s1, $s2
# Clobbers:	$a0, $t0

# Locals:
#   - 'i' in $s0
#   - 'j' in $s1
#   - 'N' in $s2
#   - 'newBoard[i][j]' in $t1

# Structure:
#   copyBackAndShow
#	-> [prologue]
#	-> i_init_fun3
#	-> i_cond_fun3
#	    -> j_init_fun3
#	    -> j_cond_fun3
#	        -> if_cond_fun3
#           -> if_cond_two_fun3
#           -> end_if_fun3
#	    -> j_step_fun3
#       -> j_finish_fun3
#	-> i_step_fun3
#   -> i_finish_fun3
#	-> [epilogue]

# Code:
    ## set up stack frame
    sw	$fp, -4($sp)	# push $fp onto stack
	la	$fp, -4($sp)	# set up $fp for this function
	sw	$ra, -4($fp)	# save return address
	sw  $s0, -8($fp)    # save i
	sw  $s1, -12($fp)   # save j
	sw  $s2, -16($fp)   # save N
	addi	$sp, $sp, -20	# reset $sp to last pushed item
   
    lw  $s2, N      # store N in s2

i_init_fun3:
    li  $s0, 0  # int i = 0
i_cond_fun3:
    bge $s0, $s2, i_finish_fun3  # if (i >= N) end the loop
    nop
    
j_init_fun3:
    li  $s1, 0  # int j = 0
j_cond_fun3:
    bge $s1, $s2, j_finish_fun3  # if (j >= N) end the loop
    nop
    
    # newboard[i][j] = *(&newboard[0][0] + (i * N) + j)
    la  $a0, newBoard       # a0 = &newBoard[0][0]
    mul $t0, $s0, $s2       # temp <- i * N
    add $t0, $t0, $s1       # + j
    addu    $t1, $a0, $t0   # + &newBoard[0][0]
    lb  $t1, ($t1)          # *temp = newBoard[i][j]
    
    sb  $t1, board($t0)     # newBoard[i][j] = board[i][j]
    
    li  $t2, 0
    bne $t1, $t2, if_cond_two_fun3 # if (board[i][j] != 0) goto if_cond_two

if_cond_fun3:
    li	$a0, '.'
	li	$v0, 11
	syscall			# putchar('.')
    j   end_if_fun3
if_cond_two_fun3:
    li	$a0, '#'
	li	$v0, 11
	syscall			# putchar('#')
end_if_fun3:

j_step_fun3:
    add $s1, $s1, 1 # j++
    j   j_cond_fun3
    nop
j_finish_fun3:

    li	$a0, '\n'
	li	$v0, 11
	syscall			# putchar('\n')

i_step_fun3:
    add $s0, $s0, 1 # i++
    j   i_cond_fun3
    nop
i_finish_fun3:
    
    # tear down stack frame
    lw  $s2, -16($fp)   # restore s2 value
	lw  $s1, -12($fp)   # restore s1 value
	lw  $s0, -8($fp)    # restore s0 value
	lw  $ra, -4($fp)    # restore $ra for return
	la	$sp, 4($fp)	# restore $sp (remove stack frame)
	lw	$fp, ($fp)	# restore $fp (remove stack frame)
	
	jr	$ra # return
