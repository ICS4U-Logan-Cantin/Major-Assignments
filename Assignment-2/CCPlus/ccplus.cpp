#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Converting from int to character (starting at 0)
char int_char(int i) {
    return (char)(i + 97);
}

// Converting from character to int (starting at 0)
int char_int(char c) {
    return (int)(c - 97);
}

// Shifts a character by a given value
// Must be lowercase, s can be any integer value
void shift(char &c, long s) {
    long n = char_int(c);       //Getting char value
    n = (n + s) % 26;           //Adding the shift value and applying mod 26
    if ( n < 0) n += 26;        //if the value is negative, add 26 to make it positive
    c = int_char(n);            //Set the new character to c
}

// Converting from base26 to decimal
int b26_dec(string dec) {

    // Initializing variables
    int sum = 0;
    int size = dec.size();

    // For every digit of the base26 number
    for (int i = 0; i < size; i++) {

        // Get the digit and its integer coefficient
        char c = dec[i];
        int value = char_int(c);

        // Add the coefficient times 26 to the power of that character's position to the total
        sum += value * pow(26, size - i - 1);
    }

    // Return the total
    return sum;
}

// Overloaded function for converting b26 to decimal
int b26_dec(char c) {
    string s(1, c);
    return b26_dec(s);
}


// Converting decimal to base 26
string dec_b26(int dec) {

    // Setting the initial power to be the largest meaningful power of 26
    int power = 0;
    while (dec - pow(26, power + 1) >= 0) power++;

    // Vector to store all the coefficients
    // Leftover variable is set initially to the full value
    vector<int> coefficients;
    int leftover = dec;

    // While the power is positive or zero
    while (power >= 0) {
        // Maximize coefficient without going negative
        int coefficient = 0;
        while (leftover - (coefficient + 1) * pow(26, power) >= 0) coefficient++;

        // Subtract that from the leftover and add it to the vector
        leftover -= coefficient * pow(26, power);
        coefficients.push_back(coefficient);
        power--; // decrement power
    }

    // Base26 string: convert each coefficient to base26 and add it to the string
    string s("");
    for (vector<int>::iterator iter = coefficients.begin(); iter != coefficients.end(); iter++) {
        s += int_char(*iter);
    }

    // Return the base26 string
    return s;
}

// Encrypt a string, given a key
void encrypt (string &s, long key) {

    // Diving the string into the individual words
    vector<string> strings;
    string temp;
    for (char c : s) {
        if (c == ' ') {
            strings.push_back(temp);
            temp.clear();
        }
        else {
            temp += c;
        }
    }
    strings.push_back(temp);

    // Building the prefix
    // Format (all in base26): (#words, 2 characters long always)(length of each word, always one character)
    string prefix;
    string numwords = dec_b26(strings.size());  // Calculating the number of new words
    if (numwords.length() == 1) {               // Padding with an a if necessary
        numwords = "a" + numwords;
    }
    prefix += numwords;                         // Number of words
    for (string word : strings) {               // Calculating the length of each string and appending it to the prefix
        prefix += dec_b26(word.length());
    }
    prefix += " ";                              // Appending a space
    s = prefix + s;                             // Prepending it to the string

    // Erasing all spaces
    s.erase(remove(s.begin(), s.end(), ' '), s.end());

    // Shifting all characters
    int sum = 0;                                // Sum of characters to the right
    int tempSum;                                // Temp value to hold the value of a character
    for (string::reverse_iterator iter = s.rbegin(); iter != s.rend(); iter++) {
                                                // Iterating through the string backwards
        char &c = *iter;
        tempSum = char_int(c);                  // Calculating value of character before shifting
        shift(c, sum + key);                    // Shifting the letter
        sum += tempSum;                         // Adding the value of the unshifted character to the sum
    }
}

void decrypt(string &s, int key) {
    // Unshift all characters
    int sum = 0;
    for (string::reverse_iterator iter = s.rbegin(); iter != s.rend(); iter++) {
        char &c = *iter;
        shift(c, - sum - key);
        sum += char_int(c);
    }

    // Calculate the number of words from the prefix
    int numwords = b26_dec(s.substr(0, 2));

    // For the next <numwords> characters, store that word's length
    int size[numwords];
    for (int i = 0; i < numwords; i++) {
        size[i] = b26_dec(s.at(i+2));
    }

    // Removing the prefix and initializing the pivot
    string message = s.substr(2+numwords);
    int pivot = 0;
    
    // Clearing the input string
    s.clear();

    // Divide the message up into its pieces
    for (int i : size) {
        s += message.substr(pivot, i) + " ";
        pivot += i;
    }
}


int main() {
    // Foreach Case
    for (int casenum = 0; casenum < 10; casenum++){

        // Initialize key and message
        int key;
        string message;
        getline(cin, message);
        key = stoi(message);
        getline(cin, message);

        // If there are spaces, encrypt the message
        if (find(message.begin(), message.end(), ' ') != message.end()) {
            encrypt(message, key);
        }
        else {
            // Decrypt the message
            decrypt(message, key);
        }
        
        // Output the message (decrypted or encrypted)
        cout << message << endl;
    }
} 