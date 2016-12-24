#include "MiniMax.h"

//constructor for action variable -
// position is the place that the action will place a piece
// player is either X or O, this decides what kind of symbol will be placed with this action
//this is not a necessary class but it was added for clarity
Action::Action(vector<int> position, XO player) : player(player)
{
    this->position.push_back(position[0]);
    this->position.push_back(position[1]);
}
//default constructor
Action::Action() : position(2, 0)
{
    player = z;
}

//prints board
static void printBoard(vector<vector<XO>> &board)
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
XO MiniMax::isTerminal(vector<vector<XO>> &board)
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
vector<vector<XO>> MiniMax::result(Action action, vector<vector<XO>> &board)
{
    vector<vector<XO>> result = board;
    result[action.position[0]][action.position[1]] = action.player;
    return result;
}
//returns the empty spots on the board that can be moved into
//TODO: this can be removed/improved if the TicTacToe object just stores successors that are empty and methods are passed TicTacToe objects
vector<vector<int>> MiniMax::successors(vector<vector<XO>> &board)
{
    vector<vector<int>> successors;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == z)
            {
                successors.push_back({i, j});
            }
        }
    }
    return successors;
}

//Minimax returns a position vector with the optimal place for a player to go
//this method assumes it is player's turn
//can be imporoved if successors is stored on game object and method is passed TicTacToe object.
vector<int> MiniMax::miniMax(vector<vector<XO>> &board, bool maxPlayer, XO player)
{
    vector<int> bestMove(3,0); //first two ints are the coordinates of the move, the last int is the utility value of the move

    XO state = MiniMax::isTerminal(board); //state is False if not a terminal state, else the winning player is returned (X or O or z if there is a tie)

//base case - terminal state
    if(state != False){
        int utility;
        if(maxPlayer){
            utility = MiniMax::utility(state,player);
        }
        else{
            utility = -MiniMax::utility(state,player);
        }
        bestMove[2] = utility;
        return bestMove;
    }

    vector<vector<int>> successors = MiniMax::successors(board); //array of x,y positions that player may place a piece, should never be empty (this is handled by TicTacToe class)
    if (maxPlayer)
    {
        bestMove[2] = numeric_limits<int>::min();
        for (vector<int> move : successors)
        {
            board[move[0]][move[1]] = player; //Place symbol of placer in spot defined by move
           vector<int> bestResponse = MiniMax::miniMax(board,false, !player); //!player gives X if O or gives O if X
            if(bestResponse[2]>bestMove[2]){ //return the move with utility that is the max(utility(min's response))
                bestMove[0] = move[0];
                bestMove[1] = move[1];
                bestMove[2] = bestResponse[2];
            }
            board[move[0]][move[1]] = z; //undo change to board that was done in calculation
        }
    }
    else
    {
        bestMove[2] = numeric_limits<int>::max();
        for(vector<int> move : successors){
            board[move[0]][move[1]] = player;
           vector<int> bestResponse = MiniMax::miniMax(board,true, !player); //!player gives X if O or gives O if X
           if(bestResponse[2]<bestMove[2]){
                bestMove[0] = move[0];
                bestMove[1] = move[1];
                bestMove[2] = bestResponse[2];
            }
            board[move[0]][move[1]] = z; //undo change to board that was done in calculation
        }
    }

    //after going through all possible actions, the move with the greatest utility is bestMove
    return bestMove;
}
