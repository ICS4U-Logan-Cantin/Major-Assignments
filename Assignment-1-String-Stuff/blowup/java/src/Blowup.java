/* BLOWUP
 * Created by: Logan Cantin
 * Created on: 07-Feb-2019
 * Created for: ICS4U
 * Assignment 1 (String Stuff) - Blowup
 * This program blows up a string by using numbers as coefficients, multiplying the letter to the right of it
 */

import java.util.Scanner;

public class Blowup {

    // Multiplies a given character a certain amount of times
    public static String charMultiplier(int multiplier, char base){

        // Initializing new char array
        char[] output = new char[multiplier];

        // Adding the character to the output array <multiplier> times
        for (; multiplier > 0; multiplier--){
            output[multiplier-1] = base;
        }

        // Return string
        return new String(output);
    }

    public static void main(String[] args) {

        // Initialize Scanner
        Scanner iostream = new Scanner(System.in);

        // Reading input from the user
        String inputString = iostream.nextLine();

        // If the string contains non-alphanumeric characters
        if (!inputString.matches("[A-Za-z0-9]*")) {
            System.out.println("Only enter alphanumerical characters.");
        }

        // Initializing variables
        int index = 0;
        StringBuilder outputString = new StringBuilder();

        // Ensuring index doesn't go out of the bounds of the string
        while (index < inputString.length()){

            // Getting the character at the index
            char tempChar = inputString.charAt(index);

            // If the character is a digit
            if (Character.isDigit(tempChar)) {

                // If character is the last in the string, output it and increase increment the index
                if (index == inputString.length() - 1) {
                    outputString.append(tempChar);
                    index++;
                    continue;
                }

                // Getting the adjacent character
                char nextChar = inputString.charAt(index + 1);

                // If the adjacent character is a number, output the current character and increment the index
                if (Character.isDigit(nextChar)) {
                    outputString.append(tempChar);
                    index++;
                    continue;
                }

                // Add the adjacent character <multiplier> times
                int multiplier = Integer.parseInt(String.valueOf(tempChar));
                outputString.append(Blowup.charMultiplier(multiplier, nextChar));
            }
            // Character is a letter
            else {
                // Add it to the output string
                outputString.append(tempChar);
            }

            // Increment index
            index++;
        }

        // Print output
        System.out.println(outputString);

    }
}
