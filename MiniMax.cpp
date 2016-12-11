/*
 * MiniMax.cpp
 *
 *  Created on: Nov 5, 2016
 *      Author: jshnaidman
 */

#include "MiniMax.h"

int utility(TicTacToe game,XO player){
	XO winningPlayer;
	winningPlayer = game.winner(game.board);
	if (winningPlayer == XO::z){
		return 0;
	}
	else if (winningPlayer == player){
		return 1;
	}
	else return -1;
}
