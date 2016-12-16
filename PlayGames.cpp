/*
 * PlayGames.cpp
 *
 *  Created on: Nov 5, 2016
 *      Author: jshnaidman
 */
#include "TicTacToe.h"
#include "MiniMax.h"

int main() {
	vector < vector < XO >> board =  { {z, z, z},  {z, X, O},  {z, z, z}}; 
	vector < int > bestMove = MiniMax::miniMax(board, X); 
	printf("\nbest move is: %d,%d\n", bestMove[0], bestMove[1]); 
	return 0; 
}
