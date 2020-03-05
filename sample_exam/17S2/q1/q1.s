# COMP1521 17s2 Final Exam
# void colSum(m, N, a)

   .text
   .globl colSum

# params: m=$a0, N=$a1, a=$a2
colSum:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   addi $sp, $sp, -4
   sw   $s2, ($sp)
   addi $sp, $sp, -4
   sw   $s3, ($sp)
   addi $sp, $sp, -4
   sw   $s4, ($sp)
   addi $sp, $sp, -4
   sw   $s5, ($sp)
   # if you need to save more than six $s? registers
   # add extra code here to save them on the stack

# suggestion for local variables (based on C code):
# m=#s0, N=$s1, a=$s2, row=$s3, col=$s4, sum=$s5
    move  $s0, $a0   
    move  $s1, $a1
    move  $s2, $s2
    
col_ini:
    li  $s4, 0
col_cond:
    bge $s4, $s1, col_finish
    li  $s5, 0
row_ini:
    li  $s3, 0
row_cond:
    bge $s3, $s1, row_finish
    
    move $t0, $s3
    mul  $t0, $t0, $s1
    add  $t0, $t0, $s4
    li   $t1, 4
    mul  $t0, $t0, $t1
    add  $t0, $t0, $s0
    lw   $t2, ($t0)     # t2 = m[row][col]
    
    add $s5, $s5, $t2

row_add:
    add $s3, $s3, 1
    j   row_cond
    
    move $t0, $s4
    mul  $t0, $t0, 4
    add  $t0, $t0, $s2
    lw   $t3, ($t0)
    
    sw   $t2, ($t3)
    
col_add:
    add $s4, $s4, 1
    j   col_cond
# epilogue
   # if you saved more than six $s? registers
   # add extra code here to restore them
   lw   $s5, ($sp)
   addi $sp, $sp, 4
   lw   $s4, ($sp)
   addi $sp, $sp, 4
   lw   $s3, ($sp)
   addi $sp, $sp, 4
   lw   $s2, ($sp)
   addi $sp, $sp, 4
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

