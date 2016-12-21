/*
 * TicTacToe.h
 *
 *  Created on: Nov 4, 2016
 *  Last Edit: Dec 11, 2016
 *      Author: jshnaidman
 */

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <string>
#include <vector>
#include "XO.h"

using namespace std;

class MiniMax;

class TicTacToe
{

public:
  vector<vector<XO>> board;

  TicTacToe();
  XO playGame();
  XO playTurn();
  XO compTurn();
  static XO winner(vector<vector<XO>> board);
  XO getTurn();
  void setBoard(vector<vector<XO>> board);
  vector<vector<XO>> getBoard();

private:
  XO playerOne;
  XO playerTwo;
  XO *turn;

  void printBoard();
  void place(XO player, vector<int> pos);
  vector<int> receiveInputPosition(int attempt);
  XO pickSymbol();
  int promptComputerEnabled();
  bool isPositionTaken(int row, int col);
};
#endif /* TICTACTOE_H_ */
