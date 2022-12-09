/*
 * Anthony Redamonti
 * Professor Gregory Wagner
 * CSE 681 Software Modeling
 * Assignment 1
 * 7/19/2022
 * 
 * The following program asks the user for their name.
 * If the user enters an empty string, the program will
 * keep asking for their name. After a valid string (name)
 * has been entered, the  program displays "Hello " followed
 * by the entered name.
 */

namespace Assignment1
{
    public class Class1
    {
        static public void Main(String[] stringArgs)
        {
            // declare variable
            string name = null;

            // get the input from the user.
            try
            {
                // make sure the user entered something.
                while ((name == null) || (name == ""))
                {
                    // ask the user for their name.
                    Console.WriteLine("Please enter your name: ");

                    // update the string.
                    name = Console.ReadLine();
                }
            }
            // catch any exception here.
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                throw;
            }

            // say hello to the user.
            Console.WriteLine("Hello " + name);
        }
    }
}