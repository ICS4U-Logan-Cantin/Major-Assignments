#include <iostream>
#include <vector>

using namespace std;

string pattern(int n) {
    if (n == 1) {
        return "1 ";
    }
    else {
        return pattern(n-1) + to_string(n) + ((n > 5) ? "\n" : " ") + pattern(n-1);
    }
}

int main() {
    int n;
    cin >> n;
    cout << pattern(n) << endl;
}