using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FinalExam
{
    public partial class FinalExam : Form
    {
        // create a struct for an instruction
        struct Instruction
        {
            public string opcode;
            public string rt;
            public string rs;
            public string rd;
        }

        // create a global variable that counts the total number of instructions executed thus far.
        // used to create spacing in timing diagram.
        int numberOfInstructionsExecuted = 0;

        // create a global variable that counts the current instruction cycle thus far.
        int cycleNumber = 0;

        // array holding the previous instruction's timing sequence
        char[] prevTimingSequence = new char[7];

        string[] registerNameStringArray = new string[32]; // an array containing the register strings
        string[] opcodeStringArray = new string[4]; // an array holding all 4 op-codes
        int parsingIndex = 0; // index used to parse commands

        // array containing the last instruction executed
        Instruction lastInstruction = new Instruction();

        // array containing the second to last instruction executed
        Instruction secondToLastInstruction = new Instruction();

        // an array of arrays
        TextBox[][] commandsArr = new TextBox[10][];

        public FinalExam()
        {
            InitializeComponent();
        }

        // loader function called once on startup
        private void FinalExam_Load(object sender, EventArgs e)
        {
            // load the textboxes into the array of textbox arrays.
            commandsArr[0] = new TextBox[] { textBox0, textBox1, textBox2, textBox3, textBox4, textBox5, textBox6, textBox7, textBox8, textBox9, textBox10, textBox11, textBox12, textBox13, textBox14, textBox15, textBox16, textBox17, textBox18, textBox19, textBox20, textBox21, textBox22, textBox23, textBox24, textBox25, textBox26, textBox27, textBox28, textBox29, textBox30, textBox31 };
            commandsArr[1] = new TextBox[] { textBox32, textBox33, textBox34, textBox35, textBox36, textBox37, textBox38, textBox39, textBox40, textBox41, textBox42, textBox43, textBox44, textBox45, textBox46, textBox47, textBox48, textBox49, textBox50, textBox51, textBox52, textBox53, textBox54, textBox55, textBox56, textBox57, textBox58, textBox59, textBox60, textBox61, textBox62, textBox63 };
            commandsArr[2] = new TextBox[] { textBox64, textBox65, textBox66, textBox67, textBox68, textBox69, textBox70, textBox71, textBox72, textBox73, textBox74, textBox75, textBox76, textBox77, textBox78, textBox79, textBox80, textBox81, textBox82, textBox83, textBox84, textBox85, textBox86, textBox87, textBox88, textBox89, textBox90, textBox91, textBox92, textBox93, textBox94, textBox95 };
            commandsArr[3] = new TextBox[] { textBox96, textBox97, textBox98, textBox99, textBox100, textBox101, textBox102, textBox103, textBox104, textBox105, textBox106, textBox107, textBox108, textBox109, textBox110, textBox111, textBox112, textBox113, textBox114, textBox115, textBox116, textBox117, textBox118, textBox119, textBox120, textBox121, textBox122, textBox123, textBox124, textBox125, textBox126, textBox127 };
            commandsArr[4] = new TextBox[] { textBox128, textBox129, textBox130, textBox131, textBox132, textBox133, textBox134, textBox135, textBox136, textBox137, textBox138, textBox139, textBox140, textBox141, textBox142, textBox143, textBox144, textBox145, textBox146, textBox147, textBox148, textBox149, textBox150, textBox151, textBox152, textBox153, textBox154, textBox155, textBox156, textBox157, textBox158, textBox159 };
            commandsArr[5] = new TextBox[] { textBox160, textBox161, textBox162, textBox163, textBox164, textBox165, textBox166, textBox167, textBox168, textBox169, textBox170, textBox171, textBox172, textBox173, textBox174, textBox175, textBox176, textBox177, textBox178, textBox179, textBox180, textBox181, textBox182, textBox183, textBox184, textBox185, textBox186, textBox187, textBox188, textBox189, textBox190, textBox191 };
            commandsArr[6] = new TextBox[] { textBox192, textBox193, textBox194, textBox195, textBox196, textBox197, textBox198, textBox199, textBox200, textBox201, textBox202, textBox203, textBox204, textBox205, textBox206, textBox207, textBox208, textBox209, textBox210, textBox211, textBox212, textBox213, textBox214, textBox215, textBox216, textBox217, textBox218, textBox219, textBox220, textBox221, textBox222, textBox223 };
            commandsArr[7] = new TextBox[] { textBox224, textBox225, textBox226, textBox227, textBox228, textBox229, textBox230, textBox231, textBox232, textBox233, textBox234, textBox235, textBox236, textBox237, textBox238, textBox239, textBox240, textBox241, textBox242, textBox243, textBox244, textBox245, textBox246, textBox247, textBox248, textBox249, textBox250, textBox251, textBox252, textBox253, textBox254, textBox255 };
            commandsArr[8] = new TextBox[] { textBox256, textBox257, textBox258, textBox259, textBox260, textBox261, textBox262, textBox263, textBox264, textBox265, textBox266, textBox267, textBox268, textBox269, textBox270, textBox271, textBox272, textBox273, textBox274, textBox275, textBox276, textBox277, textBox278, textBox279, textBox280, textBox281, textBox282, textBox283, textBox284, textBox285, textBox286, textBox287 };
            commandsArr[9] = new TextBox[] { textBox288, textBox289, textBox290, textBox291, textBox292, textBox293, textBox294, textBox295, textBox296, textBox297, textBox298, textBox299, textBox300, textBox301, textBox302, textBox303, textBox304, textBox305, textBox306, textBox307, textBox308, textBox309, textBox310, textBox311, textBox312, textBox313, textBox314, textBox315, textBox316, textBox317, textBox318, textBox319 };

            // enable provide solution check box.
            provideSolutionCheckBox.Enabled = true;

            // disable enable forwarding unit checkbox.
            enableForwardingUnitCheckBox.Enabled = false;

            // load the first element of the previous timing sequence with an empty character
            prevTimingSequence[0] = ' ';

            // load the opcode of the last instruction executed with an empty string
            lastInstruction.opcode = "";

            // load the opcode of the 2nd to last instruction executed with an empty string
            secondToLastInstruction.opcode = "";

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
            registerNameStringArray[14] = "$t6";
            registerNameStringArray[15] = "$t7";
            registerNameStringArray[16] = "$s0";
            registerNameStringArray[17] = "$s1";
            registerNameStringArray[18] = "$s2";
            registerNameStringArray[19] = "$s3";
            registerNameStringArray[20] = "$s4";
            registerNameStringArray[21] = "$s5";
            registerNameStringArray[22] = "$s6";
            registerNameStringArray[23] = "$s7";
            registerNameStringArray[24] = "$t8";
            registerNameStringArray[25] = "$t9";
            registerNameStringArray[26] = "$k0";
            registerNameStringArray[27] = "$k1";
            registerNameStringArray[28] = "$gp";
            registerNameStringArray[29] = "$sp";
            registerNameStringArray[30] = "$fp";
            registerNameStringArray[31] = "$ra";

            // load the opcodes into the opcode string array
            opcodeStringArray[0] = "add";
            opcodeStringArray[1] = "sub";
            opcodeStringArray[2] = "lw";
            opcodeStringArray[3] = "sw";
        }

        // the user pressed the play button
        private void playButton_Click(object sender, EventArgs e)
        {
            reset(); // reset the settings for a new execution.

            // collect the user input
            string commands = scriptTextBox.Text; 

            // parse the user input
            char[] delimitingChars = { ',', '\r', '\n', ' ', '(', ')' };
            string[] words = commands.Split(delimitingChars, StringSplitOptions.RemoveEmptyEntries);

            // if the length of the script is zero, ask the user for input.
            if (words.Length == 0)
            {
                translationTextBox.Text = "Please enter code into the script textbox.";
                return;
            }

            // used to detect error.
            int error = 0;

            while ((parsingIndex < words.Length) && (error == 0))
            {
                // call single step function
                error = singleStep(ref words, ref parsingIndex);
            }
        }

        private void singleStepButton_Click(object sender, EventArgs e)
        {
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

            // if executing the first command, reset the spacing and the cycle parameters.
            if(parsingIndex == 0)
            {
                numberOfInstructionsExecuted = 0;
                cycleNumber = 0;
            }

            // if the parsing index is less than the length of the instructions, perform a single instruction
            if ((parsingIndex < words.Length) && (error == 0))
            {
                // call single step function
                error = singleStep(ref words, ref parsingIndex);
            }
        }

        // Perform a single command. 
        // Update the index of the opcode for the next command.
        int singleStep(ref string[] commands, ref int index)
        {
            // if the number of commands executed thus far exceeds 
            // the maximum number of commands supported, return here.
            if(numberOfInstructionsExecuted >= commandsArr.Length)
            {
                return -1;
            }

            // see if the opcode is in the opcode string array
            string opcode = "invalid";
            int arrayParse = 0;
            while ((opcode == "invalid") && (arrayParse < opcodeStringArray.Length))
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
                return -2;
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
            // Example: lw $t0, 1000($t1)
            if (opcode == "lw")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the load word function and update the index for the next instruction
                    loadWord(array[index + 1], array[index + 3], array[index + 2]);
                    index = index + 4;
                }
            }
            // Example: writew $t0, 1000($t1)
            else if (opcode == "sw")
            {
                // if one of the registers is invalid, return.
                if (!checkTwoRegisters(ref array[index], ref array[index + 1], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the store word function and update the index for the next instruction
                    storeWord(array[index + 1], array[index + 3], array[index + 2]);
                    index = index + 4;
                }
            }
            // Example: add $t0, $t1, $t2 
            else if (opcode == "add")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the add function and update the index for the next instruction
                    add(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            // Example: sub $t0, $t1, 123
            else if (opcode == "sub")
            {
                // if one of the registers is invalid, return.
                if (!checkThreeRegisters(ref array[index], ref array[index + 1], ref array[index + 2], ref array[index + 3]))
                {
                    return -1;
                }
                else
                {
                    // call the subtract function and update the index for the next instruction
                    sub(array[index + 1], array[index + 2], array[index + 3]);
                    index = index + 4;
                }
            }
            else
            {
                // nothing to do at this time
            }

            // increment the number of instructions executed up to this point and return 0 (success).
            numberOfInstructionsExecuted = numberOfInstructionsExecuted + 1;

            // increment the cycle number for the next command.
            cycleNumber = cycleNumber + 1;

            // return zero (success).
            return 0;
        }

        // write a value from rt to memory
        void storeWord(string rt, string rs, string inputOffset)
        {
            // if the provide solutions checkbox is not checked, print the details of the instruction.
            // No timing diagram is generated in this case.
            if (!provideSolutionCheckBox.Checked)
            {
                // write the instruction to the translation text box
                translationTextBox.Text += "\nOpcode 01: Write the contents of " + rt + " to memory location (" + rs + " + " + inputOffset + ")\r";
            }

            string opcode = "sw";
            string emptyString = "";

            // check for data dependencies.
            checkDataDependencies(ref opcode, ref rt, ref rs, ref emptyString);

        }

        // load the value from memory into register rt
        // the memory location is stored in rs and added to the offset.
        void loadWord(string rt, string rs, string inputOffset)
        {
            // if the provide solutions checkbox is not checked, print the details of the instruction.
            // No timing diagram is generated in this case.
            if (!provideSolutionCheckBox.Checked)
            {
                // write the instruction to the translation text box
                translationTextBox.Text += "\nOpcode 00: Read the contents of memory location (" + rs + " + " + inputOffset + ") and write them to register " + rt + '\r';
            }

            string opcode = "lw";
            string emptyString = "";
            
            // check for data dependencies.
            checkDataDependencies(ref opcode, ref rt, ref rs, ref emptyString);
        }

        // add the two registers together, and store the result in rt.
        // rt = rs + rd
        void add(string rt, string rs, string rd)
        {
            // if the provide solutions checkbox is not checked, print the details of the instruction.
            // No timing diagram is generated in this case.
            if (!provideSolutionCheckBox.Checked)
            {
                // write the instruction to the translation text box
                translationTextBox.Text += "\nOpcode 10: Add reg. " + rt + " = " + rs + " + " + rd + '\r';
            }

            string opcode = "add";

            // check for data dependencies.
            checkDataDependencies(ref opcode, ref rt, ref rs, ref rd);
        }

        // subtract the two registers, and store the result in rt.
        // rt = rs - rd
        void sub(string rt, string rs, string rd)
        {
            // if the provide solutions checkbox is not checked, print the details of the instruction.
            // No timing diagram is generated in this case.
            if (!provideSolutionCheckBox.Checked)
            {
                // write the instruction to the translation text box
                translationTextBox.Text += "\nOpcode 11: Subtract reg. " + rt + " = " + rs + " - " + rd + '\r';
            }

            string opcode = "sub";

            // check for data dependencies.
            checkDataDependencies(ref opcode, ref rt, ref rs, ref rd);
        }

        // check for data dependencies
        void checkDataDependencies(ref string opcode, ref string rt, ref string rs, ref string rd)
        {
            // string holding correct answer based on data dependencies.
            string answer = "FDXMW";

            // check for all possible data dependencies for load word command
            if (opcode == "lw")
            {
                // Example data dependency:
                // add $s2, $t0, $t1
                // lw $t2, 0($s2)

                // data dependency with previous command
                if (((lastInstruction.opcode == "add")||(lastInstruction.opcode == "sub")) && (rs == lastInstruction.rt))
                {
                    // checkbox is checked. Provide solution.
                    if (provideSolutionCheckBox.Checked)
                    {
                        // if the forwarding unit is enabled, do not insert stall cycles.
                        if (!enableForwardingUnitCheckBox.Checked)
                        {
                            answer = "FSSDXMW";
                        }
                    }

                    // checkbox not checked. Simply report the dependency to the user.
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rs + " cannot be used as rs in lw and rt in previous instruction (add/sub)\r"; 
                    }
                }

                // Example data dependency:
                // lw $s2, 0($t0)
                // lw $t1, 0($s2)

                // data dependency with previous command
                else if ((lastInstruction.opcode == "lw") && (rs == lastInstruction.rt))
                {
                    // checkbox is checked. Provide solution.
                    if (provideSolutionCheckBox.Checked)
                    {
                        // if the forwarding unit is enabled, only insert one stall cycle.
                        if (!enableForwardingUnitCheckBox.Checked)
                        {
                            answer = "FSSDXMW";
                        }
                        else
                        {
                            answer = "FDSXMW";
                        }
                    }

                    // checkbox not checked. Simply report the dependency to the user.
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rs + " cannot be used as rs in lw and rt in previous lw instruction\r";
                    }
                }

                // Example data dependency:
                // add $s2, $t0, $t1
                // add $t4, $t5, $t6
                // lw $t2, 0($s2)
                //
                // Only needs one stall cycle if not using forwarding unit.
                // if the second to last instruction was an add or sub and the forwarding unit is disabled and the previous instruction did not have a stall cycle.
                else if ((rs == secondToLastInstruction.rt) && (!enableForwardingUnitCheckBox.Checked) && (!prevInstructionHasStall()) && ((secondToLastInstruction.opcode == "add") || (secondToLastInstruction.opcode == "sub")))
                {
                    if (provideSolutionCheckBox.Checked)
                    {
                        answer = "FSDXMW";
                    }
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rs + " cannot be used as rs in lw and rt in 2 instructions previous (add/sub)\r";
                    }
                }

                // Example data dependency:
                // lw $s2, 0($t0)
                // add $t4, $t5, $t6
                // lw $t1, 0($s2)
                //
                // if the second to last instruction was an add or sub and the forwarding unit is disabled and the previous instruction did not have a stall cycle.
                else if ((rs == secondToLastInstruction.rt) && (!enableForwardingUnitCheckBox.Checked) && (!prevInstructionHasStall()) && (secondToLastInstruction.opcode == "lw"))
                {
                    if (provideSolutionCheckBox.Checked)
                    {
                        answer = "FSDXMW";
                    }
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rs + " cannot be used as rs in lw and rt in lw 2 instructions previous.\r";
                    }
                }

                else
                {
                    // nothing to do at this time.
                }
            }

            // check for all possible data dependencies for add/sub commands
            else if ((opcode == "add")||(opcode == "sub"))
            {
                // Example data dependency:
                // lw $s2, 0($t0)
                // add $t1, $s2, $t2

                // data dependency with previous command
                if ((lastInstruction.opcode == "lw") && ((rs == lastInstruction.rt) || (rd == lastInstruction.rt)))
                {
                    // checkbox is checked. Provide solution.
                    if (provideSolutionCheckBox.Checked)
                    {
                        // if the forwarding unit is enabled, do not insert stall cycles.
                        if (!enableForwardingUnitCheckBox.Checked)
                        {
                            answer = "FSSDXMW";
                        }
                        else
                        {
                            answer = "FDSXMW";
                        }
                    }

                    // checkbox not checked. Simply report the dependency to the user.
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + lastInstruction.rt + " cannot be used as argument in add/sub when used as rt in previous lw instruction\r";
                    }
                }

                // Example data dependency:
                // add $s2, $t0, $t1
                // add $t2, $s2, $t3

                // data dependency with previous command
                else if (((lastInstruction.opcode == "add") || (lastInstruction.opcode == "sub")) && ((rs == lastInstruction.rt) || (rd == lastInstruction.rt)))
                {
                    // checkbox is checked. Provide solution.
                    if (provideSolutionCheckBox.Checked)
                    {
                        // if the forwarding unit is enabled, only insert one stall cycle.
                        if (!enableForwardingUnitCheckBox.Checked)
                        {
                            answer = "FSSDXMW";
                        }
                    }

                    // checkbox not checked. Simply report the dependency to the user.
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + lastInstruction.rt + " cannot be used as an argument in add/sub because it was used as rt in previous instruction\r";
                    }
                }

                // Example data dependency:
                // lw $s2, 0($t0)
                // add $t4, $t5, $t6
                // add $t1, $s2, $t2
                //
                // Only needs one stall cycle if not using forwarding unit.
                // if the second to last instruction was an add or sub and the forwarding unit is disabled and the previous instruction did not have a stall cycle.
                else if (((rs == secondToLastInstruction.rt) || rd == secondToLastInstruction.rt) && (!enableForwardingUnitCheckBox.Checked) && (!prevInstructionHasStall()) && ((secondToLastInstruction.opcode == "lw")))
                {
                    if (provideSolutionCheckBox.Checked)
                    {
                        answer = "FSDXMW";
                    }
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + secondToLastInstruction.rt + " cannot be used as an argument in add/sub when it was used as rt in lw 2 instructions previous.\r";
                    }
                }

                // Example data dependency:
                // add $s2, $t0, $t1
                // add $t4, $t5, $t6
                // add $t2, $s2, $t3                
                //
                // if the second to last instruction was an add or sub and the forwarding unit is disabled and the previous instruction did not have a stall cycle.
                else if (((rs == secondToLastInstruction.rt) || (rd == secondToLastInstruction.rt)) && (!enableForwardingUnitCheckBox.Checked) && (!prevInstructionHasStall()) && ((secondToLastInstruction.opcode == "add") || (secondToLastInstruction.opcode == "sub")))
                {
                    if (provideSolutionCheckBox.Checked)
                    {
                        answer = "FSDXMW";
                    }
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + secondToLastInstruction.rt + " cannot be used as an argument in add/sub and as rt in add/sub 2 instructions previous.\r";
                    }
                }

                else
                {
                    // nothing to do at this time.
                }
            }

            // check for all possible data dependencies for store word command
            else if (opcode == "sw")
            {
                // Example data dependency:
                // add $s2, $t0, $t1
                // sw $t2, 0($s2)

                // data dependency with previous command
                if (((lastInstruction.opcode == "add") || (lastInstruction.opcode == "sub")) && (rs == lastInstruction.rt))
                {
                    // checkbox is checked. Provide solution.
                    if (provideSolutionCheckBox.Checked)
                    {
                        // if the forwarding unit is enabled, do not insert stall cycles.
                        if (!enableForwardingUnitCheckBox.Checked)
                        {
                            answer = "FSSDXMW";
                        }
                    }

                    // checkbox not checked. Simply report the dependency to the user.
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rs + " cannot be used as rs in sw and rt in previous instruction (add/sub)\r";
                    }
                }

                // Example data dependency:
                // add $s2, $t0, $t1
                // sw $s2, 0($t2)

                // data dependency with previous command
                else if (((lastInstruction.opcode == "add") || (lastInstruction.opcode == "sub")) && (rt == lastInstruction.rt))
                {
                    // checkbox is checked. Provide solution.
                    if (provideSolutionCheckBox.Checked)
                    {
                        // if the forwarding unit is enabled, do not insert stall cycles.
                        if (!enableForwardingUnitCheckBox.Checked)
                        {
                            answer = "FSSDXMW";
                        }
                    }

                    // checkbox not checked. Simply report the dependency to the user.
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rt + " cannot be used as rt in sw and rt in previous instruction (add/sub)\r";
                    }
                }

                // Example data dependency:
                // lw $s2, 0($t0)
                // sw $s2, 0($t1)

                // data dependency with previous command
                else if ((lastInstruction.opcode == "lw") && (rt == lastInstruction.rt))
                {
                    // checkbox is checked. Provide solution.
                    if (provideSolutionCheckBox.Checked)
                    {
                        // if the forwarding unit is enabled, only insert one stall cycle.
                        if (!enableForwardingUnitCheckBox.Checked)
                        {
                            answer = "FSSDXMW";
                        }
                    }

                    // checkbox not checked. Simply report the dependency to the user.
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rt + " cannot be used as rt in sw and rt in previous lw instruction\r";
                    }
                }

                // Example data dependency:
                // lw $s2, 0($t0)
                // sw $t1, 0($s2)

                // data dependency with previous command
                else if ((lastInstruction.opcode == "lw") && (rs == lastInstruction.rt))
                {
                    // checkbox is checked. Provide solution.
                    if (provideSolutionCheckBox.Checked)
                    {
                        // if the forwarding unit is enabled, only insert one stall cycle.
                        if (!enableForwardingUnitCheckBox.Checked)
                        {
                            answer = "FSSDXMW";
                        }
                        else
                        {
                            answer = "FDSXMW";
                        }
                    }

                    // checkbox not checked. Simply report the dependency to the user.
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rs + " cannot be used as rs in sw and rt in previous lw instruction\r";
                    }
                }

                // Example data dependency:
                // add $s2, $t0, $t1
                // add $t4, $t5, $t6
                // sw $t2, 0($s2)
                //
                // Only needs one stall cycle if not using forwarding unit.
                // if the second to last instruction was an add or sub and the forwarding unit is disabled and the previous instruction did not have a stall cycle.
                else if ((rs == secondToLastInstruction.rt) && (!enableForwardingUnitCheckBox.Checked) && (!prevInstructionHasStall()) && ((secondToLastInstruction.opcode == "add") || (secondToLastInstruction.opcode == "sub")))
                {
                    if (provideSolutionCheckBox.Checked)
                    {
                        answer = "FSDXMW";
                    }
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rs + " cannot be used as rs in sw and rt in add/sub 2 instructions previous.\r";
                    }
                }

                // Example data dependency:
                // lw $s2, 0($t0)
                // add $t4, $t5, $t6
                // sw $t1, 0($s2)
                //
                // if the second to last instruction was an add or sub and the forwarding unit is disabled and the previous instruction did not have a stall cycle.
                else if ((rs == secondToLastInstruction.rt) && (!enableForwardingUnitCheckBox.Checked) && (!prevInstructionHasStall()) && (secondToLastInstruction.opcode == "lw"))
                {
                    if (provideSolutionCheckBox.Checked)
                    {
                        answer = "FSDXMW";
                    }
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rs + " cannot be used as rs in sw and rt in lw 2 instructions previous.\r";
                    }
                }

                // Example data dependency:
                // lw $s2, 0($t0)
                // add $t4, $t5, $t6
                // sw $s2, 0($t1)
                //
                // if the second to last instruction was an add or sub and the forwarding unit is disabled and the previous instruction did not have a stall cycle.
                else if ((rt == secondToLastInstruction.rt) && (!enableForwardingUnitCheckBox.Checked) && (!prevInstructionHasStall()) && (secondToLastInstruction.opcode == "lw"))
                {
                    if (provideSolutionCheckBox.Checked)
                    {
                        answer = "FSDXMW";
                    }
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rt + " cannot be used as rt in sw and rt in lw 2 instructions previous.\r";
                    }
                }

                // Example data dependency:
                // add $s2, $t0, $t1
                // add $t4, $t5, $t6
                // sw $s2, 0($t2)
                //
                // Only needs one stall cycle if not using forwarding unit.
                // if the second to last instruction was an add or sub and the forwarding unit is disabled and the previous instruction did not have a stall cycle.
                else if ((rt == secondToLastInstruction.rt) && (!enableForwardingUnitCheckBox.Checked) && (!prevInstructionHasStall()) && ((secondToLastInstruction.opcode == "add") || (secondToLastInstruction.opcode == "sub")))
                {
                    if (provideSolutionCheckBox.Checked)
                    {
                        answer = "FSDXMW";
                    }
                    else
                    {
                        translationTextBox.Text += "\nDATA DEPENDENCY: " + rt + " cannot be used as rt in sw and rt in add/sub 2 instructions previous.\r";
                    }
                }

                else
                {
                    // nothing to do here.
                }
            }

            else
            {
                // nothing to do here.
            }

            // if the user wants a timing diagram solution, format the timing diagram and output it
            if (provideSolutionCheckBox.Checked)
            {
                // send answer to the console properly formatted.
                formatTimeDiagramWithPrevTimeDiagram(ref answer);
            }
            else
            {
                // create a local copy of the cycle number
                int cycleCopy = cycleNumber;

                char[] standardTimingSequence = new char[] {'F', 'D', 'X', 'M', 'W' };

                // print the current timing diagram to the output.
                for (int i = 0; i < standardTimingSequence.Length; i++)
                {
                    // send each character in the string builder to the console followed by the spacing between characters.
                    commandsArr[numberOfInstructionsExecuted][cycleCopy].Text += standardTimingSequence[i];
                    cycleCopy = cycleCopy + 1;
                }
            }

            // update the instruction history
            updateInstructionHistory(ref opcode, ref rt, ref rs, ref rd);
        }

        // format the correct current timing diagram with the previous timing sequence
        // so that stall cycles are taken into account.
        // Format is "FDXMW". 'S' for stall.
        void formatTimeDiagramWithPrevTimeDiagram(ref string currentTimeDiagram)
        {
            // create a string builder and append the characters of the current timing diagram to it.
            var stringBuilder = new StringBuilder();
            for(int i = 0; i < currentTimeDiagram.Length; i++)
            {
                stringBuilder.Append(currentTimeDiagram[i]);
            }

            // if the second character in the previous timing sequence was a stall cycle, 
            // increment the number of instructions executed by 1, which adjusts the padding
            // for future commands.
            if (prevTimingSequence[1] == 'S')
            {
                cycleNumber = cycleNumber + 1;

                // if the third character is also a stall cycle in the previous instruction
                // add another offset to the initial spacing
                if (prevTimingSequence[2] == 'S')
                {
                    cycleNumber = cycleNumber + 1;
                }
            }

            // find the index of the decode in the previous instruction
            int dIndex = 0;
            while((dIndex < prevTimingSequence.Length) && (prevTimingSequence[dIndex] != 'D'))
            {
                dIndex = dIndex + 1;
            }

            // if the previous command had a stall cycle after the decode stage, carry it over to the current instruction.
            if (lastInstruction.opcode != "")
            {
                if (prevTimingSequence[dIndex + 1] == 'S')
                {
                    stringBuilder.Insert(1, 'S');
                }
            }

            // create a local copy of the cycle number
            int cycleCopy = cycleNumber;

            // print the current timing diagram to the output.
            for (int i = 0; i < stringBuilder.Length; i++)
            {
                // send each character in the string builder to the console followed by the spacing between characters.
                commandsArr[numberOfInstructionsExecuted][cycleCopy].Text += stringBuilder[i];
                cycleCopy = cycleCopy + 1;
            }

            // convert the properly formatted string builder to a string.
            string properlyFormattedAnswer = stringBuilder.ToString(); 

            // update the timing sequence history for the next command.
            updateTimingSequenceHistory(ref properlyFormattedAnswer);
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
            while ((arrayParse < registerNameStringArray.Length) && ((rt == "invalid") || (rs == "invalid") || (rd == "invalid")))
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

        // update the history of the instructions
        void updateInstructionHistory(ref string opcode, ref string rt, ref string rs, ref string rd)
        {
            // first update the 2nd to last instruction
            secondToLastInstruction.opcode = lastInstruction.opcode;
            secondToLastInstruction.rt = lastInstruction.rt;
            secondToLastInstruction.rs = lastInstruction.rs;
            secondToLastInstruction.rd = lastInstruction.rd;

            // update the last instruction.
            lastInstruction.opcode = opcode;
            lastInstruction.rt = rt;
            lastInstruction.rs = rs;
            lastInstruction.rd = rd;
        }

        // update the history of the timing sequence
        void updateTimingSequenceHistory(ref string currentTimingSequence)
        {
            // create a string builder and append all elements of the current timing sequence to it.
            var stringBuilder = new StringBuilder();
            for (int i = 0; i < currentTimingSequence.Length; i++)
            {
                stringBuilder.Append(currentTimingSequence[i]);
            }
            
            // update the previous timing sequence character array
            for(int i = 0; i < stringBuilder.Length; i++)
            {
                prevTimingSequence[i] = stringBuilder[i];
            }
        }

        // check if the previous instruction had a stall cycle.
        bool prevInstructionHasStall()
        {
            bool hasStall = false;
            for(int i = 0; i < prevTimingSequence.Length; i++)
            {
                if(prevTimingSequence[i] == 'S')
                {
                    hasStall = true;
                }
            }

            return hasStall;
        }

        // event handler for clicking the provide solution checkbox
        private void provideSolutionCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            // reset the settings for a new execution.
            reset(); 

            if (provideSolutionCheckBox.Checked)
            {
                // enable the forwarding unit checkbox.
                enableForwardingUnitCheckBox.Enabled = true;
            }
            else
            {
                // if the user unchecks the provide solution checkbox, uncheck and disable the forwarding unit checkbox.
                enableForwardingUnitCheckBox.Checked = false;
                enableForwardingUnitCheckBox.Enabled = false;
            }
        }

        // User pressed the enable forwarding unit checkbox and triggered this event.
        private void enableForwardingUnitCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            // reset the settings for new execution.
            reset();
        }

        // reset all setting for new execution.
        public void reset()
        {
            // clear the translation textbox
            translationTextBox.Clear();

            // clear all data in all textboxes
            for(int i = 0; i < commandsArr.Length; i++)
            {
                for(int j = 0; j < commandsArr[i].Length; j++)
                {
                    commandsArr[i][j].Clear();
                }
            }

            // reset index used to parse commands.
            parsingIndex = 0;

            // set the previous instruction opcode to the empty string
            lastInstruction.opcode = "";
            lastInstruction.rd = "";
            lastInstruction.rt = "";
            lastInstruction.rs = "";

            // set the 2nd to last opcode to the empty string
            secondToLastInstruction.opcode = "";
            secondToLastInstruction.rd = "";
            secondToLastInstruction.rt = "";
            secondToLastInstruction.rs = "";

            // set the previous timing sequence to empty characters
            for(int i = 0; i < prevTimingSequence.Length; i++)
            {
                prevTimingSequence[i] = ' ';
            }

            // set the number of instructions executed to zero.
            numberOfInstructionsExecuted = 0;

            // set the current cycle number to zero.
            cycleNumber = 0;
        }
    }
}
