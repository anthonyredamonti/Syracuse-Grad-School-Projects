addi $s3, $zero, 5
addi $s0, $zero, 0 # s0 = x = 0
addi $s1, $zero, 0 # s1 = i = 0

forlp1:
slt $t0, $s1, $s3
beq $t0, $zero, exitforlp1
add $s2, $s1, $zero

forlp2:
slt $t0, $s2, $s3
beq $t0, $zero, exitforlp2
addi $s0, $s0, 1
addi $s2, $s2, 1
j forlp2

exitforlp2:
addi $s1, $s1, 1
j forlp1

exitforlp1:
addi $t4, $zero, 123