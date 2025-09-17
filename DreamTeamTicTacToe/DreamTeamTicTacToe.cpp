#include <vector>
#include <iostream>
#include <limits>
#include <cctype> // for tolower and toupper
#include <algorithm> // for transform
using namespace std;

class Board {
private:
    size_t rows = 3; // Sets row count
    size_t cols = 3; // Sets column count
    vector <vector<char>> board; // 2d vector
    bool winner; // Bool to track the winner

public:
    Board() : board(rows, vector<char>(cols, ' ')), winner(false) {} // Constructor for a 3x3 matrix. Sets winner to false
    bool getWinner() const { return winner; } // Winner getter

    // SAFE bounds
    bool isInBounds(size_t i, size_t j) const {  // checks to see if the entered points are within the bounds of the matrix
        return (i >= 1 && i <= rows && j >= 1 && j <= cols);
    }

    char at(size_t i, size_t j) const { return board[i - 1][j - 1]; }

    bool changeAtPosition(size_t i, size_t j, char p) { // Checks to see if position is in bounds, if it is, changes at position
        if (!isInBounds(i, j)) {
            cout << "ERR: input of row or column was out of bounds\n";
            return false;
        }
        if (board[i - 1][j - 1] != ' ') {
            cout << "ERR: Spot is already taken\n";
            return false;
        }
        board[i - 1][j - 1] = p;
        return true;
    }

    bool three(char a, char b, char c, char who) const {
        return (a == who && b == who && c == who);
    }

    // Returns 'X'/'O' winner, 'T' tie, or ' ' continue
    char checkGameState() {
        for (char who : {'X', 'O'}) {
            // rows
            for (size_t r = 1; r <= rows; ++r)
                if (three(at(r, 1), at(r, 2), at(r, 3), who))
                    return winner = true, who;
            // cols
            for (size_t c = 1; c <= cols; ++c)
                if (three(at(1, c), at(2, c), at(3, c), who))
                    return winner = true, who;
            // diagonals
            if (three(at(1, 1), at(2, 2), at(3, 3), who))
                return winner = true, who;
            if (three(at(1, 3), at(2, 2), at(3, 1), who))
                return winner = true, who;
        }
        // tie
        bool anyEmpty = false;
        for (size_t r = 1; r <= rows; ++r)
            for (size_t c = 1; c <= cols; ++c)
                if (at(r, c) == ' ') anyEmpty = true;

        if (!anyEmpty) return 'T';
        return ' ';
    }

    void print() { // Print function iterates through the rows and columns, printing everything out into a 3x3 grid.
        cout << "   1 2 3\n";
        for (size_t i = 0; i < rows; i++) {
            cout << i + 1 << ": ";
            for (size_t j = 0; j < cols; j++) {
                cout << board[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    void clear() { // Print function iterates through the rows and columns, printing everything out into a 3x3 grid.
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                board[i][j] = ' ';
            }
            cout << '\n';
        }
    }
};

class Player {
private:
    char piece;
    string name;
public:
    Player() : piece(' '), name(" ") {} // Empty constructor 
    Player(char p, const string& n) : piece(p), name(n) {} // Normal constructor
    char getPiece() const { return piece; }
    const string& getName() const { return name; }
};
void displayRulesAndInstructions() {
    cout << "\n=== TIC-TAC-TOE RULES & INSTRUCTIONS ===\n\n";
    cout << "OBJECTIVE:\n";
    cout << "Be the first player to get 3 of your marks in a row\n";
    cout << "(horizontally, vertically, or diagonally)\n\n";

    cout << "HOW TO PLAY:\n";
    cout << "1. Players take turns placing their mark (X or O)\n";
    cout << "2. Enter row number (1-3) and column number (1-3)\n";
    cout << "3. The board coordinates are as follows:\n\n";

    // Show example board with coordinates
    cout << "   1 2 3\n";
    cout << "1: . . .\n";
    cout << "2: . . .\n";
    cout << "3: . . .\n\n";

    cout << "EXAMPLE: To place your mark in the center, enter:\n";
    cout << "Row: 2\n";
    cout << "Column: 2\n\n";

    cout << "WINNING CONDITIONS:\n";
    cout << "- Three in a row horizontally\n";
    cout << "- Three in a row vertically\n";
    cout << "- Three in a row diagonally\n\n";

    cout << "If all spaces are filled with no winner, it's a tie!\n";
    cout << "============================================\n\n";
}

string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
        [](unsigned char c) { return tolower(c); });
    return lowerStr;
}

// Function to convert string to uppercase
string toUpper(const string& str) {
    string upperStr = str;
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(),
        [](unsigned char c) { return toupper(c); });
    return upperStr;
}
int main() {
    /*
    TODO:
        implement player classes
        create turn switcher
        create win checker
        refine game loop
        fix error message when you input multichar strings
    */
    cout << "Hello, Tic-tac-toe!\n"; // comment explaining what you did
    string choice;
    bool toPlay = false;
    do {
        cout << "Enter \"Rules\" to read the Rules\nOR\nEnter \"Play\" to Play" << endl;
        cin >> choice;
        if (toLower(choice)._Equal("rules")) {
            displayRulesAndInstructions();
        }
        else if (toLower(choice)._Equal("play"))
        {
            toPlay = true;
        }
        else {
            cout << "Invalid input" << endl;
        }
        cin.clear();
    } while (toPlay == false);
    toPlay = false;
    // --- Player initialization ---
    string p1Name, p2Name;
    cout << "Enter Player 1 name (plays as X): ";
    cin >> p1Name;
    cout << "Enter Player 2 name (plays as O): ";
    cin >> p2Name;

    Player p1('X', p1Name);
    Player p2('O', p2Name);

    Board b; //Initialize the board 
    bool play = true;
    char turn = 'X';

    auto nameFor = [&](char piece) -> const string& {
        return (piece == 'X') ? p1.getName() : p2.getName();
        };
    size_t row, col;  // <--- declare ONCE
    bool repeatPlay = false;
    do {
        while (play) { // Print the board
            b.print();

            cout << nameFor(turn) << " (" << turn << ") - select a row: ";
            while (!(cin >> row)) { // Input validation for rows
                cout << "Invalid input. Enter a number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << nameFor(turn) << " (" << turn << ") - select a column: ";
            while (!(cin >> col)) { // Input validation for colums
                cout << "Invalid input. Enter a number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (!b.changeAtPosition(row, col, turn)) {
                // invalid move; same player tries again
                continue;
            }

            char state = b.checkGameState();
            if (state == 'X' || state == 'O') {
                b.print();
                cout << nameFor(state) << " wins!\n";
                play = false;
            }
            else if (state == 'T') {
                b.print();
                cout << "It's a tie.\n";
                play = false;
            }
            else {
                turn = (turn == 'X') ? 'O' : 'X';
            }
        }
        string replayChoice = "";
        bool validReplayChoice = false;
        do {
            cout << "Would you like to play again? Y/N" << endl;
            cin >> replayChoice;
            if (toLower(replayChoice)._Equal("y")) {
                repeatPlay = true;
                play = true;
                b.clear();
                validReplayChoice = true;
            }
            else if (toLower(replayChoice)._Equal("n"))
            {
                repeatPlay = false;
                validReplayChoice = true;
            }
            else {
                cout << "Invalid input" << endl;
            }
        } while (validReplayChoice == false);
        replayChoice = "";
    } while (repeatPlay);
    cout << "Thank you for playing!!!\nGoodbye!!!" << endl;
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