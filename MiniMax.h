/*
 * MiniMax.h
 *
 *  Created on: Nov 5, 2016
 *      Author: jshnaidman
 */

#ifndef MINIMAX_H_
#define MINIMAX_H_
#include "TicTacToe.h"

int utility(TicTacToe *game, XO player);
int max(TicTacToe game); //returns the max value of a state
int min(TicTacToe game); //returns the min value of a state
#endif			 /* MINIMAX_H_ */
