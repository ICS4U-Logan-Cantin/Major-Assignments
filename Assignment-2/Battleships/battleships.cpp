#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Returns a column from the board
string vline(int col, vector<string> &board) {
    string column;

    // If the column requested is out of bounds, return a column with no anomalies
    if (col < 0 || col >= board.size())
        return string(board.size(), '.');
    
    // Generate the column
    for (int i = 0; i < board.size(); i++) {
        column += board.at(i).at(col);
    }

    // Return the column
    return column;
}


// Returns a row from the board
string hline(int row, vector<string> &board) {

    // If the column requested is out of bounds, return a column with no anomalies
    if (row < 0 || row >= board.size())
        return string(board.size(), '.');

    // Return the requested row
    return board.at(row);
}

// Calculate the number of positions in a given column / row
// Aux1 and aux2 are the neighbouring rows / columns
int numPositions(string main, string aux1, string aux2, int size) {
    
    /// MARK OFF THE ILLEGAL AREAS
    // Block out any illegal spots with an x
    for (int i = 0; i < main.length(); i++) {

        // If the spot above or below has a hit, this position is illegal
        if (aux1[i] == 'h' || aux2[i] == 'h') {
            main[i] = 'x';

            // Any adjacent positions are also illegal, put an x if in range
            if (i > 0) main[i - 1] = 'x';
            if (i < main.length() - 1) main[i + 1] = 'x';
        }

        // A miss is also illegal (the ship can't pass through a miss)
        if (main[i] == 'm') {
            main[i] = 'x';
        }
    }

    /// GIVEN THE LEGAL AREAS AND SHIP WIDTH, CALCULATE HOW MANY POSSIBILITIES THERE ARE
    // Counter variable for the number of possibilities
    int counter = 0;
    
    // For every possible ship position, regardless of whether it is legal
    for (int i = 0; i < main.length() - size + 1; i++) {
        // Create a substring for this ship position
        string temp = main.substr(i, size);

        // If there is an x inside the ships bounds, move on
        if (find(temp.begin(), temp.end(), 'x') != temp.end())
            continue;
        
        // If an adjacent tile to the left or right is a hit, move on
        else if (i > 0 && main[i-1] == 'h') continue;
        else if (i < main.length() - 1 && main[i + size] == 'h') continue;
        
        // Legal spot!
        else counter++;

    }

    // Return number of legal spots
    return counter;
}

// Handles the calculation of the number of positions for the whole board
int numPositions(vector<string> &board, int width) {
    int positions = 0;

    // For each row / column
    for (int i = 0; i < board.size(); i++) {
        // Calculate the number of positions that it has and add it to the positions counter
        positions += numPositions(vline(i, board), vline(i - 1, board), vline(i + 1, board), width);
        positions += numPositions(hline(i, board), hline(i - 1, board), hline(i + 1, board), width);
    }

    return positions;
}

// Main function
int main() {
    // Board size and ship width, respectively
    int s, w;

    // For each case
    for (int casenum = 0; casenum < 10; casenum++){

        // Read the variables and populate board
        cin >> s >> w;
        vector<string> board;
        for (int i = 0; i < s; i++) {
            string temp;
            cin >> temp;
            board.push_back(temp);
        }

        // Calculate and output the number of positions for that board.
        cout << numPositions(board, w) << endl;
    }
}