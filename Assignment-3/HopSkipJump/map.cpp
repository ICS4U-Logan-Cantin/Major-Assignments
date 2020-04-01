#include <iostream>
#include "map.h"


Map::Map(int width, int height, std::vector<std::string> &map) 
    : width(width), height(height) {

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            this->map[i][j] = map.at(height-j-1).at(i);
        }
    }
}

char Map::peek(std::pair<int, int> p) {
    if (!valid(p)) {
        return CLEAR;
    }
    else {
        return map[p.first][p.second];
    }
    
}

char Map::visit(std::pair<int, int> p) {
    visited[p.first][p.second] = true;
    return peek(p);
}

bool Map::valid(std::pair<int, int> p) {
    int x = p.first;
    int y = p.second;

    return 0 <= x && x < width && 0 <= y && y < height && !visited[x][y];
}

void Map::print_mask() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << visited[j][height - i - 1];
        }
        std::cout << std::endl;
    }
}

void Map::print() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << map[j][height - i - 1];
        }
        std::cout << std::endl;
    }
}
