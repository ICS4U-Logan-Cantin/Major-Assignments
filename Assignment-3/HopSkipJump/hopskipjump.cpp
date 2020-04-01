#include <iostream>
#include <string>
#include <vector>

#include "map.h"

using namespace std;

pair<int, int> operator+ (pair<int, int> one, pair<int, int> two) {
    return make_pair(one.first + two.first, one.second + two.second);
}

// Moving vertically down
pair<int, int> operator- (pair<int, int> one, int two) {
    return make_pair(one.first, one.second - two);
}

pair<int, int> operator+ (pair<int, int> one, int two) {
    return make_pair(one.first, one.second + two);
}

class Player {
    public:
    bool cup, flag, treasure;
    Map map;

    void try_strafe(pair<int, int> old) {
        
        pair<int, int> new_point = old + make_pair(1, 0);
        if (map.peek(new_point) != PLATFORM && map.peek(new_point - 1) == PLATFORM) {
            move(new_point);
        }

        new_point = old + make_pair(-1, 0);
        if (map.peek(new_point) != PLATFORM && map.peek(new_point - 1) == PLATFORM) {
            move(new_point);
        }
    }

    void try_climb(pair<int, int> old) {
        if (map.peek(old) == LADDER && map.peek(old + 1) == LADDER) {
            move(old + 1);
        }
    }

    void move(pair<int, int> p) {
        if (!map.valid(p)) {
            return;
        }

        map.visit(p);

        char currentTile = map.peek(p);
        char underneath = map.peek(p - 1);
        if (currentTile != LADDER && underneath != PLATFORM) {
            // Falling!
            move(p-1);
            return;
        }

        // Moves
        try_strafe(p);
        try_climb(p);
    }

    Player(int x, int y, Map map) : map(map) {
        cup = false;
        flag = false;
        treasure = false;
        
        move(make_pair(x, y));
    }
};



int main() {
    vector<string> v;
    string temp;
    int width, height;

    cin >> width >> height;

    for (int i = 0; i < height; i++) {
        cin >> temp;
        v.push_back(temp);
    }

    Map m(width, height, v);
    

    Player p(0, 4, m);
    p.map.print_mask();

}