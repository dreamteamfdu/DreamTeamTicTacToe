#include <vector>
#include <iostream>
using namespace std;

class Board {
private:
    size_t rows = 3; // Sets row count
    size_t cols = 3; // Sets column count
    vector <vector<char>> board; // 2d vector
    bool winner; // Bool to track the winner
public:
    Board() : board(rows, vector<char>(cols, ' ')) { // Constructor for a 3x3 matrix. Sets winner to false
        winner = false;
    }
    bool getWinner() { return winner; } // Winner getter
    bool isInBounds(size_t i, size_t j) { // checks to see if the entered points are within the bounds of the matrix
        if (i - 1 >= rows) { return false; }
        else if (j - 1 >= cols) { return false; }
        else { return true; }
    }
    void changeAtPosition(size_t i, size_t j, char p) { // Checks to see if position is in bounds, if it is, changes at position
        if (!isInBounds(i, j)) {
            cout << "ERR: input of row or column was out of bounds" << endl;
            return;
        }
        else if (board[i-1][j-1] != ' ') {
            cout << "ERR: Spot is already taken" << endl;
            return;
        }
        else {
            board[i-1][j-1] = p;
            return;
        }
    }
    void print() { // Print function iterates through the rows and columns, printing everything out into a 3x3 grid.
        cout << "   1 2 3" << endl;
        for (size_t i = 0; i < rows; i++) {
            cout << i + 1 << ": ";
            for (size_t j = 0; j < cols; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

class Player {
private:
    char piece;
    string name;
public:
    Player() { // Empty constructor
        piece = ' ';
        name = " ";
    }
    Player(char p, string n) { // Normal constructor
        piece = p;
        name = n;
    }
};

int main()
{
    /*
    TODO:
        implement player classes
        create turn switcher
        create win checker
        refine game loop
        fix error message when you input multichar strings
    */
    cout << "Hello, Tic-tac-toe!\n"; // comment explaining what you did
    size_t row;
    size_t col;
    Board b; // Initialize the board
    bool play = true;

    while (play) {

        b.print(); // Print the board

        cout << "Select a row: ";
        while (!(cin >> row)) { // Input validation for rows
            cout << "invalid input. Please enter a valid input: ";
            cin.clear();
            cin.ignore();
        }
        cout << "Select a column: ";
        while (!(cin >> col)) { // Input validation for columns
            cout << "Invalid input, please enter a vailid input: ";
            cin.clear();
            cin.ignore();
        }
        b.changeAtPosition(row, col, 'X');
    }


    return 0;
}

/*
User requirements:
    - X goes first
    - 3x3 grid
    - Program will tell players how to play the game
    - Give players a way to pick their symbol and enter their name into program
    - Give the player a way to input their spot
    - Make sure players cant write over another player's space, give them an error, and let them try to input again
    - Make sure players cant enter an invalid spot that doesnt exist, give them an error, and let them try to input again
    - Switch the turns after a player successfully picks a spot
    - Have the game check after a player enters their spot for a winner
    - When someone wins, it will say their name and that they won, and then add to a score showing many games they won
    - Give the players the option to play again
    - If the game ends in a tie, no points are awarded and players are given option to play again
    - Adding in singleplayer is a stretch goal


Design: 
    - We should use classes for this project.
        - Board class, player class
    - Board class (Design item)
    - How to break up the work
        - 3 coders (Elias, Matt, and John), 2 testers (Anthony and Alina)
           - Should testers fix code if they discover something that breaks? Yes?
              - Make sure to detail testing process and fix applied in commit message
    - Make sure it runs in Visual Studio
    - Make sure code is clear and understandable
        - dont do anything weird, make sure to comment what code does
    -For testers, explicitly explain testing process, issues, and resolutions
        - can be done as a commit message and as a block comment
    - Create README.md explaining how to play

    Bonus:

    - Maybe make way for players to keep playing and then track wins until they stop playing

Implementation (pseudocode):
    create class board with char 3x3 matrix and winner bool in private
    create constructors in public
    create check function in public
        check for winners and draws
    create change value function in public
        check if space is not X or O
        if true
            change value at position to player char
    create get winner function
    crete print function in public

    create player class with char symbol and string name in private
    create constructors in public
    create getters and setters

    in main
        construct board
        construct X and O player with names

        while no winner
            print function
            change value function
            check function
            if winner
                print player name is the winner

Tests:
    - Two rounds of testing (To determine order with Anthony and Alina)
    - Tests should be verbose and well documented
    - Create a documentation form on the test. How the test works, what happened when you ran the test, what caused the issues, how the coders can fix issues
    - Test process, results, and fixes to be clearly documented in commit message
*/