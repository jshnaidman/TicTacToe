/*
 * TicTacToe.h
 *
 *  Created on: Nov 4, 2016
 *      Author: jshnaidman
 */

#ifndef TICTACTOE_H_
#define TICTACTOE_H_

enum Player { X,O,Z };
enum XO {X,O,z};

struct TicTacToe{
public:
	TicTacToe(): playerX(X), playerO(O) {
		for (int i = 0; i<3;i++){
			for(int j=0;j<3;j++){
				board[i][j] = z;
			}
		}
	}

private:
		Player playerX;
		Player playerO;
		XO board[3][3];
};

void place(Player player, int pos, TicTacToe game);

#endif /* TICTACTOE_H_ */
