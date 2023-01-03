.data # Defines variable section of an assembly routine.
array: .word 0, 5, 15, 3, 18, 7, 20, 2, 16, 1 # Define a variable named array as a word
# (integer) array.
# After your program has run, the integers in this
# array should be sorted.
.text # Defines the start of the code section for the program.
.globl main
main:
la $t0, array # Move the address of array into register $t0.
addi $a0, $t0, 0 # Set argument 1 to the base address of the array.
addi $a1, $zero, 10 # Set argument 2 to (n = 10).
jal shell_sort # Call shell_sort (you need to implement this function).
li $v0, 10 # System Service call to terminate program run.
syscall

swap:
addi $sp, $sp, -4
sw $s0, 0($sp)    # save s0 on the stack (temp variable)

sll $t0, $a1, 2 
add $t0, $a0, $t0 # i1 index memory location in t0
lw $s0, 0($t0)    # temp = array[i1]
sll $t1, $a2, 2 
add $t1, $a0, $t1 # i2 index memory location in t1
lw $t2, 0($t0)    # t2 = array[i1]
lw $t3, 0($t1)    # t3 = array[i2]
sw $t3, 0($t0)    # array[i1] = array[i2]
sw $s0, 0($t1)    # array[i2] = temp

lw $s0, 0($sp)    # return s0 back to original value from the stack
addi $sp, $sp, 4
jr $ra

insert_shell:
addi $sp, $sp, -36 # save s0-s4 as well as the return address
sw $ra, 32($sp)
sw $a2, 28($sp)
sw $a1, 24($sp)
sw $a0, 20($sp)
sw $s4, 16($sp)
sw $s3, 12($sp)
sw $s2, 8($sp)
sw $s1, 4($sp)
sw $s0, 0($sp)
move $s0, $a0 # s0 = array
move $s1, $a1 # s1 = n
move $s2, $a2 # s2 = gap
move $s3, $a2 # s3 = i = gap

bne $s2, $zero, outer_loop # if gap is non-zero begin outer_loop
addi $v0, $zero, 0 # if gap == 0 then v0 = 0. Exit function.
j exit_insert_shell

outer_loop:
move $s4, $s3 # j = i
slt $t0, $s3, $s1 # t0 = 1 if i < n
bne $t0, $zero, inner_loop # if i < n then jump to inner_loop
addi $v0, $zero, 1 # if i >= n then v0 = 1. Exit function.
j exit_insert_shell

inner_loop:
slt $t0, $s4, $s2 # t0 = 1 if j < gap
bne $t0, $zero, exit_inner # if j < gap then exit the inner loop
sub $t0, $s4, $s2 # t0 = j - gap
sll $t3, $t0, 2 # t3 = t0 x 4
add $t3, $s0, $t3 # t3 = address of array[j-gap]
lw $t3, 0($t3) # t3 = array[j-gap]
sll $t1, $s4, 2 # t1 = j x 4
add $t1, $t1, $s0 # t1 = address of array[j]
lw $t1, 0($t1) # t1 = array[j]
slt $t2, $t1, $t3 # t2 = 1 if array[j] < array[j-gap]     if t1 < t3 then t2 = 1
beq $t2, $zero, exit_inner # if array[j] >= array[j-gap] then exit the inner loop
# setup the swap arguments
move $a0, $s0 # a0 = array
move $a1, $t0 # a1 = (j - gap)
move $a2, $s4 # a2 = j
jal swap
sub $s4, $s4, $s2 # j = j - gap
j inner_loop

exit_inner:
addi $s3, $s3, 1
j outer_loop

exit_insert_shell:
lw $s0, 0($sp)
lw $s1, 4($sp)
lw $s2, 8($sp)
lw $s3, 12($sp)
lw $s4, 16($sp)
lw $a0, 20($sp)
lw $a1, 24($sp)
lw $a2, 28($sp)
lw $ra, 32($sp)
addi $sp, $sp, 36
jr $ra

shell_sort:
addi $sp, $sp, -16
sw $ra, 12($sp)
sw $s2, 8($sp)
sw $s1, 4($sp)
sw $s0, 0($sp)
move $s0, $a0 # s0 = array
move $s1, $a1 # s1 = n
srl $s2, $s1, 1 # s2 = gap = (n/2)
move $a2, $s2 # a2 = gap

while_loop:
jal insert_shell
beq $v0, $zero, exit_shell_sort
srl $a2, $a2, 1 # gap = gap / 2
j while_loop

exit_shell_sort:
lw $s0, 0($sp)
lw $s1, 4($sp)
lw $s2, 8($sp)
lw $ra, 12($sp)
addi $sp, $sp, 16
jr $ra
