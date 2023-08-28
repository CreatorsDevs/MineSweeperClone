#include "minesweeper.h"

int main() {
    Minesweeper minesweeper;          // Create a Minesweeper game object
    minesweeper.choosedifficulty();   // Choose game difficulty
    minesweeper.play();               // Start the game
    return 0;
}