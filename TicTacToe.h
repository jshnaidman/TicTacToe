/*
 * TicTacToe.h
 *
 *  Created on: Nov 4, 2016
 *      Author: jshnaidman
 */

#ifndef TICTACTOE_H_
#define TICTACTOE_H_

//============================================================================
// Name        : TicTacToe.cpp
// Author      : Jacob Shnaidman
// Version     :
// Copyright   : Steal this as much as you want
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum XO {
	O=79,
	X=88,
	z = 90};

class TicTacToe{

public:
	TicTacToe();
	XO playGame();
	vector< vector<XO> > board;
	XO winner(vector<vector <XO> > board);
private:
	XO playerOne;
	XO playerTwo;
	void printBoard();
	void place(XO player, vector<int> pos);
	vector<int> receiveInputPosition();
	XO pickSymbol();
};
#endif /* TICTACTOE_H_ */
