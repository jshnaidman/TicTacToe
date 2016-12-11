output: MiniMax.o TicTacToe.o PlayGames.o
	g++ -std=c++11 MiniMax.o TicTacToe.o PlayGames.o -o output

MiniMax.o: MiniMax.cpp MiniMax.h
	g++ -std=c++11 -c MiniMax.cpp

TicTacToe.o: TicTacToe.cpp TicTacToe.h
	g++ -std=c++11 -c TicTacToe.cpp 

PlayGames.o: PlayGames.cpp
	g++ -std=c++11 -c PlayGames.cpp

clean:
	rm *.o
