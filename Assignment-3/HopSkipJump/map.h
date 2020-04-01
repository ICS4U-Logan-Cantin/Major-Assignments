#pragma once
#include <string>
#include <vector>

const int MAX_SIZE = 200;

const char PLATFORM = '=';
const char CLEAR = '.';
const char LADDER = '#';

class Map {
public:
    char map[MAX_SIZE][MAX_SIZE];
    bool visited[MAX_SIZE][MAX_SIZE];
    int width, height;

    Map(int, int, std::vector<std::string>&);
    char peek(std::pair<int, int>);
    char visit(std::pair<int, int>);
    bool valid(std::pair<int, int>);
    void print_mask();
    void print();
};