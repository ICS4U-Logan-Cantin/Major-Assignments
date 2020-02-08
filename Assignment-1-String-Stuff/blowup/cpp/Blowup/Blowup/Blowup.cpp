/* BLOWUP
 * Created by: Logan Cantin
 * Created on: 07-Feb-2019
 * Created for: ICS4U
 * Assignment 1 (String Stuff) - Blowup
 * This program blows up a string by using numbers as coefficients, multiplying the letter to the right of it
 */

#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
	// Initializing inputString with user input
	string inputString;
	cin >> inputString;

	// If string contains non-alphanumeric characters, alert the user and exit
	if (!regex_match(inputString, regex("[0-9a-zA-Z]*"))) {
		cout << "Invalid input: only enter alphanumeric characters." << endl;
		exit(1);
	}

	// initializing variables
	int index = 0;
	string outputString = "";

	// Making sure to stay inside the bounds of the string
	while (index < inputString.length()) {

		// Getting character at index
		char tempChar = inputString.at(index);

		// If it is a digit
		if (isdigit(tempChar)) {

			// If it is the last character in the string, add it to the output and increment counter
			if (index == inputString.length() - 1) {
				outputString += tempChar;
				index++;
				continue;
			}

			// Get next character
			char nextChar = inputString.at(index + 1);
			
			// If it is another digit, add current character to the output and increment the counter
			if (isdigit(nextChar)) {
				outputString += tempChar;
				index++;
				continue;
			}

			// Calculate the resulting string and add it to the output. Increment index
			int multiplier = stoi(string(1, tempChar));
			outputString += string(multiplier, nextChar);
			index++;
		}

		// Character is a letter. Add it to the output and increment index
		else {
			outputString += tempChar;
			index++;
		}
	}

	// print outputString
	cout << outputString << endl;
	
	return 0;
}


