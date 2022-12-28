#
# The following program simply creates an array of 10 integers
# and runs a loop to find the minimum and maximum values in 
# the array. The minimum value is stored in register $s0 and
# the maximum value is stored in register $s1.
#

.data                  # Defines variable section of an assembly routine.
array: .word 10, 5, 15, 3, 18, 7, 20, 2, 16, 1 # Define a variable named array as a word
                                              # (integer) array.

.text                  # Defines the start of the code section for the program.
.globl main

main:
la $t0, array          # Move the address of array into register $t0.
addi $t1, $zero, 10    # t1 will have the number of elements inside of it (10) (array length)
lw $s0, 0($t0)         # min = array[0]
lw $s1, 0($t0)         # max = array[0]
addi $t2, $zero, 1     # t2 represents i which will start at index 1 in the array (not index 0)

loop:
beq $t1, $t2, exit_loop

sll $t3, $t2, 2        # t3 holds the offset to be applied later to the original address of the array
add $t3, $t3, $t0      # t3 holds the address of array[i]
lw $t4, 0($t3)         # t4 holds the value of array[i]

slt $t5, $t4, $s0      # slt = set less than. Set t5 if s0 (min) is less than t4 (array[i])
beq $t5, $zero, do_not_set_min
add $s0, $zero, $t4   # set min = array[i]

do_not_set_min:
slt $t5, $t4, $s1      # set t5 if t4 (array[i]) is less than s1 (max)
bne $t5, $zero, do_not_set_max
add $s1, $zero, $t4   # set max = array[i]

do_not_set_max:

addi $t2, $t2, 1
j loop

exit_loop:
li $v0, 10             # System Service call to terminate program run.
syscall