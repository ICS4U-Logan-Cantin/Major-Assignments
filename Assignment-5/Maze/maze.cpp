#include <iostream>
#include <string>
#include <vector>

using namespace std;

const char WALL = '#';
const char CLEAR = '.';
const char GOODPATH = '+';
const char START = 'S';
const char GOAL = 'G';

const int MAX_SIZE = 100;

class Map {
    char map[MAX_SIZE][MAX_SIZE];
    int width, height;

    public:
    Map(istream& is, int width, int height) : width(width), height(height) {
        for (int j = 0; j < height; j++) {
            string s;
            getline(is, s);
            for (int i = 0; i < width; i++) {
                map[i][j] = s[i];
            }
        }
    }

    void print() {
        for (int j = 0; j < MAX_SIZE; j++) {
            for (int i = 0; i < MAX_SIZE; i++) {
                cout << map[i][j];
            }
            cout << endl;   
        }
        
    }
};


int main() {
    int width, height;
    cin >> width >> height;

    Map m(cin, width, height);
    m.print();
}