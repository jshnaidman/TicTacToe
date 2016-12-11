/*
 * TicTacToe.h
 *
 *  Created on: Nov 4, 2016
 *  Last Edit: Dec 11, 2016
 *      Author: jshnaidman
 */

#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum XO
{
    O = 79,
    X = 88,
    z = 90
};

class TicTacToe
{

  public:
    vector<vector<XO> > board;

    TicTacToe();
    TicTacToe(XO playerOne, XO playerTwo, vector< vector <XO> > board);
    XO playGame();
    XO winner(vector<vector <XO> > board);
    XO getTurn();

  private:
    XO playerOne;
    XO playerTwo;
    XO *turn;

    void printBoard();
    void place(XO player, vector<int> pos);
    vector<int> receiveInputPosition(int attempt);
    XO pickSymbol();
	bool positionTaken(int row, int col);
};
#endif /* TICTACTOE_H_ */
