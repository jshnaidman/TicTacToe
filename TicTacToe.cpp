//============================================================================
// Name        : TicTacToe.cpp
// Author      : Jacob Shnaidman
// Version     :
// Copyright   : Steal this as much as you want
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
using namespace std;



//place X or O on board
void place(Player player, int pos, TicTacToe game){
	if(game.board[pos] != z){
		cout << "\n Place taken, try again";
		place(player,pos,game);
	}
	if(player == X){
		game.board[pos] = X;
	}
	else{
		game.board[pos] = O;
	}
};

Player wonGame(TicTacToe game){
	for(int i=0;i<3;i++){
		int horizontalCount = 0;
		int verticalCount = 0;
		int diagonalCount = 0;
		XO tempHorizontal = game.board[i][0];
		XO tempVertical = game.board[0][i];
		for(int j=1;j<3;j++){
			if(game.board[i][j] == tempHorizontal){
				horizontalCount++;
			}
			if (game.board[i][j] == tempVertical){
				verticalCount++;
			}
		}
		if (horizontalCount == 2){
			return true;
		}
		if (verticalCount == 2){
			return true;
		}
		if(game.board[i][2-i])
	}
}
