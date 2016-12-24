#ifndef MINIMAX_H
#define MINIMAX_H
#include <cmath>
#include <cstdlib>
#include <limits>
#include <vector>
#include "XO.h"
#include "TicTacToe.h"

using namespace std;


struct Action
{
    vector<int> position;
    XO player;
    Action(vector<int> position, XO player);
    Action();
};

class MiniMax
{
  public:
    static XO isTerminal(vector<vector<XO>> &board); //method returns the winner or false if it is not a terminal state.
    static int utility(XO winner, XO player);
    static vector<vector<XO>> result(Action action, vector<vector<XO>> &board);
    static vector<int> miniMax(vector<vector<XO>> &board, bool maxPlayer, XO player); //returns a pair of coordinates x,y that represent the best move for player
    static vector<vector<int>> successors(vector<vector<XO>> &board);
};
#endif