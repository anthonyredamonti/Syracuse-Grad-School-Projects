.data # Defines variable section of an assembly routine.
array: .word 1,3,5,7,9,11,13,15,17 # Defines an array of integers (the input).
.text # Start the instructions of the program.
la $s0, array # Moves the address of array into register $s0.
# Your instructions go here

lw $s1, 0($s0)  # s1 = temp = array[0]
lw $t0, 32($s0) # t0 = array[8]
addi $t0, $t0, 1 # t0 = array[8] + 1
sw $t0, 0($s0)  # array[0] = array[8] + 1
addi $s1, $s1, -1 # temp = temp - 1
sw $s1, 32($s0) # array[8] = temp - 1

lw $s1, 4($s0) # temp = array[1]
lw $t0, 28($s0) # t0 = array[7]
addi $t0, $t0, 3 # t0 = array[7] + 3
sw $t0, 4($s0) # array[1] = array[7] + 3
addi $s1, $s1, -3 # temp = temp - 3
sw $s1, 28($s0) # array[7] = temp - 3

lw $s1, 8($s0) # temp = array[2]
lw $t0, 24($s0) # t0 = array[6]
addi $t0, $t0, 5 # t0 = array[6] + 5
sw $t0, 8($s0) # array[6] = array[6] + 5
addi $s1, $s1, -5 # temp = temp - 5
sw $s1, 24($s0) # array[6] = temp - 5

lw $s1, 12($s0) # temp = array[3]
lw $t0, 20($s0) # t0 = array[5]
sll $t0, $t0, 3 # t0 = array[5] * 8
sw $t0, 12($s0) # array[3] = array[5] * 8
srl $s1, $s1, 3 # temp = temp / 8
sw $s1, 20($s0) # array[5] = temp / 8 
