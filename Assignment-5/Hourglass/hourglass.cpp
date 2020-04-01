#include <iostream>
#include <string>

using namespace std;

string multiplier (string s, int multiplier) {
    string output;
    for (int i = 0; i < multiplier; i++) {
        output += s;
    }
    return output;
}

string hourglass(int n, int maxsize = -1) {
    if (maxsize == -1) {
        maxsize = n;
    }
    if (n == 1) {
        return multiplier(multiplier(" ", maxsize - n) + "*\n", 2);
    }
    string s = multiplier(" ", maxsize - n) + multiplier("* ", n) + "\n";
    return s + hourglass(n - 1, maxsize) + s; 
}

int main() {
    cout << hourglass(4) << endl;
    cout << hourglass(7) << endl;
    cout << hourglass(1);
}