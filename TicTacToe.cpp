//============================================================================
// Name        : TicTacToe.cpp
// Author      : Jacob Shnaidman
// Version     :
// Copyright   : Steal this as much as you want
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "TicTacToe.h"




TicTacToe::TicTacToe(): playerOne(TicTacToe::z), playerTwo(TicTacToe::z) {
	for (int i = 0; i<3;i++){
		for(int j=0;j<3;j++){
			this->board[i][j] = TicTacToe::z;
		}
	}
}

//place X or O on board
void TicTacToe:: place(XO player, vector<int> pos){
	if(this->board[pos[0]][pos[1]] != TicTacToe::z){
		cout << "\n Place taken, try again";
		this->place(player,pos);
	}
	this->board[pos[0]][pos[1]] = player;
};

//evalautes who won the game, X or O.
//if nobody has won, then z is returned.
TicTacToe::XO TicTacToe::winner(){
	//if diagonals are thought of as a linear equations on a graph,
	//pDiagonalCount looks like a diagonal with a positive slope
	//nDiagonalCount looks like a diagonal with a negative slope
	int pDiagonalCount = 0;
	int nDiagonalCount = 0;
	for(int i=0;i<3;i++){
		int horizontalCount = 0;
		int verticalCount = 0;
		//each iteration of i will scan a new row and column simultaneously
		//if two adjacent spots in a column or a row are the same and not empty (equal to z)
		// then add one to the count of horizontal/vertical matches
		XO tempHorizontal = this->board[i][0];
		XO tempVertical = this->board[0][i];
		for(int j=1;j<3;j++){
			if(this->board[i][j] == tempHorizontal && this->board[i][j] != z){
				horizontalCount++;
			}
			if (this->board[j][i] == tempVertical && this->board[j][i] != z){
				verticalCount++;
			}
		}
		//if more than two comparisons come back true, then someone has three in a row and has won
		// returns the winner, or z if there is no winner
		if (horizontalCount == 2){
			return this->board[i][0];
		}
		if (verticalCount == 2){
			return this->board[0][i];
		}
		//checks both diagonals for matches
		if(this->board[i][2-i] == this->board[0][2] && this->board[i][2-i] != z){
			pDiagonalCount++;
		}
		if(this->board[2-i][i] == this->board[2][0] && this->board[2-i][i] != z){
			nDiagonalCount++;
		}
	}
	//if there are more than 3 matches, return the winner
	if(nDiagonalCount == 3 || pDiagonalCount ==3){
		return this->board[1][1];
	}
	return z;
}

vector<int> TicTacToe::receiveInputPosition(){
	string posString;
	cout<< "Enter a position (e.g: 1,2)\n";
	cin>>posString;
	cout<<"\n";
	if(posString.length()>3){
		cout<< "The input has string length " << posString.length();
		cout<< "Invalid Position, try again\n";
		return receiveInputPosition();
	}
	if(posString.at(0)<48 || posString.at(0) > 57){
		cout << "Invalid position, try again\n";
		return receiveInputPosition();
	}
	if(posString.at(2)<48 || posString.at(2) > 57){
		cout << "Invalid position, try again\n";
		return receiveInputPosition();
	}
	vector<int> pos(2);
	pos[0] = posString.at(0)-48;
	pos[1] = posString.at(2)-48;
	return pos;
}

TicTacToe::XO TicTacToe::pickSymbol(){
	string playerOneSymbol;
	cout<< "Player one, choose X or O \n";
	cin>> playerOneSymbol;
	if(playerOneSymbol.length()>1){
		cout << "Symbol must be X or O and input must not be longer than one character";
	}
	int rawCharChosen = playerOneSymbol.at(0);
	if(rawCharChosen != 120 && rawCharChosen != 111 &&
			rawCharChosen != 88 && rawCharChosen != 79){
		cout << "Invalid character chosen, pick again";
		return pickSymbol();
	}
	if(rawCharChosen == 120 || rawCharChosen == 88){
		return TicTacToe::X;
	}
	else return TicTacToe::O;
}

void TicTacToe::printBoard(){
	for(int i = 0; i<3;i++){
		for(int j=0; j<3;j++){
			cout<< (char) this->board[i][j] << " ";
		}
		cout<<"\n";
	}
	cout<<"\n";
}

//playerOne goes first
TicTacToe::XO TicTacToe::playGame(){
	XO winner = TicTacToe::z; //z is used as default enum value
	playerOne=this->pickSymbol();
	if(playerOne == TicTacToe::X){
		playerTwo = TicTacToe::O;
	}
	else playerTwo = TicTacToe::X;
	for(int turn = 1; turn<=9; turn++){
		this->printBoard();
		if(turn%2 == 1){
			cout<< "Player One, please Enter a position you would like to place your piece\n";
			this->place(playerOne,receiveInputPosition());
		}
		else {
			cout<< "Player Two, please Enter a position you would like to place your piece\n";
			this->place(playerTwo,receiveInputPosition());
		}
		//returns enum XO of player that won, or z if no winner
		winner = TicTacToe::winner();
		if(winner != TicTacToe::z){
			printBoard();
			cout<< "Player " << (char) winner<< " has won!";
			return winner;
		}
	}
	return winner;
}
