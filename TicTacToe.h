/*
 * TicTacToe.h
 *
 *  Created on: Nov 4, 2016
 *      Author: jshnaidman
 */

#ifndef TICTACTOE_H_
#define TICTACTOE_H_

//these represent both players and board-pieces
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



class TicTacToe{

public:
	enum XO {
		O=79,
		X=88,
		z = 90};
	TicTacToe();
	TicTacToe::XO playGame();

private:
	XO playerOne;
	XO playerTwo;
	XO board[3][3];
	void printBoard();
	void place(XO player, vector<int> pos);
	XO winner();
	vector<int> receiveInputPosition();
	XO pickSymbol();
};
#endif /* TICTACTOE_H_ */
