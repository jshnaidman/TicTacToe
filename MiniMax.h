/*
 * MiniMax.h
 *
 *  Created on: Nov 5, 2016
 *      Author: jshnaidman
 */

#ifndef MINIMAX_H_
#define MINIMAX_H_
#include "math.h"
#include <stdlib.h>
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
    static XO isTerminal(vector<vector<XO>> board); //method returns the winner or false if it is not a terminal state.
    static int utility(XO winner, XO player);
    static vector<vector<XO>> result(Action action, vector<vector<XO>> board);
    static int maxValue(vector<vector<XO>> board, XO player);	//returns the max value of a state
    static int minValue(vector<vector<XO>> board, XO player);	//returns the min value of a state
    static vector<int> miniMax(vector<vector<XO>> board, XO player); //returns a pair of coordinates x,y that represent the best move for player
    static vector<vector<int>> successors(vector<vector<XO>> board);
    static XO other(XO player);
};
#endif /* MINIMAX_H_ */