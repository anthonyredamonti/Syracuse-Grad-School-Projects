// Anthony Redamonti
// 11-11-2020
//
// Please use the gcc compiler to complile this file.
// After navigating to the correct project folder, the following commands were
// performed via the terminal on a Linux (Ubuntu) operating system to compile
// and run the program:
//
// gcc ./instruction_decoder.c -o instruction_decoder
// ./instruction_decoder 
//
// Unix platform is supported. No Windows specific libraries or functions were used.
//
// The following is my solution for Lab 3.
// It decodes an encoded MIPS instruction by converting the binary form to assembly.
//

#include <stdio.h>
#include <string.h>
#define LENGTH 32
#define false 0
#define true 1

// Checks that the char array is 32 bits long
// and only has 0 and 1 in it.
int check(char* bits) {
   if (strlen(bits) != LENGTH) {
      return false;
   }
   for (int i = 0; i < LENGTH; i++) {
      if (bits[i] != '0' && bits[i] != '1') {
         return false;
      }
   }
   return true;
}

void print_register_name(int reg_num){
   switch(reg_num){
      case 0:
         printf("$zero");
         break;
      case 1:
         printf("$at");
         break;
      case 2:
         printf("$v0");
         break;
      case 3:
         printf("$v1");
         break;
      case 4:
         printf("$a0");
         break;
      case 5:
         printf("$a1");
         break;
      case 6:
         printf("$a2");
         break;
      case 7:
         printf("$a3");
         break;
      case 8:
         printf("$t0");
         break;
      case 9:
         printf("$t1");
         break;
      case 10:
         printf("$t2");
         break;
      case 11:
         printf("$t3");
         break;
      case 12:
         printf("$t4");
         break;
      case 13:
         printf("$t5");
         break;
      case 14:
         printf("$t6");
         break;
      case 15:
         printf("$t7");
         break;
      case 16:
         printf("$s0");
         break;
      case 17:
         printf("$s1");
         break;
      case 18:
         printf("$s2");
         break;
      case 19:
         printf("$s3");
         break;
      case 20:
         printf("$s4");
         break;
      case 21:
         printf("$s5");
         break;
      case 22:
         printf("$s6");
         break;
      case 23:
         printf("$s7");
         break;
      case 24:
         printf("$t8");
         break;
      case 25:
         printf("$t9");
         break;
      case 26:
         printf("$k0");
         break;
      case 27:
         printf("$k1");
         break;
      case 28:
         printf("$gp");
         break;
      case 29:
         printf("$sp");
         break;
      case 30:
         printf("$fp");
         break;
      case 31:
         printf("$ra");
         break;
   }
}

unsigned parse_bits(char* bits, int least_significant, int most_significant){
   unsigned result = 0;
   int i;
   int pos = 0;
   for(i = (31-least_significant); i >= (31-most_significant); i--){
      if(bits[i] == '1'){
         result |= 1 << pos;
      }
      pos++;
   }
   return(result);
}

void print_signed_bits_0_15(char* bits){
   unsigned result = 0;
   int pos = 0;
   if(bits[16]=='1'){
      for(int j = 31; j >= 17; j--){
         if(bits[j] == '0'){
            result |= 1 << pos;
         }
         pos++;
      }
      result += 1;
      printf("-");
      printf("%d", result);
   }
   else{
      result = parse_bits(bits, 0, 15);
      printf("%d", result);
   }
}

