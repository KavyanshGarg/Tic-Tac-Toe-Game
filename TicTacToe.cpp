#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Display the current game board
void displayBoard(const char board[3][3])
{
    cout << "\n";
    cout << "       TIC TAC TOE\n\n";

    for (int i = 0; i < 3; i++)
    {
        cout << "       ";

        for (int j = 0; j < 3; j++)
        {
            cout << " " << board[i][j] << " ";

            if (j < 2)
                cout << "|";
        }

        cout << "\n";

        if (i < 2)
            cout << "      ---+---+---\n";
    }

    cout << "\n";
}

// Check whether a player has won
bool checkWin(const char board[3][3], char player)
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
        {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == player &&
            board[1][j] == player &&
            board[2][j] == player)
        {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
    {
        return true;
    }

    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
    {
        return true;
    }

    return false;
}

// Take and validate a player's move
int getMove(const char board[3][3], char player)
{
    string input;
    int position;
    char extra;

    while (true)
    {
        cout << "Player " << player
             << ", choose a cell (1-9): ";

        if (!getline(cin, input))
            return 0;

        stringstream stream(input);

        if (!(stream >> position) ||
            (stream >> extra) ||
            position < 1 ||
            position > 9)
        {
            cout << "Invalid input. Enter a number from 1 to 9.\n";
            continue;
        }

        int row = (position - 1) / 3;
        int column = (position - 1) % 3;

        if (board[row][column] == 'X' ||
            board[row][column] == 'O')
        {
            cout << "That cell is already occupied. Try again.\n";
            continue;
        }

        return position;
    }
}

// Run one game
void playGame()
{
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char player = 'X';

    for (int turn = 0; turn < 9; turn++)
    {
        displayBoard(board);

        int position = getMove(board, player);

        // Handle end-of-input safely
        if (position == 0)
        {
            cout << "\nInput ended. Game closed.\n";
            return;
        }

        int row = (position - 1) / 3;
        int column = (position - 1) % 3;

        board[row][column] = player;

        // Check for a winner after each move
        if (checkWin(board, player))
        {
            displayBoard(board);

            cout << "Congratulations! Player "
                 << player << " wins!\n";

            return;
        }

        // Switch the player
        if (player == 'X')
            player = 'O';
        else
            player = 'X';
    }

    // All nine cells are filled and nobody won
    displayBoard(board);
    cout << "The game is a draw!\n";
}

// Main function
int main()
{
    string answer;

    cout << "================================\n";
    cout << "       TIC TAC TOE GAME\n";
    cout << "================================\n";
    cout << "Player 1: X\n";
    cout << "Player 2: O\n";

    do
    {
        playGame();

        cout << "\nWould you like to play again? (Y/N): ";

        if (!getline(cin, answer))
            break;

    } while (answer == "Y" || answer == "y");

    cout << "\nThanks for playing Tic Tac Toe!\n";

    return 0;
}