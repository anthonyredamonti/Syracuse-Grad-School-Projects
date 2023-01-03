.data
array: .word 4,5,6,67
.text
addi $t0, $t0, 128
sll $t0, $t0, 1
addi $t2, $zero, 100
addi $t1, $zero, 1048000
slt $t2, $t1, $zero