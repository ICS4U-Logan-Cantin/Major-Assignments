#include <iostream>
#include <vector>
#include <map>

using namespace std;

const map<char, string> num2chars = {
    {'2', "ABC"},
    {'3', "DEF"},
    {'4', "GHI"},
    {'5', "JKL"},
    {'6', "MNO"},
    {'7', "PQRS"},
    {'8', "TUV"},
    {'9', "WXYZ"}
};

vector<string> mnemonics(string number) {
    if (number.size() == 1) {
        vector<string> v;
        for (char c : num2chars.at(number[0])) {
            v.push_back(string(1, c));
        }
        return v;
    }

    vector<string> vec;
    for (char c : num2chars.at(number[0])) {
        for (string s : mnemonics(number.substr(1))) {
            vec.push_back(c + s);
        }
    }
    return vec;
}

void print_vector(const vector<string> &v) {
    for (string s : v) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    string num;
    cin >> num;

    print_vector(mnemonics(num));
}