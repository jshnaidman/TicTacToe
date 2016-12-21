/*
 * MiniMax.cpp
 *
 *  Created on: Nov 5, 2016
 *      Author: jshnaidman
 */

#include "MiniMax.h"

//constructor for action variable - 
// position is the place that the action will place a piece
// player is either X or O, this decides what kind of symbol will be placed with this action
Action::Action(vector<int> position, XO player) : player(player)
{
    this->position.push_back(position[0]);
    this->position.push_back(position[1]);
}
//default constructor
Action::Action()
{
}

//prints board
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

//calculates the utility of a terminal state for a player.
//utility if: player wins -> 1, player ties -> 0, player loses -> -1
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

//returns the result of taking an action on the board (placing a piece)
//TODO: instead of creating a new board, just change the board traversing down tree and unchange it traversing up tree
vector<vector<XO>> MiniMax::result(Action action, vector<vector<XO>> board)
{
    vector<vector<XO>> result = board;
    result[action.position[0]][action.position[1]] = action.player;
    return result;
}

//Minimax returns a position vector with the optimal place for a player to go
//this method assumes it is player's turn
//TODO: this could be written as a single method instead of calling min and max
vector<int> MiniMax::miniMax(vector<vector<XO>> board, XO player)
{
    vector<int> bestMove(2);
    vector<vector<int>> successors = MiniMax::successors(board); //array of positions that player may place a piece, should never be empty (this is handled by TicTacToe class)

    int v = numeric_limits<int>::min();

    for (vector<int> move : successors)
    {
        vector<vector<XO>> possibleFutureState = board;                       //future state is the board state + next move, this line copies the board
        possibleFutureState[move[0]][move[1]] = player;                       //this line makes a move for player
        int possibleUtility = MiniMax::maxValue(possibleFutureState, player); //this is the utility of this move
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

//returns the empty spots on the board that can be moved into
//TODO: this can be removed if the TicTacToe object just stores successors that are empty
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

//maxValue returns the move that will maximize the utility of player
int MiniMax::maxValue(vector<vector<XO>> board, XO player)
{
    Action bestAction;                     //to be returned
    int v = numeric_limits<int>::min();    //initialize to small number
    XO state = MiniMax::isTerminal(board); //if false, it's not terminal, else it returns who's won or if there's a tie
    if (state == False)
    {
        vector<vector<int>> successors = MiniMax::successors(board); //all possible places to move
        for (vector<int> move : successors)
        {
            Action action(move, MiniMax::other(player));                                 //possible action that other player can make
            int actionUtility = MiniMax::minValue(result(action, board), action.player); //gives the utility of min's best move (min's best move will minimize player's utility)
            if (actionUtility > v) //want to return the move with the most utility
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
//minValue returns the move that will minimize the utility for the other player (max's utility)
int MiniMax::minValue(vector<vector<XO>> board, XO player)
{
    Action bestAction; //best action to be returned is the one that minimizes the utility
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
        v = -utility(state, player); //always calculate the utility for max, so it's negative
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
