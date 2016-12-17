//============================================================================
// Name        : TicTacToe.cpp
// Author      : Jacob Shnaidman
// Version     :
// Copyright   : Steal this as much as you want
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "TicTacToe.h"
#include "MiniMax.h"

TicTacToe::TicTacToe() : playerOne(z), playerTwo(z), board(3, vector<XO>(3, z))
{
}

//place X or O on board
void TicTacToe::place(XO player, vector<int> pos)
{
    if (this->board[pos[0]][pos[1]] != z)
    {
        cout << "\n Place taken, try again";
        this->place(player, pos);
    }
    this->board[pos[0]][pos[1]] = player;
};

//evalautes who won the game, X or O.
//if nobody has won, then z is returned.
XO TicTacToe::winner(vector<vector<XO>> board)
{
    //if diagonals are thought of as a linear equations on a graph,
    //pDiagonalCount looks like a diagonal with a positive slope
    //nDiagonalCount looks like a diagonal with a negative slope
    int pDiagonalCount = 0;
    int nDiagonalCount = 0;
    for (int i = 0; i < 3; i++)
    {
        int horizontalCount = 0;
        int verticalCount = 0;
        //each iteration of i will scan a new row and column simultaneously
        //if two adjacent spots in a column or a row are the same and not empty (not equal to z)
        // then add one to the count of horizontal/vertical matches
        XO tempHorizontal = board[i][0]; //symbol from row i
        XO tempVertical = board[0][i];   //symbol from column i
        for (int j = 1; j < 3; j++)
        {
            if (board[i][j] != z && board[i][j] == tempHorizontal)
            {
                horizontalCount++;
            }
            if (board[j][i] != z && board[j][i] == tempVertical)
            {
                verticalCount++;
            }
        }
        //if two comparisons come back true, then someone has three in a row and has won
        // returns the winner, or z if there is no winner
        if (horizontalCount == 2)
        {
            return board[i][0];
        }
        if (verticalCount == 2)
        {
            return board[0][i];
        }
        //checks both diagonals for matches
        if (board[i][2 - i] == board[0][2] && board[i][2 - i] != z)
        {
            pDiagonalCount++;
        }
        if (board[2 - i][i] == board[2][0] && board[2 - i][i] != z)
        {
            nDiagonalCount++;
        }
    }
    //if there are more than 3 matches, return the winner
    if (nDiagonalCount == 3 || pDiagonalCount == 3)
    {
        return board[1][1];
    }
    return z;
}

vector<int> TicTacToe::receiveInputPosition(int attempt)
{
    string posString;
    if (attempt % 3 == 0)
    {
        this->printBoard();
    }
    cout << "Enter a position (e.g: 1,2)\n";
    cin >> posString;
    if (posString.length() > 3)
    {
        cout << "\n The input has string length " << posString.length() << "\n";
        cout << "Invalid Position, try again\n";
        return receiveInputPosition(attempt + 1);
    }
    if (posString.at(0) < 48 || posString.at(0) > 50)
    {
        cout << "Invalid position, try again\n";
        return receiveInputPosition(attempt + 1);
    }
    if (posString.at(2) < 48 || posString.at(2) > 50)
    {
        cout << "Invalid position, try again\n";
        return receiveInputPosition(attempt + 1);
    }
    vector<int> pos(2);
    pos[0] = posString.at(0) - 48;
    pos[1] = posString.at(2) - 48;
    if (this->isPositionTaken(pos[0], pos[1]))
    {
        cout << "Position Taken, try again\n";
        return receiveInputPosition(attempt + 1);
    }
    return pos;
}
bool TicTacToe::isPositionTaken(int row, int col)
{
    if (this->board[row][col] != z)
    {
        return true;
    }
    return false;
}

XO TicTacToe::pickSymbol()
{
    string playerOneSymbol;
    cout << "Player one, choose X or O \n"
         << "\nX goes first\n";
    cin >> playerOneSymbol;
    if (playerOneSymbol.length() > 1)
    {
        cout << "Symbol must be X or O and input must not be longer than one character";
        return pickSymbol();
    }
    int rawCharChosen = playerOneSymbol.at(0);
    //if it's not X or O lower/upper case
    if (rawCharChosen != 120 && rawCharChosen != 111 &&
        rawCharChosen != 88 && rawCharChosen != 79)
    {
        cout << "Invalid character chosen, pick again";
        return pickSymbol();
    }
    if (rawCharChosen == 120 || rawCharChosen == 88)
    {
        return X;
    }
    else
        return O;
}

bool TicTacToe::promptComputerEnabled()
{
    cout << "Would you like to play against the computer? (y/n)";
    string decision; 
    cin >> decision;

    if ( (char) decision.at(0) != 'y' && (char) decision.at(0) != 'n')
    {
        cout << "Decision must be y/n \n";
        return promptComputerEnabled();
    }

    if (decision.at(0) == 'y')
    {
        cout << "Player Two is the Computer\n";
        return true;
    }
    else
        return false;
}

void TicTacToe::printBoard()
{
    cout << "\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << (char)this->board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// TODO: can improve this if I give turn as argument
XO TicTacToe::playTurn()
{
    this->printBoard();
    bool isPlayerOne = false;
    if (&(*turn) == &playerOne)
    {
        isPlayerOne = true;
        cout << "Player One, please Enter a position you would like to place your piece\n";
        this->place(playerOne, receiveInputPosition(1));
    }
    else
    {
        cout << "Player Two, please Enter a position you would like to place your piece\n";
        this->place(playerTwo, receiveInputPosition(1));
    }
    //decide who goes next
    if (isPlayerOne)
    {
        turn = &playerTwo;
    }
    else
        turn = &playerOne;

    //returns enum XO of player that won, or z if no winner
    XO winningPlayer = this->winner(board);
    return winningPlayer;
}

XO TicTacToe::compTurn()
{
    vector<int> move = MiniMax::miniMax(board, playerTwo);
    this->place(playerTwo, move);

    turn = &playerOne;
    XO winningPlayer = this->winner(board);
    return winningPlayer;
}

//X goes first
XO TicTacToe::playGame()
{
    XO winningPlayer = z; //z is used as default enum value
    //decide if you want to play against the computer
    bool computerEnabled = TicTacToe::promptComputerEnabled();
    //player one picks X or O
    playerOne = this->pickSymbol();
    if (playerOne == X)
    {
        turn = &playerOne;
        playerTwo = O;
    }
    else
    {
        turn = &playerTwo;
        playerTwo = X;
    }

    //play 9 turns
    for (int turnNum = 1; turnNum <= 9; turnNum++)
    {
        XO winningPlayer;
        if (!computerEnabled)
        {
            winningPlayer = playTurn();
        }
        else
        {
            if (&(*turn) == &playerOne)
            {
                winningPlayer = playTurn();
            }
            else
            {
                winningPlayer = compTurn();
            }
        }
        if (winningPlayer != z)
        {
            printBoard();
            if(winningPlayer == playerOne){
                cout << "\n Player One has won!\n";
            }
            else{
                cout << "\n Player Two has won!\n";
            }
            return winningPlayer;
        }
    }
    cout << "Tie game!\n";
    return winningPlayer;
}

XO TicTacToe::getTurn()
{
    return *turn;
}

vector<vector<XO>> TicTacToe::getBoard()
{
    return this->board;
}
void TicTacToe::setBoard(vector<vector<XO>> board)
{
    if (!board.empty())
    {
        this->board = board;
    }
}