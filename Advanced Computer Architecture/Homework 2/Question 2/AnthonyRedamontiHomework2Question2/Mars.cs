/*
 
 Anthony Redamonti
 Prof. Mohammed Abdallah
 Syracuse University
 CIS-655 Advanced Computer Architecture
 Homework 2 Question 2
 10/27/2021
    
 The following is a code editor similar to MARS. 
 The Instruction Set Architectue is custom and 
 documented in detail in the PDF attached.
  
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AnthonyRedamontiHomework2Question2
{
    public partial class Mars : Form
    {
        int parsingIndex = 0; // index used to parse commands
        const int zeroRegisterValue = 0; // zero register is a constant value
        int[] registerValueArray = new int[25]; // rest of registers are modifiable
        double[] floatValueArray = new double[6]; // modifiable floating point register values

        TextBox[] registerTextBoxArray = new TextBox[32]; // all register textboxes are put inside of array

        int[] memoryLocations = new int[32]; // memory locations
        string[] memoryValueArray = new string[32]; // contiguous values of the memory locations
        bool[] memoryValueIsDouble = new bool[32];
        TextBox[] memoryTextBoxArray = new TextBox[32];
        int memoryOffset = 268500992;

        string[] registerNameStringArray = new string[32]; // an array containing the register strings
        string[] opcodeStringArray = new string[50]; // an array holding all 51 op-codes

        public Mars()
        {
            InitializeComponent();
        }

        // initialize register textboxes in the textbox array
        // and start the register timer
        private void Mars_Load(object sender, EventArgs e) {

            // load the register strings array with the register strings
            registerNameStringArray[0] = "$zero";
            registerNameStringArray[1] = "$at";
            registerNameStringArray[2] = "$v0";
            registerNameStringArray[3] = "$v1";
            registerNameStringArray[4] = "$a0";
            registerNameStringArray[5] = "$a1";
            registerNameStringArray[6] = "$a2";
            registerNameStringArray[7] = "$a3";
            registerNameStringArray[8] = "$t0";
            registerNameStringArray[9] = "$t1";
            registerNameStringArray[10] = "$t2";
            registerNameStringArray[11] = "$t3";
            registerNameStringArray[12] = "$t4";
            registerNameStringArray[13] = "$t5";
            registerNameStringArray[14] = "$f0";
            registerNameStringArray[15] = "$f1";
            registerNameStringArray[16] = "$s0";
            registerNameStringArray[17] = "$s1";
            registerNameStringArray[18] = "$s2";
            registerNameStringArray[19] = "$s3";
            registerNameStringArray[20] = "$s4";
            registerNameStringArray[21] = "$s5";
            registerNameStringArray[22] = "$f2";
            registerNameStringArray[23] = "$f3";
            registerNameStringArray[24] = "$f4";
            registerNameStringArray[25] = "$f5";
            registerNameStringArray[26] = "$k0";
            registerNameStringArray[27] = "$k1";
            registerNameStringArray[28] = "$gp";
            registerNameStringArray[29] = "$sp";
            registerNameStringArray[30] = "$fp";
            registerNameStringArray[31] = "$ra";

            // load the opcodes into the opcode string array
            opcodeStringArray[0] = "readw";
            opcodeStringArray[1] = "writew";
            opcodeStringArray[2] = "add";
            opcodeStringArray[3] = "addv";
            opcodeStringArray[4] = "sub";
            opcodeStringArray[5] = "mult";
            opcodeStringArray[6] = "multv";
            opcodeStringArray[7] = "div";
            opcodeStringArray[8] = "divrv";
            opcodeStringArray[9] = "divvr";
            opcodeStringArray[10] = "and";
            opcodeStringArray[11] = "or";
            opcodeStringArray[12] = "xor";
            opcodeStringArray[13] = "nand";
            opcodeStringArray[14] = "nor";
            opcodeStringArray[15] = "not";
            opcodeStringArray[16] = "andv";
            opcodeStringArray[17] = "orv";
            opcodeStringArray[18] = "xorv";
            opcodeStringArray[19] = "nandv";
            opcodeStringArray[20] = "setlt";
            opcodeStringArray[21] = "setltv";
            opcodeStringArray[22] = "atan2";
            opcodeStringArray[23] = "rand";
            opcodeStringArray[24] = "log";
            opcodeStringArray[25] = "pow";
            opcodeStringArray[26] = "sin";
            opcodeStringArray[27] = "cos";
            opcodeStringArray[28] = "tan";
            opcodeStringArray[29] = "csc";
            opcodeStringArray[30] = "sec";
            opcodeStringArray[31] = "cot";
            opcodeStringArray[32] = "sinh";
            opcodeStringArray[33] = "cosh";
            opcodeStringArray[34] = "tanh";
            opcodeStringArray[35] = "asin";
            opcodeStringArray[36] = "acos";
            opcodeStringArray[37] = "atan";
            opcodeStringArray[38] = "hypot";
            opcodeStringArray[39] = "shiftl";
            opcodeStringArray[40] = "shiftr";
            opcodeStringArray[41] = "sqrt";
            opcodeStringArray[42] = "flr";
            opcodeStringArray[43] = "ceil";
            opcodeStringArray[44] = "trunc";
            opcodeStringArray[45] = "rnd";
            opcodeStringArray[46] = "abs";
            opcodeStringArray[47] = "deg";
            opcodeStringArray[48] = "rad";
            opcodeStringArray[49] = "fact";

            int offsetCopy = memoryOffset;
            // load the locations into the memory locations array
            for (int i = 0; i < memoryLocations.Length; i++)
            {
                memoryLocations[i] = offsetCopy;
                offsetCopy = offsetCopy + 4;
            }

            // load false for the boolean array representing 
            // if the value in the memory location is a double
            // value
            for(int i = 0; i < memoryValueIsDouble.Length; i++)
            {
                memoryValueIsDouble[i] = false;
            }

            // load the memory value array with an empty string
            for (int i = 0; i < memoryValueArray.Length; i++)
            {
                memoryValueArray[i] = "0";
            }

            // load the register value array with zeroes
            for(int i = 0; i < registerValueArray.Length; i++)
            {
                registerValueArray[i] = 0;
            }

            // load the floating point register value array with 0.0
            for(int i = 0; i < floatValueArray.Length; i++)
            {
                floatValueArray[i] = 0.0;
            }

            // load the zero register with the value 0 once on startup.
            reg0TextBox.Text = Convert.ToString(zeroRegisterValue); 

            // load the register textbox array with the register textboxes
            registerTextBoxArray[0] = reg0TextBox;
            registerTextBoxArray[1] = reg1TextBox;
            registerTextBoxArray[2] = reg2TextBox;
            registerTextBoxArray[3] = reg3TextBox;
            registerTextBoxArray[4] = reg4TextBox;
            registerTextBoxArray[5] = reg5TextBox;
            registerTextBoxArray[6] = reg6TextBox;
            registerTextBoxArray[7] = reg7TextBox;
            registerTextBoxArray[8] = reg8TextBox;
            registerTextBoxArray[9] = reg9TextBox;
            registerTextBoxArray[10] = reg10TextBox;
            registerTextBoxArray[11] = reg11TextBox;
            registerTextBoxArray[12] = reg12TextBox;
            registerTextBoxArray[13] = reg13TextBox;
            registerTextBoxArray[14] = reg14TextBox;
            registerTextBoxArray[15] = reg15TextBox;
            registerTextBoxArray[16] = reg16TextBox;
            registerTextBoxArray[17] = reg17TextBox;
            registerTextBoxArray[18] = reg18TextBox;
            registerTextBoxArray[19] = reg19TextBox;
            registerTextBoxArray[20] = reg20TextBox;
            registerTextBoxArray[21] = reg21TextBox;
            registerTextBoxArray[22] = reg22TextBox;
            registerTextBoxArray[23] = reg23TextBox;
            registerTextBoxArray[24] = reg24TextBox;
            registerTextBoxArray[25] = reg25TextBox;
            registerTextBoxArray[26] = reg26TextBox;
            registerTextBoxArray[27] = reg27TextBox;
            registerTextBoxArray[28] = reg28TextBox;
            registerTextBoxArray[29] = reg29TextBox;
            registerTextBoxArray[30] = reg30TextBox;
            registerTextBoxArray[31] = reg31TextBox;

            // load the memory textboxes into the memory textbox array
            memoryTextBoxArray[0] = memoryTextBox0;
            memoryTextBoxArray[1] = memoryTextBox1;
            memoryTextBoxArray[2] = memoryTextBox2;
            memoryTextBoxArray[3] = memoryTextBox3;
            memoryTextBoxArray[4] = memoryTextBox4;
            memoryTextBoxArray[5] = memoryTextBox5;
            memoryTextBoxArray[6] = memoryTextBox6;
            memoryTextBoxArray[7] = memoryTextBox7;
            memoryTextBoxArray[8] = memoryTextBox8;
            memoryTextBoxArray[9] = memoryTextBox9;
            memoryTextBoxArray[10] = memoryTextBox10;
            memoryTextBoxArray[11] = memoryTextBox11;
            memoryTextBoxArray[12] = memoryTextBox12;
            memoryTextBoxArray[13] = memoryTextBox13;
            memoryTextBoxArray[14] = memoryTextBox14;
            memoryTextBoxArray[15] = memoryTextBox15;
            memoryTextBoxArray[16] = memoryTextBox16;
            memoryTextBoxArray[17] = memoryTextBox17;
            memoryTextBoxArray[18] = memoryTextBox18;
            memoryTextBoxArray[19] = memoryTextBox19;
            memoryTextBoxArray[20] = memoryTextBox20;
            memoryTextBoxArray[21] = memoryTextBox21;
            memoryTextBoxArray[22] = memoryTextBox22;
            memoryTextBoxArray[23] = memoryTextBox23;
            memoryTextBoxArray[24] = memoryTextBox24;
            memoryTextBoxArray[25] = memoryTextBox25;
            memoryTextBoxArray[26] = memoryTextBox26;
            memoryTextBoxArray[27] = memoryTextBox27;
            memoryTextBoxArray[28] = memoryTextBox28;
            memoryTextBoxArray[29] = memoryTextBox29;
            memoryTextBoxArray[30] = memoryTextBox30;
            memoryTextBoxArray[31] = memoryTextBox31;

            timer1.Start();
        }

        // update the textboxes in the GUI to match the values of the registers.
        private void timer1_Tick(object sender, EventArgs e)
        {
            // update the 13 general purpose registers after the $zero register
            for(int i = 1; i < 14; i++)
            {
                registerTextBoxArray[i].Text = Convert.ToString(registerValueArray[i - 1]);
            }

            // update two floating point registers
            registerTextBoxArray[14].Text = Convert.ToString(floatValueArray[0]);
            registerTextBoxArray[15].Text = Convert.ToString(floatValueArray[1]);

            // update the general purpose registers
            for(int i = 16; i < 22; i++)
            {
                registerTextBoxArray[i].Text = Convert.ToString(registerValueArray[i - 3]);
            }

            // update the 13 general purpose registers after the $zero register
            for (int i = 22; i < 26; i++)
            {
                registerTextBoxArray[i].Text = Convert.ToString(floatValueArray[i-20]);
            }

            // update the general purpose registers
            for (int i = 26; i < 32; i++)
            {
                registerTextBoxArray[i].Text = Convert.ToString(registerValueArray[i - 7]);
            }

            // update the memory locations with their values
            for (int i = 0; i < memoryTextBoxArray.Length; i++)
            {
                memoryTextBoxArray[i].Text = memoryValueArray[i];
            }
        }

        // check wether the input string is a valid register.
        bool isValidRegister(string inputRegister)
        {
            for(int i = 0; i < registerNameStringArray.Length; i++)
            {
                if(inputRegister == registerNameStringArray[i])
                {
                    return true;
                }
            }
            return false;
        }

        // parse the script textbox. 
        private void playButton_Click(object sender, EventArgs e)
        {
            resetValues(); // reset all values to 0 in registers and memory

            translationTextBox.Clear(); // clear the translation textbox

            string commands = scriptTextBox.Text; // collect the user input

            // parse the user input
            char[] delimitingChars = { ',', '\r', '\n', ' ', '(', ')' };
            string[] words = commands.Split(delimitingChars, StringSplitOptions.RemoveEmptyEntries);

            // if the length of the script is zero, ask the user for input.
            if(words.Length == 0)
            {
                translationTextBox.Text = "Please enter code into the script textbox.";
                return;
            }

            // index used to parse the instruction strings
            parsingIndex = 0;

            // used to detect error.
            int error = 0;

            while((parsingIndex < words.Length) && (error == 0))
            {
                // call single step function
                error = singleStep(ref words, ref parsingIndex);
            }
        }

        // convert the input binary string (ranges 0-15) to hex
        char convertBinaryWordToHexChar(string inputBinaryString)
        {
            if(inputBinaryString == "0000"){ return '0'; }
            else if(inputBinaryString == "0001") { return '1'; }
            else if (inputBinaryString == "0010") { return '2'; }
            else if (inputBinaryString == "0011") { return '3'; }
            else if (inputBinaryString == "0100") { return '4'; }
            else if (inputBinaryString == "0101") { return '5'; }
            else if (inputBinaryString == "0110") { return '6'; }
            else if (inputBinaryString == "0111") { return '7'; }
            else if (inputBinaryString == "1000") { return '8'; }
            else if (inputBinaryString == "1001") { return '9'; }
            else if (inputBinaryString == "1010") { return 'a'; }
            else if (inputBinaryString == "1011") { return 'b'; }
            else if (inputBinaryString == "1100") { return 'c'; }
            else if (inputBinaryString == "1101") { return 'd'; }
            else if (inputBinaryString == "1110") { return 'e'; }
            else { return 'f'; }
        }

        // convert the input binary string (ranges 0-15) to hex
        string convertHexCharToBinaryWord(char inputHexString)
        {
            if (inputHexString == '0') { return "0000"; }
            else if (inputHexString == '1') { return "0001"; }
            else if (inputHexString == '2') { return "0010"; }
            else if (inputHexString == '3') { return "0011"; }
            else if (inputHexString == '4') { return "0100"; }
            else if (inputHexString == '5') { return "0101"; }
            else if (inputHexString == '6') { return "0110"; }
            else if (inputHexString == '7') { return "0111"; }
            else if (inputHexString == '8') { return "1000"; }
            else if (inputHexString == '9') { return "1001"; }
            else if (inputHexString == 'a') { return "1010"; }
            else if (inputHexString == 'b') { return "1011"; }
            else if (inputHexString == 'c') { return "1100"; }
            else if (inputHexString == 'd') { return "1101"; }
            else if (inputHexString == 'e') { return "1110"; }
            else { return "1111"; }
        }

        // Convert a string double to a string IEEE 32-bit floating point number (string).
        string convertDoubleToFloatingPoint(string inputDoubleString)
        {
            // convert the input string to a string builder.
            var inputDoubleStringBuilder = new StringBuilder();
            for(int i = 0; i < inputDoubleString.Length; i++)
            {
                inputDoubleStringBuilder.Append(inputDoubleString[i]);
            }

            // if it does not contain a decimal, insert one.
            bool initialDecimalFound = false;
            int index = 0;
            while((initialDecimalFound == false) && (index < inputDoubleStringBuilder.Length))
            {
                if(inputDoubleStringBuilder[index] == '.')
                {
                    initialDecimalFound = true;
                }
                index = index + 1;
            }

            // record the index of the decimal place
            int decimalIndex = 0;
            if(initialDecimalFound == true)
            {
                decimalIndex = index - 1;
            }
            else
            {
                inputDoubleStringBuilder.Append('.');
                inputDoubleStringBuilder.Append('0');
                decimalIndex = inputDoubleStringBuilder.Length - 2;
            }

            // create the fractional in decimal
            var fractionalBuilder = new StringBuilder();
            fractionalBuilder.Append('0');
            for (int i = decimalIndex; i < inputDoubleStringBuilder.Length; i++)
            {
                fractionalBuilder.Append(inputDoubleStringBuilder[i]);
            }

            // convert the fractional to a double value
            string fracString = fractionalBuilder.ToString();
            double fractionalValue = Convert.ToDouble(fracString);

            // a string builder for the final answer in binary form to be converted to hex later.
            var fractionalBinary = new StringBuilder();

            // if the fractional is 0, append that here.
            if(fractionalValue == 0)
            {
                fractionalBinary.Append('0');
            }

            // append its binary equivalent to the final answer
            while (fractionalValue != 0)
            {
                // multiply fractional by 2
                fractionalValue = fractionalValue * 2;

                // build the fractional base value
                if (fractionalValue >= 1.0)
                {
                    fractionalBinary.Append('1');
                }
                else
                {
                    fractionalBinary.Append('0');
                }

                // remove anything to the left of the decimal place
                fractionalValue = fractionalValue - Math.Truncate(fractionalValue);
            }

            // convert the input string to a double
            double inputDouble = Convert.ToDouble(inputDoubleString);
            
            // boolean value representing if the double is negative. true for negative, false for positive.
            bool isNegative = false;
            if (inputDouble < 0)
            {
                isNegative = true;
            }

            // create a string containing the entire number in base 2 form.
            var answerBaseTwo = new StringBuilder();

            // find the left half of the double, called the "integral"
            int integral = Math.Abs(Convert.ToInt32(Math.Truncate(inputDouble)));

            // convert this number to a binary string
            string integralBinary = Convert.ToString(integral, 2);

            // add it to the base 2 string.
            for (int i = 0; i < integralBinary.Length; i++)
            {
                answerBaseTwo.Append(integralBinary[i]);
            }

            // record the index of the decimal place in the string
            int decimalIndexBase2 = answerBaseTwo.Length;

            // append the decimal place
            answerBaseTwo.Append('.');

            // append the fractional 
            for(int i = 0; i < fractionalBinary.Length; i++)
            {
                answerBaseTwo.Append(fractionalBinary[i]);
            }

            /// AT THIS POINT WE HAVE IT IN BASE 2.
            /// 

            // indices representing the index of the decimal place and nearest '1' character
            int nearestOneIndex = 0;
            bool oneFound = false;

            // find the correct index of the decimal character
            while ((nearestOneIndex < answerBaseTwo.Length) && (oneFound == false))
            {
                if(answerBaseTwo[nearestOneIndex] == '1')
                {
                    oneFound = true;
                    nearestOneIndex = nearestOneIndex - 1;
                }

                nearestOneIndex = nearestOneIndex + 1;
            }

            // if there are no '1' characters in the entire base 2 representation, return 0x00000000.
            if(oneFound == false)
            {
                return ("0x00000000");
            }

            // calculate the exponent
            int exponent = 0;

            // if the truncated base 2 value is equal to 0, adjust exponent calculation
            // so that scientific notation is correct: 0.1 x 10^-3
            // else it will look like: 1.05 x 10^4
            if (Math.Truncate(Convert.ToDouble(answerBaseTwo.ToString())) == 0)
            {
                exponent = decimalIndexBase2 - nearestOneIndex;
            }
            else
            {
                exponent = decimalIndexBase2 - (nearestOneIndex + 1);
            }


            // add 127 to the exponent.
            exponent = exponent + 127;

            // convert the exponent to a binary number.
            string binaryExponent = Convert.ToString(exponent, 2);

            // create the final answer in binary
            var answerBinary = new StringBuilder();

            // if the answer should be negative, the first bit is set.
            if (isNegative)
            {
                answerBinary.Append('1');
            }
            else
            {
                answerBinary.Append('0');
            }

            // append necessary filler zeroes if binary exponent is less than 8 characters long.
            if (binaryExponent.Length < 8)
            {
                int numberOfZeroesNeeded = 8 - binaryExponent.Length;
                for (int i = 0; i < numberOfZeroesNeeded; i++)
                {
                    answerBinary.Append('0');
                }
            }

            // append the exponent to the answer
            for (int i = 0; i < binaryExponent.Length; i++)
            {
                answerBinary.Append(binaryExponent[i]);
            }

            // remove everything before the first '1' character from fractional
            while ((fractionalBinary.Length > 0) && (fractionalBinary[0] != '1'))
            {
                fractionalBinary.Remove(0, 1);
            }

            if(fractionalBinary.Length > 0)
            {
                // remove the first '1'
                fractionalBinary.Remove(0, 1);
            }


            // append the rest of the fractional to the final answer
            for (int i = 0; i < fractionalBinary.Length; i++)
            {
                answerBinary.Append(fractionalBinary[i]);
            }

            // fill in the rest of the fractional with zeroes.
            for (int i = 0; i < 23 - fractionalBinary.Length; i++)
            {
                answerBinary.Append('0');
            }

            // compute the answer in hex
            var answerHex = new StringBuilder();
            for (int i = 0; i < 8; i++)
            {
                // used to store 4 binary bits at a time
                var stringFourBinaryBits = new StringBuilder();

                // used to keep track of where we are in the long binary string
                int startingIndex = i * 4;

                // collect the next four bits in the binary string
                for (int j = startingIndex; j < startingIndex + 4; j++)
                {
                    stringFourBinaryBits.Append(answerBinary[j]);
                }

                // convert them to hexadecimal
                char hexCharacter = convertBinaryWordToHexChar(stringFourBinaryBits.ToString());

                // append the hex character to the final answer (answerHex).
                answerHex.Append(hexCharacter);
            }

            // add 0x for hex formatting
            string finalAnswer = "0x" + answerHex.ToString();

            // return the answer in hexadecimal
            return finalAnswer;
        }

        // Convert an IEEE 32-bit floating point number to a string double
        string convertFloatingPointToDouble(string inputFloatString)
        {
            // handle the case where 0 is input.
            if(inputFloatString == "0x00000000")
            {
                return ("0.0");
            }

            // binary form of input float string
            var binaryFloat = new StringBuilder();

            // remove 0x from hex string
            inputFloatString = inputFloatString.Remove(0, 2);

            // convert the hex float to binary
            for (int i = 0; i < inputFloatString.Length; i++)
            {
                // retrieve the binary representation of the hex character.
                string binaryWord = convertHexCharToBinaryWord(inputFloatString[i]);

                // append the binary word to the 32-bit version
                binaryFloat.Append(binaryWord);
            }

            int sign = 1;
            if(binaryFloat[0] == '1') 
            { 
                sign = -1; 
            }

            // calculate the fraction value
            double fractionalValue = 0.0;
            int fractionalIndex = 9; // begin counting here
            int bitCount = 1;
            while(fractionalIndex < binaryFloat.Length)
            {
                if (binaryFloat[fractionalIndex] == '1')
                {
                    fractionalValue = fractionalValue + Math.Pow(2, (-1 * bitCount));
                }

                fractionalIndex = fractionalIndex + 1;
                bitCount = bitCount + 1;
            }

            // calculate the exponent value
            double exponentValue = 0.0;
            int exponentIndex = 8;
            bitCount = 0;
            while(exponentIndex > 0)
            {
                if(binaryFloat[exponentIndex] == '1')
                {
                    exponentValue = exponentValue + Math.Pow(2, bitCount);
                }

                exponentIndex = exponentIndex - 1;
                bitCount = bitCount + 1;
            }

            // formula = (-1)^s * (1+Fraction) * 2^(exp-127)
            double finalAnswer = sign * (1 + fractionalValue) * Math.Pow(2, (exponentValue - 127));

            // return the answer in string form
            return (Convert.ToString(finalAnswer));
        }

        // reset all values to 0
        void resetValues()
        {
            // set all floating point values to 0.0
            for(int i = 0; i < floatValueArray.Length; i++)
            {
                floatValueArray[i] = 0.0;
            }

            // set all integer values to 0
            for(int i = 0; i < registerValueArray.Length; i++)
            {
                registerValueArray[i] = 0;
            }

            // set all memory values to "0"
            for(int i = 0; i < memoryValueArray.Length; i++)
            {
                memoryValueArray[i] = "0";
            }

            // set all boolean values in memory to false (non-floating point)
            for(int i = 0; i < memoryValueIsDouble.Length; i++)
            {
                memoryValueIsDouble[i] = false;
            }
        }
        
        // perform a single instruction
        private void singleStepButton_Click(object sender, EventArgs e)
        {
            //translationTextBox.Clear(); // clear the translate textbox

            string commands = scriptTextBox.Text; // collect the user input

            // parse the user input
            char[] delimitingChars = { ',', '\r', '\n', ' ', '(', ')' };
            string[] words = commands.Split(delimitingChars, StringSplitOptions.RemoveEmptyEntries);

            // if the length of the script is zero, ask the user for input.
            if (words.Length == 0)
            {
                translationTextBox.Text = "Please enter code into the script textbox.";
                return;
            }

            int error = 0; // used to detect user error

            // if the parsing index is less than the length of the instructions, perform a single instruction
            if((parsingIndex < words.Length) && (error == 0))
            {
                // call single step function
                error = singleStep(ref words, ref parsingIndex);
            }
        }
        // Perform a single command. 
        // Update the index of the opcode for the next command.
        int singleStep(ref string[] commands, ref int index)
        {
            // see if the opcode is in the opcode string array
            string opcode = "invalid";
            int arrayParse = 0;
            while((opcode == "invalid") && (arrayParse < opcodeStringArray.Length))
            {
                // if there's a match, update the opcode
                if (commands[index] == opcodeStringArray[arrayParse])
                {
                    opcode = opcodeStringArray[arrayParse];
                }

                // increase arrayParse for next iteration
                arrayParse = arrayParse + 1;
            }

            // if there was no match, inform the user.
            if (opcode == "invalid")
            {
                translationTextBox.Text += commands[index] + " is not a supported opcode.";
                return -1;
            }
            // perform the instruction.
            else
            {
                // perform the command and update the index of the next opcode.
                int error = performCommand(ref commands, ref opcode, ref index);
                return error;
            }
        }

        // call the function needed for this command
        int performCommand(ref string[] array, ref string opcode, ref int index)
        {
            // Example: readw $t0, 1000($t1)
            if (opcode == "readw")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    readw(array[index + 1], array[index + 3], array[index + 2]);
                    index = index + 4;
                }
            }
            // Example: writew $t0, 1000($t1)
            else if (opcode == "writew")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    writew(array[index + 1], array[index + 3], array[index + 2]);
                    index = index + 4;
                }
            }
            // Example: add $t0, $t1, $t2 
            else if (opcode == "add")
            {
                // if one of the registers is invalid, return.
                if(!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3])) {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    add(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: addv $t0, $t1, 123
            else if(opcode == "addv")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    addv(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: sub $t0, $t1, $t3
            else if(opcode == "sub")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    sub(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: mult $t0, $t1, $t2
            else if(opcode == "mult")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    mult(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: multv $t0, $t1, -123
            else if(opcode == "multv")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    multv(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: div $t0, $t1, $t2
            else if(opcode == "div")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    div(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: divrv $t0, $t1, 123
            else if (opcode == "divrv")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    divrv(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: divvr $t0, 123, $t1
            else if (opcode == "divvr")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    divvr(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: and $t0, $t1, $t2
            else if (opcode == "and")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    andFunc(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: or $t0, $t1, $t2
            else if (opcode == "or")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    orFunc(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: xor $t0, $t1, $t2
            else if (opcode == "xor")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    xorFunc(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: nand $t0, $t1, $t2
            else if (opcode == "nand")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    nandFunc(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: nor $t0, $t1, $t2
            else if (opcode == "nor")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    norFunc(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: not $t0, $t1
            else if (opcode == "not")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    notFunc(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: andv $t0, $t1, 1234
            else if (opcode == "andv")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    andv(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: orv $t0, $t1, 1234
            else if (opcode == "orv")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    orv(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: xorv $t0, $t1, 1234
            else if (opcode == "xorv")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    xorv(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: nandv $t0, $t1, 1234
            else if (opcode == "nandv")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    nandv(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: setlt $t0, $t1, $t2
            else if (opcode == "setlt")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    setlt(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: setlv $t0, $t1, 1234
            else if (opcode == "setltv")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    setltv(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: atan2 $t0, $t1, $t2
            else if (opcode == "atan2")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    atan2(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: rand $t0, $t1, $t2
            else if (opcode == "rand")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    rand(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: log $t0, $t1, $t2
            else if (opcode == "log")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    log(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: pow $t0, $t1, $t2
            else if (opcode == "pow")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    pow(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: sin $t0, $t1
            else if (opcode == "sin")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    sin(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: cos $t0, $t1
            else if (opcode == "cos")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    cos(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: tan $t0, $t1
            else if (opcode == "tan")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    tan(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: csc $t0, $t1
            else if (opcode == "csc")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    csc(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: sec $t0, $t1
            else if (opcode == "sec")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    sec(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: cot $t0, $t1
            else if (opcode == "cot")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    cot(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: sinh $t0, $t1
            else if (opcode == "sinh")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    sinh(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: cosh $t0, $t1
            else if (opcode == "cosh")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    cosh(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: tanh $t0, $t1
            else if (opcode == "tanh")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    tanh(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: asin $t0, $t1
            else if (opcode == "asin")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    asin(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: acos $t0, $t1
            else if (opcode == "acos")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    acos(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: atan $t0, $t1
            else if (opcode == "atan")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    atan(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: hypot $t0, $t1, $t2
            else if (opcode == "hypot")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    hypot(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: shiftl $t0, $t1, 4
            else if (opcode == "shiftl")
            {
                // if one of the registers is invalid, return.
                if ((!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2])) || (isValidRegister(array[index + 3])))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    shiftl(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: shiftr $t0, $t1, 4
            else if (opcode == "shiftr")
            {
                // if one of the registers is invalid, return.
                if ((!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2])) || (isValidRegister(array[index + 3])))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    shiftr(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: sqrt $t0, $t1
            else if (opcode == "sqrt")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    sqrt(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: flt $t0, $t1
            else if (opcode == "flr")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    flr(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: ceil $t0, $t1
            else if (opcode == "ceil")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    ceil(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: trunc $t0, $t1
            else if (opcode == "trunc")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    trunc(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: rnd $t0, $t1
            else if (opcode == "rnd")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    rnd(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: abs $t0, $t1
            else if (opcode == "abs")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    abs(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: deg $t0, $t1
            else if (opcode == "deg")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    deg(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: rad $t0, $t1
            else if (opcode == "rad")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    rad(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            // Example: fact $t0, $t1
            else if (opcode == "fact")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 2]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    fact(array[index + 1], array[index + 2]);
                    index = index + 3;
                }
            }
            else
            {
                // nothing to do here at this time.
            }

            return 0;
        }
        
        // check if two register names are valid
        bool checkTwoRegisters(ref string opcode, ref string reg1, ref string reg2)
        {
            // initialize local variables
            string rt = "invalid";
            string rs = "invalid";
            int arrayParse = 0;

            // check that the register names are valid.
            while ((arrayParse < registerNameStringArray.Length) && ((rt == "invalid") || (rs == "invalid")))
            {
                // if the register name is valid, update it to "valid"
                if (reg1 == registerNameStringArray[arrayParse])
                {
                    rt = "valid";
                }
                if (reg2 == registerNameStringArray[arrayParse])
                {
                    rs = "valid";
                }

                // increment the arrayParse for the next iteration
                arrayParse = arrayParse + 1;
            }

            // if one of the arguments are invalid, print an error message and return false.
            // else return true.
            if ((rt == "invalid") || (rs == "invalid"))
            {
                translationTextBox.Text += "\nInvalid argument found in " + opcode + " instruction";
                return false;
            }
            else
            {
                return true;
            }
        }

        // check if three register names are valid.
        bool checkThreeRegisters(ref string opcode, ref string reg1, ref string reg2, ref string reg3)
        {
            // initialize local variables
            string rt = "invalid";
            string rs = "invalid";
            string rd = "invalid";
            int arrayParse = 0;

            // check that the register names are valid.
            while((arrayParse < registerNameStringArray.Length) && ((rt == "invalid") || (rs == "invalid") || (rd == "invalid")))
            {
                // if the register name is valid, update it to "valid"
                if (reg1 == registerNameStringArray[arrayParse])
                {
                    rt = "valid";
                }
                if (reg2 == registerNameStringArray[arrayParse])
                {
                    rs = "valid";
                }
                if (reg3 == registerNameStringArray[arrayParse])
                {
                    rd = "valid";
                }

                // increment the arrayParse for the next iteration
                arrayParse = arrayParse + 1;
            }

            // if one of the arguments are invalid, print an error message and return false.
            // else return true.
            if ((rt == "invalid") || (rs == "invalid") || (rd == "invalid"))
            {
                translationTextBox.Text += "\nInvalid argument found in " + opcode + " instruction";
                return false;
            }
            else
            {
                return true;
            }
        }

        // write a value from a rt to memory
        void writew(string rt, string rs, string inputOffset)
        {
            // rs must be a non-floating point register
            if (isFloat(rs))
            {
                translationTextBox.Text += "\nSource register in readw instruction cannot be a floating point register.\r";
                return;
            }

            // convert the input offset to an integer value.
            int offset = Convert.ToInt32(inputOffset);

            // calculate address
            int address = getRegisterValue(rs) + offset;

            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 000001: Write the contents of " + rt + " to memory location " + Convert.ToString(address) + '\r';

            // if it is not a valid address, inform the user.
            if (!isMemoryLocation(address))
            {
                translationTextBox.Text += "\nThe address in writew instruction is invalid.\r";
            }
            else
            {
                // compute the index of the memory location in the memory value array
                int index = (address - memoryOffset) / 4;

                // if rt is a float, set the value to true in the boolean array
                if (isFloat(rt))
                {
                    // get the value in the floating point value array
                    double value = getFloatRegisterValue(rt);

                    // convert it to type string
                    string stringValue = Convert.ToString(value);
                    
                    // convert it to floating point string form
                    string fpForm = convertDoubleToFloatingPoint(stringValue);
                    
                    // write the fp string to the memory array
                    memoryValueArray[index] = fpForm;

                    // set the boolean value to true for this value, meaning that the string 
                    // represents a floating point value.
                    memoryValueIsDouble[index] = true;
                }
                else
                {
                    // the register rt is non-floating point
                    int value = getRegisterValue(rt);

                    // convert it to string form
                    string stringValue = Convert.ToString(value);

                    // write the string value to memory
                    memoryValueArray[index] = stringValue;

                    // set the boolean value to false for this value, meaning that the string
                    // does not represent a floating point value.
                    memoryValueIsDouble[index] = false;
                }
            }
        }

        // load the value from memory into register rt
        // the memory location is stored in rs and added to the offset.
        void readw(string rt, string rs, string inputOffset)
        {
            // rs must be a non-floating point register
            if (isFloat(rs))
            {
                translationTextBox.Text += "\nSource register in readw instruction cannot be a floating point register.\r";
                return;
            }

            // convert the input offset to an integer value.
            int offset = Convert.ToInt32(inputOffset);

            // compute address
            int address = getRegisterValue(rs) + offset;

            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 000000: Read the contents of memory location " + Convert.ToString(address) + " and write them to register " + rt + '\r';

            // if it is not a valid address, inform the user.
            if (!isMemoryLocation(address))
            {
                translationTextBox.Text += "\nThe address in readw instruction is invalid.\r";
            }
            else
            {
                // compute the index of the memory location in the memory value array
                int index = (address - memoryOffset) / 4;
                
                // retrieve the value in string form
                string value = memoryValueArray[index];

                // if the value in the memory value array represents a double type,
                // use the setFloatReg method.
                if (!isFloat(rt))
                {
                    // make sure we do not try to load a double into a non floating point register
                    if (memoryValueIsDouble[index])
                    {
                        translationTextBox.Text += "\nThe rt register in readw instruction does not match the data type in the specified memory location.\r";
                    }
                    else
                    {
                        // register is non-float and so is the value in memory.
                        int valueInt = Convert.ToInt32(value);
                        setRegisterValue(rt, valueInt);
                    }
                }
                else
                {
                    // register is float and as is value in memory
                    if (memoryValueIsDouble[index])
                    {
                        string doubleString = convertFloatingPointToDouble(value);
                        double valueDouble = Convert.ToDouble(doubleString);
                        setRegisterValue(rt, valueDouble);
                    }
                    else
                    {
                        // register is float, but value in memory is not float
                        double valueDouble = Convert.ToDouble(value);
                        setRegisterValue(rt, valueDouble);
                    }
                }
            }
        }

        // add the two registers together, and store the result in rt.
        // rt = rs + rd
        void add(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 000010: Add reg. " + rt + " = " + rs + " + " + rd + '\r';

            // initialize local variables
            double rsValue = 0.0;
            double rdValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // get the rs value and convert it to a double
            if (isFloat(rd))
            {
                rdValue = getFloatRegisterValue(rd);
            }
            else
            {
                rdValue = Convert.ToDouble(getRegisterValue(rd));
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = rsValue + rdValue;
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = Convert.ToInt32(rsValue + rdValue);
                setRegisterValue(rt, rtValueInt);
            }
        }

        // add the register with the value and store the result in rt.
        // rt = rs + value
        void addv(string rt, string rs, string value)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 000011: Add val. " + rt + " = " + rs + " + " + value + '\r';

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;
            double valueDouble = 0.0;
            Int16 valueInt16 = 0;

            // convert the string value to a double value.
            valueDouble = Convert.ToDouble(value);

            // truncate the double (remove decimal value)
            valueDouble = Math.Truncate(valueDouble);

            // convert it to an Int16 type
            valueInt16 = Convert.ToInt16(valueDouble);

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = rsValue + valueInt16;
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = Convert.ToInt32(rsValue + valueInt16);
                setRegisterValue(rt, rtValueInt);
            }
        }

        // subtract the two registers, and store the result in rt.
        // rt = rs - rd
        void sub(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 000100: Subtract reg. " + rt + " = " + rs + " - " + rd + '\r';

            // initialize local variables
            double rsValue = 0.0;
            double rdValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // get the rs value and convert it to a double
            if (isFloat(rd))
            {
                rdValue = getFloatRegisterValue(rd);
            }
            else
            {
                rdValue = Convert.ToDouble(getRegisterValue(rd));
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = rsValue - rdValue;
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = Convert.ToInt32(rsValue - rdValue);
                setRegisterValue(rt, rtValueInt);
            }
        }

        // multiply the registers. rt = rs * rd
        void mult(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 000101: Multiply reg. " + rt + " = " + rs + " * " + rd + '\r';

            // initialize local variables
            double rsValue = 0.0;
            double rdValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // get the rs value and convert it to a double
            if (isFloat(rd))
            {
                rdValue = getFloatRegisterValue(rd);
            }
            else
            {
                rdValue = Convert.ToDouble(getRegisterValue(rd));
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = rsValue * rdValue;
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = Convert.ToInt32(rsValue * rdValue);
                setRegisterValue(rt, rtValueInt);
            }
        }

        // divide the registers. rt = rs / rd
        void div(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 000111: Divide reg. " + rt + " = " + rs + " / " + rd + '\r';

            // initialize local variables
            double rsValue = 0.0;
            double rdValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // get the rs value and convert it to a double
            if (isFloat(rd))
            {
                rdValue = getFloatRegisterValue(rd);
            }
            else
            {
                rdValue = Convert.ToDouble(getRegisterValue(rd));
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = rsValue / rdValue;
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = Convert.ToInt32(rsValue / rdValue);
                setRegisterValue(rt, rtValueInt);
            }
        }

        // add the register with the value and store the result in rt.
        // rt = rs + value
        void multv(string rt, string rs, string value)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 000110: Multiply val. " + rt + " = " + rs + " * " + value + '\r';

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;
            Int16 valueInt16 = 0;

            // convert the string value to a double value.
            valueInt16 = Convert.ToInt16(value);

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = rsValue * valueInt16;
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = Convert.ToInt32(rsValue * valueInt16);
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = value / rs
        void divvr(string rt, string value, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 001001: Divide val reg. " + rt + " = " + value + " / " + rs + '\r';

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;
            Int16 valueInt16 = 0;

            // convert the string value to a double value.
            valueInt16 = Convert.ToInt16(value);

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = valueInt16 / rsValue;
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = Convert.ToInt32(valueInt16 / rsValue);
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = rs / value
        void divrv(string rt, string rs, string value)
        {
            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;
            Int16 valueInt16 = 0;

            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 001000: Divide reg val. " + rt + " = " + rs + " / " + value + '\r';

            // convert the string value to a double value.
            valueInt16 = Convert.ToInt16(value);

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = rsValue / valueInt16;
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = Convert.ToInt32(rsValue / valueInt16);
                setRegisterValue(rt, rtValueInt);
            }
        }

        // and the two registers together, and store the result in rt.
        // rt = rs & rd
        void andFunc(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 001010: And reg. " + rt + " = " + rs + " & " + rd + '\r';

            // initialize local variables
            int rsValue = 0;
            int rdValue = 0;
            double rtValue = 0.0;

            // get the rs value and convert it to an int
            if (isFloat(rs))
            {
                rsValue = Convert.ToInt32(getFloatRegisterValue(rs));
            }
            else
            {
                rsValue = getRegisterValue(rs);
            }

            // get the rd value and convert it to an int
            if (isFloat(rd))
            {
                rdValue = Convert.ToInt32(getFloatRegisterValue(rd));
            }
            else
            {
                rdValue = getRegisterValue(rd);
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = rsValue & rdValue;
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = rsValue & rdValue;
                setRegisterValue(rt, rtValueInt);
            }
        }

        // or the two registers together, and store the result in rt.
        // rt = rs | rd
        void orFunc(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 001011: Or reg. " + rt + " = " + rs + " | " + rd + '\r';

            // initialize local variables
            int rsValue = 0;
            int rdValue = 0;
            double rtValue = 0.0;

            // get the rs value and convert it to an int
            if (isFloat(rs))
            {
                rsValue = Convert.ToInt32(getFloatRegisterValue(rs));
            }
            else
            {
                rsValue = getRegisterValue(rs);
            }

            // get the rd value and convert it to an int
            if (isFloat(rd))
            {
                rdValue = Convert.ToInt32(getFloatRegisterValue(rd));
            }
            else
            {
                rdValue = getRegisterValue(rd);
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = rsValue | rdValue;
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = rsValue | rdValue;
                setRegisterValue(rt, rtValueInt);
            }
        }

        // xor the two registers together, and store the result in rt.
        // rt = rs ^ rd
        void xorFunc(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 001100: Xor reg. " + rt + " = " + rs + " ^ " + rd + '\r';

            // initialize local variables
            int rsValue = 0;
            int rdValue = 0;
            double rtValue = 0.0;

            // get the rs value and convert it to an int
            if (isFloat(rs))
            {
                rsValue = Convert.ToInt32(getFloatRegisterValue(rs));
            }
            else
            {
                rsValue = getRegisterValue(rs);
            }

            // get the rd value and convert it to an int
            if (isFloat(rd))
            {
                rdValue = Convert.ToInt32(getFloatRegisterValue(rd));
            }
            else
            {
                rdValue = getRegisterValue(rd);
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = rsValue ^ rdValue;
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = rsValue ^ rdValue;
                setRegisterValue(rt, rtValueInt);
            }
        }

        // nand the two registers together, and store the result in rt.
        // rt = rs nand rd
        void nandFunc(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 001101: Nand reg. " + rt + " = " + "~(" + rs + " & " + rd + ")\r";

            // initialize local variables
            int rsValue = 0;
            int rdValue = 0;
            double rtValueDouble = 0.0;

            // get the rs value and convert it to an int
            if (isFloat(rs))
            {
                rsValue = Convert.ToInt32(getFloatRegisterValue(rs));
            }
            else
            {
                rsValue = getRegisterValue(rs);
            }

            // get the rd value and convert it to an int
            if (isFloat(rd))
            {
                rdValue = Convert.ToInt32(getFloatRegisterValue(rd));
            }
            else
            {
                rdValue = getRegisterValue(rd);
            }

            // result of nand-ing the registers.
            int nandValue = ~(rsValue & rdValue);

            // update the double variable
            rtValueDouble = nandValue;

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // set the new register value to the double value
                setRegisterValue(rt, rtValueDouble);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                setRegisterValue(rt, nandValue);
            }
        }

        // nor the two registers together, and store the result in rt.
        // rt = rs nor rd
        void norFunc(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 001110: Nor reg. " + rt + " = " + "~(" + rs + " | " + rd + ")\r";

            // initialize local variables
            int rsValue = 0;
            int rdValue = 0;
            double rtValueDouble = 0.0;

            // get the rs value and convert it to an int
            if (isFloat(rs))
            {
                rsValue = Convert.ToInt32(getFloatRegisterValue(rs));
            }
            else
            {
                rsValue = getRegisterValue(rs);
            }

            // get the rd value and convert it to an int
            if (isFloat(rd))
            {
                rdValue = Convert.ToInt32(getFloatRegisterValue(rd));
            }
            else
            {
                rdValue = getRegisterValue(rd);
            }

            // result of nor-ing the registers.
            int norValue = ~(rsValue | rdValue);

            // update the double variable
            rtValueDouble = norValue;

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // set the new register value to the double value
                setRegisterValue(rt, rtValueDouble);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                setRegisterValue(rt, norValue);
            }
        }

        // not the two registers together, and store the result in rt.
        // rt = not(rs)
        void notFunc(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 001111: Not. " + rt + " = " + "~(" + rs + ")\r";

            // initialize local variables
            int rsValue = 0;
            double rtValueDouble = 0.0;

            // get the rs value and convert it to an int
            if (isFloat(rs))
            {
                rsValue = Convert.ToInt32(getFloatRegisterValue(rs));
            }
            else
            {
                rsValue = getRegisterValue(rs);
            }

            // result of inverting the registers.
            int notValueInt = ~rsValue;

            // update the double variable
            rtValueDouble = notValueInt;

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // set the new register value to the double value
                setRegisterValue(rt, rtValueDouble);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                setRegisterValue(rt, notValueInt);
            }
        }

        // andv the rs register and the value, and store the result in rt.
        // rt = rs andv value
        void andv(string rt, string rs, string value)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 010000: And val. " + rt + " = " + rs + " & " + value + '\r';

            // initialize local variables
            int rsValue = 0;
            int rtValue = 0;
            Int16 valueInt16 = 0;

            // convert the string value to a double value.
            valueInt16 = Convert.ToInt16(value);

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = Convert.ToInt32(getFloatRegisterValue(rs));
            }
            else
            {
                rsValue = getRegisterValue(rs);
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                double rtValueDouble = rsValue & valueInt16;
                setRegisterValue(rt, rtValueDouble);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                rtValue = rsValue & valueInt16;
                setRegisterValue(rt, rtValue);
            }
        }

        // orv the rs register and the value, and store the result in rt.
        // rt = rs orv value
        void orv(string rt, string rs, string value)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 010001: Or val. " + rt + " = " + rs + " | " + value + '\r';

            // initialize local variables
            int rsValue = 0;
            int rtValue = 0;
            Int16 valueInt16 = 0;

            // convert the string value to a double value.
            valueInt16 = Convert.ToInt16(value);

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = Convert.ToInt32(getFloatRegisterValue(rs));
            }
            else
            {
                rsValue = getRegisterValue(rs);
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                double rtValueDouble = rsValue | valueInt16;
                setRegisterValue(rt, rtValueDouble);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                rtValue = rsValue | valueInt16;
                setRegisterValue(rt, rtValue);
            }
        }

        // xorv the rs register and the value, and store the result in rt.
        // rt = rs ^ value
        void xorv(string rt, string rs, string value)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 010010: Xor val. " + rt + " = " + rs + " ^ " + value + '\r';

            // initialize local variables
            int rsValue = 0;
            int rtValue = 0;
            Int16 valueInt16 = 0;

            // convert the string value to a double value.
            valueInt16 = Convert.ToInt16(value);

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = Convert.ToInt32(getFloatRegisterValue(rs));
            }
            else
            {
                rsValue = getRegisterValue(rs);
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                double rtValueDouble = rsValue ^ valueInt16;
                setRegisterValue(rt, rtValueDouble);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                rtValue = rsValue ^ valueInt16;
                setRegisterValue(rt, rtValue);
            }
        }

        // nandv the rs register and the value, and store the result in rt.
        // rt = rs nandv value
        void nandv(string rt, string rs, string value)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 010011: Nand val. " + rt + " = " + "~(" + rs + " & " + value + ")\r";

            // initialize local variables
            int rsValue = 0;
            int rtValue = 0;
            Int16 valueInt16 = 0;

            // convert the string value to a double value.
            valueInt16 = Convert.ToInt16(value);

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = Convert.ToInt32(getFloatRegisterValue(rs));
            }
            else
            {
                rsValue = getRegisterValue(rs);
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                double rtValueDouble = ~(rsValue & valueInt16);
                setRegisterValue(rt, rtValueDouble);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                rtValue = ~(rsValue & valueInt16);
                setRegisterValue(rt, rtValue);
            }
        }

        // set rt to 1 if rs < rd. 0 otherwise.
        void setlt(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 010100: Set less than. " + rt + " = 1 if " + rs + " < " + rd + '\r';

            // initialize local variables
            double rsValue = 0.0;
            double rdValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // get the rs value and convert it to a double
            if (isFloat(rd))
            {
                rdValue = getFloatRegisterValue(rd);
            }
            else
            {
                rdValue = Convert.ToDouble(getRegisterValue(rd));
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                if(rsValue < rdValue) 
                { 
                    rtValue = 1.0; 
                }                
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = 0;
                if(rsValue < rdValue)
                {
                    rtValueInt = 1;
                }
                setRegisterValue(rt, rtValueInt);
            }
        }

        // set rt to 1 if rs < value. 0 otherwise.
        void setltv(string rt, string rs, string value)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 010101: Set less than val. " + rt + " = 1 if " + rs + " < " + value + '\r';

            // initialize local variables
            double rsValue = 0.0;
            Int16 valueInt16 = 0;
            int rtValue = 0;

            // convert the string to a 16-bit signed integer.
            valueInt16 = Convert.ToInt16(value);

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                double rtValueDouble = 0.0;
                if (rsValue < valueInt16)
                {                    
                    rtValueDouble = 1.0;
                }
                setRegisterValue(rt, rtValueDouble);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                if (rsValue < valueInt16)
                {
                    rtValue = 1;
                }
                setRegisterValue(rt, rtValue);
            }
        }

        // rt = atan2(rs, rd)
        void atan2(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 010110: Arctan2. " + rt + " = atan2(" + rs + "/" + rd + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;
            double rdValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // get the rd value and convert it to a double
            if (isFloat(rd))
            {
                rdValue = getFloatRegisterValue(rd);
            }
            else
            {
                rdValue = Convert.ToDouble(getRegisterValue(rd));
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                rtValue = Math.Atan2(rsValue, rdValue);
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                int rtValueInt = Convert.ToInt32(Math.Atan2(rsValue, rdValue));
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = random number between rs and rd. 
        // inclusive.
        void rand(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 010111: Random. " + rt + " = a random number between " + rs + " and " + rd + '\r';

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;
            double rdValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // get the rd value and convert it to a double
            if (isFloat(rd))
            {
                rdValue = getFloatRegisterValue(rd);
            }
            else
            {
                rdValue = Convert.ToDouble(getRegisterValue(rd));
            }

            // create an instance of the Random class.
            var random = new Random();

            // generate a random number in the desired range
            rtValue = random.Next(Convert.ToInt32(rsValue), Convert.ToInt32(rdValue));

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // generate a random decimal number between 0.0 and 1.0
                double randomDecimal = random.NextDouble();
                
                // multiply the random decimal number
                double rtValueNew = rtValue * randomDecimal;
                
                // update the value of the register
                setRegisterValue(rt, rtValueNew);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = log base_rs (rd). 
        void log(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011000: Logarithmic. " + rt + " = log base " + rs + " of " + rd + '\r';

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;
            double rdValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // get the rd value and convert it to a double
            if (isFloat(rd))
            {
                rdValue = getFloatRegisterValue(rd);
            }
            else
            {
                rdValue = Convert.ToDouble(getRegisterValue(rd));
            }

            // calculate the log of rd to the base rs
            rtValue = Math.Log(rdValue, rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = rs raised to the power of rd. 
        void pow(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011001: Power. " + rt + " = " + rs + " raised to the power " + rd + '\r';

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;
            double rdValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // get the rd value and convert it to a double
            if (isFloat(rd))
            {
                rdValue = getFloatRegisterValue(rd);
            }
            else
            {
                rdValue = Convert.ToDouble(getRegisterValue(rd));
            }

            // calculate the rs raised to the rd power
            rtValue = Math.Pow(rsValue, rdValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = sin(rs)
        void sin(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x00: Sine. " + rt + " = sin(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the sine of rs
            rtValue = Math.Sin(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = cos(rs)
        void cos(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x01 : Cosine. " + rt + " = cos(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the cosine of rs
            rtValue = Math.Cos(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = tan(rs)
        void tan(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x02 : Tangent. " + rt + " = tan(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the tangent of rs
            rtValue = Math.Tan(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = csc(rs)
        void csc(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x03 : Cosecant. " + rt + " = csc(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the cosecant of rs
            rtValue = Math.Sin(rsValue);
            rtValue = 1 / rtValue;

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = sec(rs)
        void sec(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x04 : Secant. " + rt + " = sec(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the secant of rs
            rtValue = Math.Cos(rsValue);
            rtValue = 1 / rtValue;

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = cot(rs)
        void cot(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x05 : Cotangent. " + rt + " = cot(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the cotangent of rs
            rtValue = Math.Tan(rsValue);
            rtValue = 1 / rtValue;

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = sinh(rs)
        void sinh(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x06 : Hyperbolic sine. " + rt + " = sinh(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the sineh of rs
            rtValue = Math.Sinh(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = cosh(rs)
        void cosh(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x07 : Hyperbolic cosine. " + rt + " = cosh(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the hyperbolic cosine of rs
            rtValue = Math.Cosh(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = tanh(rs)
        void tanh(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x08 : Hyperbolic tangent. " + rt + " = tanh(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the hyperbolic tangent of rs
            rtValue = Math.Tanh(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = asin(rs)
        void asin(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x09 : arcsine. " + rt + " = asin(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the arcsine of rs
            rtValue = Math.Asin(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = acos(rs)
        void acos(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x0a : arccosine. " + rt + " = acos(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the arccosine of rs
            rtValue = Math.Acos(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = atan(rs)
        void atan(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x0b : arctangent. " + rt + " = atan(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the arctangent of rs
            rtValue = Math.Atan(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = sqrt(rs^2 + rd^2)
        void hypot(string rt, string rs, string rd)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011010: Hypotenuse. " + rt + " = sqrt((" + rs + "^2) + (" + rd + "^2))\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;
            double rdValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // get the rd value and convert it to a double
            if (isFloat(rd))
            {
                rdValue = getFloatRegisterValue(rd);
            }
            else
            {
                rdValue = Convert.ToDouble(getRegisterValue(rd));
            }

            // calculate the hypotenuse
            rtValue = Math.Sqrt(Math.Pow(rsValue, 2) + Math.Pow(rdValue, 2));

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // convert the random double to an integer
                int rtValueInt = Convert.ToInt32(rtValue);

                // update the register value.
                setRegisterValue(rt, rtValueInt);
            }
        }

        // rt = rs << shiftAmount
        void shiftl(string rt, string rs, string shiftAmount)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011100: Shift left. " + rt + " = " + rs + " << " + shiftAmount + '\r';

            // initialize local variables
            double rsValue = 0.0;
            UInt16 valueInt16 = 0;
            int rtValue = 0;

            // convert the string to a 16-bit signed integer.
            valueInt16 = Convert.ToUInt16(shiftAmount);

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the rt value
            rtValue = Convert.ToInt32(rsValue) << valueInt16;

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                setRegisterValue(rt, Convert.ToDouble(rtValue));
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                setRegisterValue(rt, rtValue);
            }
        }

        // rt = rs >> shiftAmount
        void shiftr(string rt, string rs, string shiftAmount)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011011: Shift right. " + rt + " = " + rs + " >> " + shiftAmount + '\r';

            // initialize local variables
            double rsValue = 0.0;
            UInt16 valueInt16 = 0;
            int rtValue = 0;

            // convert the string to a 16-bit signed integer.
            valueInt16 = Convert.ToUInt16(shiftAmount);

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the rt value
            rtValue = Convert.ToInt32(rsValue) >> valueInt16;

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                setRegisterValue(rt, Convert.ToDouble(rtValue));
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                setRegisterValue(rt, rtValue);
            }
        }

        // rt = sqrt(rs)
        void sqrt(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x0c : Squareroot. " + rt + " = sqrt(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the squareroot of rs
            rtValue = Math.Sqrt(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // update the register value.
                setRegisterValue(rt, Convert.ToInt32(rtValue));
            }
        }

        // rt = floor(rs)
        void flr(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x0d : Floor. " + rt + " = flr(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the floor of rs
            rtValue = Math.Floor(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // update the register value.
                setRegisterValue(rt, Convert.ToInt32(rtValue));
            }
        }

        // rt = ceiling(rs)
        void ceil(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x0e : Ceiling. " + rt + " = ceil(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the ceiling of rs
            rtValue = Math.Ceiling(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // update the register value.
                setRegisterValue(rt, Convert.ToInt32(rtValue));
            }
        }

        // rt = truncate(rs)
        void trunc(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x0f : Truncate. " + rt + " = trunc(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the truncate of rs
            rtValue = Math.Truncate(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // update the register value.
                setRegisterValue(rt, Convert.ToInt32(rtValue));
            }
        }

        // rt = round(rs)
        void rnd(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x10 : Round. " + rt + " = rnd(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the round of rs
            rtValue = Math.Round(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // update the register value.
                setRegisterValue(rt, Convert.ToInt32(rtValue));
            }
        }

        // rt = absolute value(rs)
        void abs(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x11 : Absolute Value. " + rt + " = abs(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the absolute value of rs
            rtValue = Math.Abs(rsValue);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // update the register value.
                setRegisterValue(rt, Convert.ToInt32(rtValue));
            }
        }

        // rt = degrees(rs)
        void deg(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x12 : Degrees. " + rt + " = deg(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the degrees of rs
            rtValue = rsValue * (180/Math.PI);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // update the register value.
                setRegisterValue(rt, Convert.ToInt32(rtValue));
            }
        }

        // rt = radians(rs)
        void rad(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x13 : Radians. " + rt + " = rad(" + rs + ")\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the radians of rs
            rtValue = rsValue * (Math.PI/180);

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // update the register value.
                setRegisterValue(rt, Convert.ToInt32(rtValue));
            }
        }

        // rt = !rs
        void fact(string rt, string rs)
        {
            // write the instruction to the translation text box
            translationTextBox.Text += "\nOpcode 011101, FC: 0x14 : Factorial. " + rt + " = (" + rs + ")!\r";

            // initialize local variables
            double rsValue = 0.0;
            double rtValue = 0.0;

            // get the rs value and convert it to a double
            if (isFloat(rs))
            {
                rsValue = getFloatRegisterValue(rs);
            }
            else
            {
                rsValue = Convert.ToDouble(getRegisterValue(rs));
            }

            // calculate the degrees of rs
            rtValue = 1.0;
            
            // use a while loop
            double copy = rsValue;
            while(copy > 0)
            {
                rtValue = rtValue * copy;
                copy = copy - 1;
            }

            // if the register is a floating point register, use a floating point value
            if (isFloat(rt))
            {
                // update the value of the register
                setRegisterValue(rt, rtValue);
            }
            // if rt is not a floating point register, use an integer value.
            else
            {
                // update the register value.
                setRegisterValue(rt, Convert.ToInt32(rtValue));
            }
        }

        // the input string is a register name. 
        // return true if it is a floating point register. false if not.
        bool isFloat(string strInput)
        {
            if ((strInput == "$f0") || (strInput == "$f1") || (strInput == "$f2") || (strInput == "$f3")||(strInput == "$f4")||(strInput == "$f5"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        // check if the memory location is valid. True for valid, false for invalid.
        bool isMemoryLocation(int memoryLocation)
        {
            for(int i = 0; i < memoryLocations.Length; i++)
            {
                if(memoryLocation == memoryLocations[i])
                {
                    return true;
                }
            }
            return false;
        }

        int getRegisterValue(string registerName)
        {
            if(registerName == "$zero")
            {
                return zeroRegisterValue;
            }
            else if(registerName == "$at")
            {
                return registerValueArray[0];
            }
            else if(registerName == "$v0")
            {
                return registerValueArray[1];
            }
            else if(registerName == "$v1")
            {
                return registerValueArray[2];
            }
            else if (registerName == "$a0")
            {
                return registerValueArray[3];
            }
            else if (registerName == "$a1")
            {
                return registerValueArray[4];
            }
            else if (registerName == "$a2")
            {
                return registerValueArray[5];
            }
            else if (registerName == "$a3")
            {
                return registerValueArray[6];
            }
            else if (registerName == "$t0")
            {
                return registerValueArray[7];
            }
            else if (registerName == "$t1")
            {
                return registerValueArray[8];
            }
            else if (registerName == "$t2")
            {
                return registerValueArray[9];
            }
            else if (registerName == "$t3")
            {
                return registerValueArray[10];
            }
            else if (registerName == "$t4")
            {
                return registerValueArray[11];
            }
            else if (registerName == "$t5")
            {
                return registerValueArray[12];
            }
            else if (registerName == "$s0")
            {
                return registerValueArray[13];
            }
            else if (registerName == "$s1")
            {
                return registerValueArray[14];
            }
            else if (registerName == "$s2")
            {
                return registerValueArray[15];
            }
            else if (registerName == "$s3")
            {
                return registerValueArray[16];
            }
            else if (registerName == "$s4")
            {
                return registerValueArray[17];
            }
            else if (registerName == "$s5")
            {
                return registerValueArray[18];
            }
            else if (registerName == "$k0")
            {
                return registerValueArray[19];
            }
            else if (registerName == "$k1")
            {
                return registerValueArray[20];
            }
            else if (registerName == "$gp")
            {
                return registerValueArray[21];
            }
            else if (registerName == "$sp")
            {
                return registerValueArray[22];
            }
            else if (registerName == "$fp")
            {
                return registerValueArray[23];
            }
            else if (registerName == "$ra")
            {
                return registerValueArray[24];
            }
            else
            {
                translationTextBox.Text += "Register " + registerName + " does not exist.";
                return 0;
            }
        }

        double getFloatRegisterValue(string registerName)
        {
            if(registerName == "$f0")
            {
                return floatValueArray[0];
            }
            else if(registerName == "$f1")
            {
                return floatValueArray[1];
            }
            else if(registerName == "$f2")
            {
                return floatValueArray[2];
            }
            else if (registerName == "$f3")
            {
                return floatValueArray[3];
            }
            else if (registerName == "$f4")
            {
                return floatValueArray[4];
            }
            else if (registerName == "$f5")
            {
                return floatValueArray[5];
            }
            else
            {
                translationTextBox.Text += "Register " + registerName + " does not exist.";
                return 0;
            }
        }

        void setRegisterValue(string registerName, int value)
        {
            if (registerName == "$zero")
            {
                return;
            }
            else if (registerName == "$at")
            {
                registerValueArray[0] = value;
            }
            else if (registerName == "$v0")
            {
                registerValueArray[1] = value;
            }
            else if (registerName == "$v1")
            {
                registerValueArray[2] = value;
            }
            else if (registerName == "$a0")
            {
                registerValueArray[3] = value;
            }
            else if (registerName == "$a1")
            {
                registerValueArray[4] = value;
            }
            else if (registerName == "$a2")
            {
                registerValueArray[5] = value;
            }
            else if (registerName == "$a3")
            {
                registerValueArray[6] = value;
            }
            else if (registerName == "$t0")
            {
                registerValueArray[7] = value;
            }
            else if (registerName == "$t1")
            {
                registerValueArray[8] = value;
            }
            else if (registerName == "$t2")
            {
                registerValueArray[9] = value;
            }
            else if (registerName == "$t3")
            {
                registerValueArray[10] = value;
            }
            else if (registerName == "$t4")
            {
                registerValueArray[11] = value;
            }
            else if (registerName == "$t5")
            {
                registerValueArray[12] = value;
            }
            else if (registerName == "$s0")
            {
                registerValueArray[13] = value;
            }
            else if (registerName == "$s1")
            {
                registerValueArray[14] = value;
            }
            else if (registerName == "$s2")
            {
                registerValueArray[15] = value;
            }
            else if (registerName == "$s3")
            {
                registerValueArray[16] = value;
            }
            else if (registerName == "$s4")
            {
                registerValueArray[17] = value;
            }
            else if (registerName == "$s5")
            {
                registerValueArray[18] = value;
            }
            else if (registerName == "$k0")
            {
                registerValueArray[19] = value;
            }
            else if (registerName == "$k1")
            {
                registerValueArray[20] = value;
            }
            else if (registerName == "$gp")
            {
                registerValueArray[21] = value;
            }
            else if (registerName == "$sp")
            {
                registerValueArray[22] = value;
            }
            else if (registerName == "$fp")
            {
                registerValueArray[23] = value;
            }
            else if (registerName == "$ra")
            {
                registerValueArray[24] = value;
            }
            else
            {
                translationTextBox.Text += "Register " + registerName + " does not exist.";
                return;
            }
        }

        // set the register value of the double (floating-point) register
        void setRegisterValue(string registerName, double value)
        {
            if (registerName == "$f0")
            {
                floatValueArray[0] = value;
            }
            else if (registerName == "$f1")
            {
                floatValueArray[1] = value;
            }
            else if (registerName == "$f2")
            {
                floatValueArray[2] = value;
            }
            else if (registerName == "$f3")
            {
                floatValueArray[3] = value;
            }
            else if (registerName == "$f4")
            {
                floatValueArray[4] = value;
            }
            else if (registerName == "$f5")
            {
                floatValueArray[5] = value;
            }
            else
            {
                translationTextBox.Text += "Register " + registerName + " does not exist.";
                // nothing to do in this case.
            }
        }

    }
}