void print_func(char* bit_string, int func_code){
   unsigned rd, rs, rt, shift_amount;
   switch(func_code){
      case 32:
         printf("add ");
         // rd = 11-15
         rd = parse_bits(bit_string, 11, 15);
         print_register_name(rd);
         printf(", ");
         // rs = 21-25
         rs = parse_bits(bit_string, 21, 25);
         print_register_name(rs);
         printf(", ");
         // rt = 16-20
         rt = parse_bits(bit_string, 16, 20);
         print_register_name(rt);
         printf("\n");
         break;
      case 34:
         printf("sub ");
         // rd = 11-15
         rd = parse_bits(bit_string, 11, 15);
         print_register_name(rd);
         printf(", ");
         // rs = 21-25
         rs = parse_bits(bit_string, 21, 25);
         print_register_name(rs);
         printf(", ");
         // rt = 16-20
         rt = parse_bits(bit_string, 16, 20);
         print_register_name(rt);
         printf("\n");
         break;
      case 0:
         printf("sll ");
         // rd = 11-15
         rd = parse_bits(bit_string, 11, 15);
         print_register_name(rd);
         printf(", ");
         // rt = 16-20
         rt = parse_bits(bit_string, 16, 20);
         print_register_name(rt);
         printf(", ");
         // shift amount = 6-10
         shift_amount = parse_bits(bit_string, 6, 10);
         printf("%d\n", shift_amount);
         break;
      case 8:
         printf("jr ");
         // rs = 21-25
         rs = parse_bits(bit_string, 21, 25);
         print_register_name(rs);
         printf("\n");
         break;
      case 42:
         printf("slt ");
         // rd = 11-15
         rd = parse_bits(bit_string, 11, 15);
         print_register_name(rd);
         printf(", ");
         // rs = 21-25
         rs = parse_bits(bit_string, 21, 25);
         print_register_name(rs);
         printf(", ");
         // rt = 16-20
         rt = parse_bits(bit_string, 16, 20);
         print_register_name(rt);
         printf("\n");
         break;
      case 2:
         printf("srl ");
         // rd = 11-15
         rd = parse_bits(bit_string, 11, 15);
         print_register_name(rd);
         printf(", ");
         // rt = 16-20
         rt = parse_bits(bit_string, 16, 20);
         print_register_name(rt);
         printf(", ");
         // shift amount = 6-10
         shift_amount = parse_bits(bit_string, 6, 10);
         printf("%d\n", shift_amount);
         break;
   }
}

void decode_opcode(char* bit_string){
   unsigned opcode = parse_bits(bit_string, 26, 31);
   unsigned rt, rs, func_code, address;
   // use a switch case statement to perform the correct math function
   switch(opcode){
      case 8:
         printf("addi ");
         // rt = 16-20
         rt = parse_bits(bit_string, 16, 20);
         print_register_name(rt);
         printf(", ");
         // rs = 21-25
         rs = parse_bits(bit_string, 21, 25);
         print_register_name(rs);
         printf(", ");
         print_signed_bits_0_15(bit_string);
         printf("\n");
         break;
      case 35:
         printf("lw ");
         // rt = 16-20
         rt = parse_bits(bit_string, 16, 20);
         print_register_name(rt);
         printf(", ");
         print_signed_bits_0_15(bit_string);
         printf("(");
         // rs = 21-25
         rs = parse_bits(bit_string, 21, 25);
         print_register_name(rs);
         printf(")\n");
         break;
      case 0:
         //(add, sub, sll, jr, slt, srl)
         func_code = parse_bits(bit_string, 0, 5);
         print_func(bit_string, func_code);
         break;
      case 43:
         printf("sw ");
         // rt = 16-20
         rt = parse_bits(bit_string, 16, 20);
         print_register_name(rt);
         printf(", ");
         print_signed_bits_0_15(bit_string);
         printf("(");
         // rs = 21-25
         rs = parse_bits(bit_string, 21, 25);
         print_register_name(rs);
         printf(")\n");
         break;
      case 4:
         printf("beq ");
         // rs = 21-25
         rs = parse_bits(bit_string, 21, 25);
         print_register_name(rs);
         printf(", ");
         // rt = 16-20
         rt = parse_bits(bit_string, 16, 20);
         print_register_name(rt);
         printf(", ");
         print_signed_bits_0_15(bit_string);
         printf("\n");
         break;
      case 2:
         printf("j ");
         address = parse_bits(bit_string, 0, 25);
         address = (address << 2);
         address = address + 4026531840; // add 0xF0000000
         printf("%u", address); //printf("%X", address);
         printf("\n");
         break;
      case 5:
         printf("bne ");
         // rs = 21-25
         rs = parse_bits(bit_string, 21, 25);
         print_register_name(rs);
         printf(", ");
         // rt = 16-20
         rt = parse_bits(bit_string, 16, 20);
         print_register_name(rt);
         printf(", ");
         print_signed_bits_0_15(bit_string);
      default:
         //printf("Error: Bad operator.\n");
         break;
   }
}

// We will take the bitstring as a command line argument.
int main(int argc, char **argv) {

   // Make sure we have at least one argument.
   if (argc < 2) {
      fprintf(stderr, "No argument found\n");
      return -1;
   }
   // Get a pointer to the argument.
   char *instruction = argv[1];
   if (!check(instruction)) {
      fprintf(stderr, "Invalid bit string\n");
      return -2;
   }
   // Your code here!
   // You can use regular printf()'s to produce your output.
   decode_opcode(instruction);
   return 0;
}
