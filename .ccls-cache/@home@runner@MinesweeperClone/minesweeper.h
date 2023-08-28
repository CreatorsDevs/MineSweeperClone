#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <bits/stdc++.h>
using namespace std;

#define max_mine 99
#define max_side 25
#define max_move 526 // 25*25-99

class Minesweeper {
public:
    Minesweeper(); // Constructor
    void play();
    void choosedifficulty();

private:
    int SIDE;   // Size of the game board (side length)
    int MINES;  // Number of mines on the board

    // Function declarations for gameplay and utilities
    void clear();
    bool isvalid(int row, int col);
    bool ismine(int row, int col, char board[][max_side]);
    void make_move(int *x, int *y);
    void printboard(char myboard[][max_side]);
    int countadjacent(int row, int col, int mines[][2], char realboard[][max_side]);
    bool playminesuntil(char myboard[][max_side], char realboard[][max_side], int mines[][2], int row, int col, int *moves_left);
    void placemines(int mines[][2], char realboard[][max_side]);
    void initialise(char realboard[][max_side], char myboard[][max_side]);
    void cheatmines(char realboard[][max_side]);
    void replacemine(int row, int col, char board[][max_side]);
};

#endif // MINESWEEPER_H