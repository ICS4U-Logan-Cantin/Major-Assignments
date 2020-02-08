/* MAX RUN
 * Created by: Logan Cantin
 * Created on: 07-Feb-2019
 * Created for: ICS4U
 * Assignment 1 (String Stuff)
 * This program finds and outputs the size of the largest run of identical characters
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
	// Getting user input
	string input;
	cin >> input; 

	// Establishing variables and constants
	int maxRun = 0; 
	int pivot = 0;
	const int INPUT_LEN = input.length();

	// Making sure that the pivot is inside the bounds of the string
	while (pivot < INPUT_LEN) {

		// Getting first char of the substring and initializing the size of the run
		char tempChar = input[pivot];
		int tempRun = 1;

		// If the next character is a continuation of the run (and not the end of the string),
		// increment the tempRun variable
		while ((pivot + tempRun < INPUT_LEN) & (input[pivot + tempRun] == tempChar)) {
			tempRun++;
		}

		// If the size of this substring is larger than the current max, set it as the current max
		if (tempRun > maxRun) {
			maxRun = tempRun;
		}

		// Increase pivot
		pivot += tempRun;
	}

	// Output the size of the largest run
	cout << maxRun << endl;
}

