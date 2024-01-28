#include <iostream>
#include <string>
#include <algorithm> 
#include <vector>    

using namespace std;

void gameboard(char board[]);
bool checkwin(char board[], char& winner);

int main()
{
    string player1, player2;
    char symbol1 = 'O', symbol2 = 'X';
    char winner = ' ';
  
    cout << "Enter Name of player 1: ";
    cin >> player1;
    cout << "Enter Name of player 2: ";
    cin >> player2;
    system("cls");
    char board[] = { '0','1','2','3','4','5','6','7','8','9' };
    gameboard(board);

    int position;
    vector<int> moves;

    for (int i = 1; i <= 9; i++)
    {
        if (i % 2 != 0)
        {
            cout << "Enter Position for player " << player1 << ": ";
            cin >> position;

            while (find(moves.begin(), moves.end(), position) != moves.end() || !(position >= 1 && position <= 9 && board[position] != symbol1 && board[position] != symbol2))
            {
                cout << "Invalid input. Enter Position for player " << player1 << ": ";
                cin >> position;
            }

            moves.push_back(position);
            system("cls");
            board[position] = symbol1;
        }
        else
        {
            cout << "Enter Position for player " << player2 << ": ";
            cin >> position;

            while (find(moves.begin(), moves.end(), position) != moves.end() || !(position >= 1 && position <= 9 && board[position] != symbol1 && board[position] != symbol2))
            {
                cout << "Invalid input. Enter Position for player " << player2 << ": ";
                cin >> position;
            }

            moves.push_back(position);
            system("cls");
            board[position] = symbol2;
        }

        gameboard(board);

        if (checkwin(board, winner))
        {
            if (winner == symbol1)
                cout << player1 << " wins!" << endl;
            else
                cout << player2 << " wins!" << endl;
            break;
        }
    }

    if (winner == ' ')
        cout << "It's a draw!" << endl;

    return 0;
}

void gameboard(char board[])
{
    cout << "     |     |      \n";
    cout << "   " << board[1] << " | " << board[2] << "   | " << board[3] << endl;
    cout << "_____|_____|______\n";
    cout << "     |     |      \n";
    cout << "   " << board[4] << " | " << board[5] << "   | " << board[6] << endl;
    cout << "_____|_____|______\n";
    cout << "     |     |      \n";
    cout << "   " << board[7] << " | " << board[8] << "   | " << board[9] << endl;
    cout << endl;
}

bool checkwin(char board[], char& winner)
{
    // Check rows
    for (int i = 1; i <= 7; i += 3)
    {
        if (board[i] == board[i + 1] && board[i + 1] == board[i + 2])
        {
            winner = board[i];
            return true;
        }
    }

    // Check columns
    for (int i = 1; i <= 3; i++)
    {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6])
        {
            winner = board[i];
            return true;
        }
    }

    // Check diagonals
    if ((board[1] == board[5] && board[5] == board[9]) || (board[3] == board[5] && board[5] == board[7]))
    {
        winner = board[5];
        return true;
    }

    // Check for draw
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] != 'X' && board[i] != 'O')
            return false;
    }

    winner = ' ';
    return true;
}
