#include "minesweeper.h"
#include <ctime>

// Constructor
Minesweeper::Minesweeper() {
    SIDE = 0;
    MINES = 0;
}

// Clear the console screen
void Minesweeper::clear() {
    printf("\33[2J\33[1;1H");
}

// Check if a cell is valid on the board
bool Minesweeper::isvalid(int row, int col) {
    return (row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE);
}

// Check if a cell contains a mine
bool Minesweeper::ismine(int row, int col, char board[][max_side]) {
    if (board[row][col] == '*')
        return true;
    else
        return false;
}

// Get the player's move
void Minesweeper::make_move(int *x, int *y) {
    while (true) {
        printf("\nEnter your move: [row] [column] -> ");
        scanf("%d %d", x, y);
        if ((*x < SIDE) && (*y < SIDE)) {
            return;
        }
    }
}

// Print the game board
void Minesweeper::printboard(char myboard[][max_side]) {
    clear();
    printf("\n\n\t\t\t    ");
    for (int i = 0; i < SIDE; i++) {
        if (i > 9)
            printf("%d ", i / 10);
        else
            printf("  ");
    }
    printf("\n\t\t\t    ");
    for (int i = 0; i < SIDE; i++)
        printf("%d ", i % 10);
    printf("\n\n");
    for (int i = 0; i < SIDE; i++) {
        printf("\t\t\t    ");
        for (int j = 0; j < SIDE; j++) {
            printf("%c ", myboard[i][j]);
        }
        printf(" %2d", i);
        printf("\n");
    }
    return;
}

// Count the number of mines adjacent to a cell
int Minesweeper::countadjacent(int row, int col, int mines[][2], char realboard[][max_side]) {
    int count = 0;

    // Check all adjacent cells for mines  
    if (isvalid(row - 1, col) == true) {
        if (ismine(row - 1, col, realboard) == true)
            count++;
    }

    if (isvalid(row + 1, col) == true) {
        if (ismine(row + 1, col, realboard) == true)
            count++;
    }

    if (isvalid(row, col + 1) == true) {
        if (ismine(row, col + 1, realboard) == true)
            count++;
    }

    if (isvalid(row, col - 1) == true) {
        if (ismine(row, col - 1, realboard) == true)
            count++;
    }

    if (isvalid(row - 1, col - 1) == true) {
        if (ismine(row - 1, col - 1, realboard) == true)
            count++;
    }

    if (isvalid(row - 1, col + 1) == true) {
        if (ismine(row - 1, col + 1, realboard) == true)
            count++;
    }

    if (isvalid(row + 1, col - 1) == true) {
        if (ismine(row + 1, col - 1, realboard) == true)
            count++;
    }

    if (isvalid(row + 1, col + 1) == true) {
        if (ismine(row + 1, col + 1, realboard) == true)
            count++;
    }

    return count;
}

// Recursive function to uncover cells until no more adjacent mines
bool Minesweeper::playminesuntil(char myboard[][max_side], char realboard[][max_side], int mines[][2], int row, int col, int *moves_left) {
    if (myboard[row][col] != '-')
        return false;

    int i, j;
  
    // Check if the chosen cell contains a mine
    if (realboard[row][col] == '*') {
        myboard[row][col] = '*';
        for (i = 0; i < MINES; i++)
            myboard[mines[i][0]][mines[i][1]] = '*';

        printboard(myboard);
        printf("\nYou lost!\n");
        return true;
    } else {
        int count = countadjacent(row, col, mines, realboard);
        (*moves_left)--;

        myboard[row][col] = count + '0';

        // If no adjacent mines, recursively uncover neighboring cells
        if (!count) {
            if (isvalid(row - 1, col) == true) {
                if (ismine(row - 1, col, realboard) == false)
                    playminesuntil(myboard, realboard, mines, row - 1, col, moves_left);
            }

            if (isvalid(row + 1, col) == true) {
                if (ismine(row + 1, col, realboard) == false)
                    playminesuntil(myboard, realboard, mines, row + 1, col, moves_left);
            }

            if (isvalid(row, col + 1) == true) {
                if (ismine(row, col + 1, realboard) == false)
                    playminesuntil(myboard, realboard, mines, row, col + 1, moves_left);
            }

            if (isvalid(row, col - 1) == true) {
                if (ismine(row, col - 1, realboard) == false)
                    playminesuntil(myboard, realboard, mines, row, col - 1, moves_left);
            }

            if (isvalid(row - 1, col + 1) == true) {
                if (ismine(row - 1, col + 1, realboard) == false)
                    playminesuntil(myboard, realboard, mines, row - 1, col + 1, moves_left);
            }

            if (isvalid(row - 1, col - 1) == true) {
                if (ismine(row - 1, col - 1, realboard) == false)
                    playminesuntil(myboard, realboard, mines, row - 1, col - 1, moves_left);
            }

            if (isvalid(row + 1, col + 1) == true) {
                if (ismine(row + 1, col + 1, realboard) == false)
                    playminesuntil(myboard, realboard, mines, row + 1, col + 1, moves_left);
            }

            if (isvalid(row + 1, col - 1) == true) {
                if (ismine(row + 1, col - 1, realboard) == false)
                    playminesuntil(myboard, realboard, mines, row + 1, col - 1, moves_left);
            }
        }
        return false;
    }
}

