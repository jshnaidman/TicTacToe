/*
 * MiniMax.cpp
 *
 *  Created on: Nov 5, 2016
 *      Author: jshnaidman
 */

#include "MiniMax.h"

int utility(TicTacToe::XO** state, TicTacToe::XO player){
	TicTacToe::XO winner = TicTacToe::winner(state);
	if (winner == TicTacToe::z){
		return 0;
	}
	else if (winner == player){
		return 1;
	}
	else return -1;
}
