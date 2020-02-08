/* MAX RUN
 * Created by: Logan Cantin
 * Created on: 07-Feb-2019
 * Created for: ICS4U
 * Assignment 1 (String Stuff)
 * This program finds and outputs the size of the largest run of identical characters
 */

import java.util.Scanner;

public class MaxRun {

    public static void main(String[] args) {

        // Getting input string from the user
        Scanner iostream = new Scanner(System.in);
        String input = iostream.nextLine();

        // Initializing variables
        int maxRun = 0;
        int pivot = 0;

        // Making sure that the pivot doesn't go out of bounds
        while (pivot < input.length()){

            // Getting first char of the substring and setting the initial size of the run to 1
            char tempChar = input.charAt(pivot);
            int tempRun = 1;

            // If the next character is part of this run (and not out of bounds) then increment the size of the run
            while ((pivot + tempRun < input.length()) && (input.charAt(pivot+tempRun) == tempChar)){
                tempRun++;
            }

            // If the size of this run is larger than all the others before it, set it to be the new largest run
            if (tempRun > maxRun){
                maxRun = tempRun;
            }

            // Moving pivot
            pivot += tempRun;
        }

        // Print size of the largest run
        System.out.println(maxRun);
        iostream.nextLine();
    }
}