// Place mines randomly on the board
void Minesweeper::placemines(int mines[][2], char realboard[][max_side]) {
    bool mark[max_side * max_side];

    memset(mark, false, sizeof(mark));

    for (int i = 0; i < MINES;) {
        int random = rand() % (SIDE * SIDE);
        int x = random / SIDE;
        int y = random % SIDE;

        if (mark[random] == false) {
            mines[i][0] = x;
            mines[i][1] = y;

            realboard[mines[i][0]][mines[i][1]] = '*';
            mark[random] = true;
            i++;
        }
    }
}

// Initialize the game board
void Minesweeper::initialise(char realboard[][max_side], char myboard[][max_side]) {
    srand(time(NULL));

    int i, j;
    for (i = 0; i < SIDE; i++)
        for (j = 0; j < SIDE; j++) {
            myboard[i][j] = realboard[i][j] = '-';
        }
}

// Cheat function to reveal mine locations
void Minesweeper::cheatmines(char realboard[][max_side]) {
    printf("The mines locations are-\n");
    printboard(realboard);
}

// Replace a mine to prevent the first move being a mine
void Minesweeper::replacemine(int row, int col, char board[][max_side]) {
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (board[i][j] != '*') {
                board[i][j] = '*';
                board[row][col] = '-';
                return;
            }
        }
    }
}

// Start the game
void Minesweeper::play() {
    bool gameover = false;

    char realboard[max_side][max_side], myboard[max_side][max_side];

    int moves_left = SIDE * SIDE - MINES;
    int x, y;
    int mines[max_mine][2];

    initialise(realboard, myboard);

    placemines(mines, realboard);

    int currentmoveindex = 0;

    while (!gameover) {
        printf("Current Status of Board : \n");
        printboard(myboard);
        make_move(&x, &y);

        if (currentmoveindex == 0) {
            if (ismine(x, y, realboard)) 
                replacemine(x, y, realboard);
        }

        currentmoveindex++;

        gameover = playminesuntil(myboard, realboard, mines, x, y, &moves_left);

        if (!gameover && moves_left == 0) {
            printf("\nYou won !\n");
            gameover = true;
        }
    }
}

// Choose game difficulty
void Minesweeper::choosedifficulty() {
    clear();
    cout << "\n\t\t\t\t\t\t\t\tMINESWEEPER";
    cout << "\n\n\t\t\t\t\t\tCHOOSE DIFFICULTY LEVEL : ";
    cout << "\n\n\t\t\t\t\t\t0.BEGINNER\n\t\t\t\t\t\t1.INTERMEDIATE\n\t\t\t\t\t\t2.ADVANCED";
    cout << "\n\n\t\t\t\t\t\tENTER CHOICE (0-2) : ";
    int choice;
    cin >> choice;
    if (choice == 0) {
        SIDE = 9;
        MINES = 10;
    } else if (choice == 1) {
        SIDE = 16;
        MINES = 40;
    } else if (choice == 2) {
        SIDE = 24;
        MINES = 99;
    } else {
        exit(0);
    }
}