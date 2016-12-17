CXX=g++
CPPFLAGS=-std=c++11 -c -g -Wall
Objects=MiniMax.o TicTacToe.o PlayGames.o

output: MiniMax.o TicTacToe.o PlayGames.o
	$(CXX) $(Objects) -o output

MiniMax.o: MiniMax.cpp MiniMax.h XO.h

TicTacToe.o: TicTacToe.cpp TicTacToe.h XO.h

PlayGames.o: PlayGames.cpp

clean:
	rm *.o
