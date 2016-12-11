output: MiniMax.o TicTacToe.o PlayGames.o
	g++ MiniMax.o TicTacToe.o PlayGames.o -o output

MiniMax.o: MiniMax.cpp MiniMax.h
	g++ -c MiniMax.cpp

TicTacToe.o: TicTacToe.cpp TicTacToe.h
	g++ -c TicTacToe.cpp 

PlayGames.o: PlayGames.cpp
	g++ -c PlayGames.cpp

clean:
	rm *.o
