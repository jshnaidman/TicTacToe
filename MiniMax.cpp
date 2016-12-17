/*
 * MiniMax.cpp
 *
 *  Created on: Nov 5, 2016
 *      Author: jshnaidman
 */

#include "MiniMax.h"

Action::Action(vector<int> position, XO player) : player(player)
{
    this->position.push_back(position[0]);
    this->position.push_back(position[1]);
}
Action::Action()
{
}

static void printBoard(vector<vector<XO>> board)
{
    cout << "\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << (char)board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

/*
this method returns X, O or z if it is a terminal state. 
Returning z indicates that there is a tie. X or O are the winners
Returning False indicates that the board is not in a terminal state

This removes the redundancy of checking the board in this method and again in the utility method.
*/
XO MiniMax::isTerminal(vector<vector<XO>> board)
{
    XO winner = TicTacToe::winner(board); //returns X or O if there is a winner; else returns z.
    if (winner != z)
    {
        return winner;
    }
    //check if it's a terminal state
    for (vector<XO> v : board)
    {
        for (XO symbol : v)
        {
            if (symbol == z)
            {
                //if there is an empty spot on the board (z), then it's not a terminal state
                return False;
            }
        }
    }
    //if there are no empty spots and no winners, then the result is a tie.
    return z;
}

int MiniMax::utility(XO winner, XO player)
{
    if (winner == z)
    {
        return 0;
    }
    else if (winner == player)
    {
        return 1;
    }
    else
        return -1;
}

vector<vector<XO>> MiniMax::result(Action action, vector<vector<XO>> board)
{
    vector<vector<XO>> result = board;
    result[action.position[0]][action.position[1]] = action.player;
    return result;
}

vector<int> MiniMax::miniMax(vector<vector<XO>> board, XO player)
{
    vector<int> bestMove(2);
    vector<vector<int>> successors = MiniMax::successors(board);

    int v = numeric_limits<int>::min();

    for (vector<int> move : successors)
    {
        vector<vector<XO>> possibleFutureState = board;                       //future state is the board state + next move, this line copies the board
        possibleFutureState[move[0]][move[1]] = player;                       //this line makes a move for player
        int possibleUtility = MiniMax::maxValue(possibleFutureState, player); //this is the utility of this move
        cout << possibleUtility << "\n";
        if (possibleUtility > v)
        { //if the utility is greater than previous greatest utility, this is a better move
            v = possibleUtility;
            bestMove[0] = move[0];
            bestMove[1] = move[1];
        }
    }
    //after going through all possible actions, the move with the greatest utility is bestMove
    return bestMove;
}

vector<vector<int>> MiniMax::successors(vector<vector<XO>> board)
{
    vector<vector<int>> successors;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == z)
            {
                vector<int> pos{i, j};
                successors.push_back(pos);
            }
        }
    }
    return successors;
}

int MiniMax::maxValue(vector<vector<XO>> board, XO player)
{
    Action bestAction;                     //to be returned
    int v = numeric_limits<int>::min();    //initialize to small number
    XO state = MiniMax::isTerminal(board); //if false, it's not terminal, else it represents who's won
    if (state == False)
    {
        vector<vector<int>> successors = MiniMax::successors(board); //all possible places to move
        for (vector<int> move : successors)
        {
            Action action(move, MiniMax::other(player));                                 //possible action that other player can make
            int actionUtility = MiniMax::minValue(result(action, board), action.player); //gives the utility of min's best move
            if (actionUtility > v)
            {
                v = actionUtility; //v will be the largest utility of all possible moves
            }
        }
    }
    else
    {
        v = utility(state, player); //if it's a terminal state return the utility of this move for max
    }
    return v;
}

int MiniMax::minValue(vector<vector<XO>> board, XO player)
{
    Action bestAction;
    int v = numeric_limits<int>::max();
    XO state = MiniMax::isTerminal(board);
    if (state == False)
    {
        vector<vector<int>> successors = MiniMax::successors(board);
        for (vector<int> move : successors)
        {
            Action action(move, MiniMax::other(player));
            int actionUtility = MiniMax::maxValue(result(action, board), action.player);
            if (actionUtility < v)
            {
                v = actionUtility;
            }
        }
    }
    else
    {
        v = utility(state, other(player)); //always calculate the utility for max
    }
    return v;
}

XO MiniMax::other(XO player)
{
    if (player == X)
    {
        return O;
    }
    else
        return X;
}
