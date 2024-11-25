#ifndef GAME_H
#define GAME_H


#include "../Grid/Grid.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Game {
private:
    int id = 0;
    Grid& grid;
    bool state = true;
    int currentGen = 0;

    void saveGen(vector<vector<bool>>& grid) const;
public:
    Game(int id, Grid& grid);

    void nextGen();

    int getCurrentGen() const;

    bool isFinished() const;

    Grid& getGrid() const;
};



#endif