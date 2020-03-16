#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

char int_char(int i) {
    return (char)(i + 97);
}

int char_int(char c) {
    return (int)(c - 97);
}

// Must be lowercase, s can be any integer value
void shift(char &c, long s) {
    long n = char_int(c);
    n = (n + s) % 26;
    if ( n < 0) n += 26;
    c = int_char(n);
}

int b26_dec(string dec) {
    int sum = 0;
    int size = dec.size();
    for (int i = 0; i < size; i++) {
        char c = dec[i];
        int value = char_int(c);
        sum += value * pow(26, size - i - 1);
    }
    return sum;
}

int b26_dec(char c) {
    string s(1, c);
    return b26_dec(s);
}

string dec_b26(int dec) {
    int power = 0;
    while (dec - pow(26, power + 1) >= 0) power++;
    vector<int> coefficients;
    int leftover = dec;
    while (power >= 0) {
        int coefficient = 0;
        while (leftover - (coefficient + 1) * pow(26, power) >= 0) coefficient++;
        leftover -= coefficient * pow(26, power);
        coefficients.push_back(coefficient);
        power--;
    }

    string s("");
    for (vector<int>::iterator iter = coefficients.begin(); iter != coefficients.end(); iter++) {
        s += int_char(*iter);
    }

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

    int numwords = b26_dec(s.substr(0, 2));
    int size[numwords];
    for (int i = 0; i < numwords; i++) {
        size[i] = b26_dec(s.at(i+2));
    }

    string message = s.substr(2+numwords);
    int pivot = 0;
    s.clear();
    for (int i : size) {
        s += message.substr(pivot, i) + " ";
        pivot += i;
    }
}

int main() {
    for (int casenum = 0; casenum < 10; casenum++){
        int key;
        string message;
        getline(cin, message);
        key = stoi(message);
        getline(cin, message);

        if (find(message.begin(), message.end(), ' ') != message.end()) {
            encrypt(message, key);
        }
        else {
            decrypt(message, key);
        }
        
        cout << message << endl;
    }
} 