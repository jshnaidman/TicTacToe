OBJ = TicTacToe.o MiniMax.o
CPPFLAGS = -std=c++14 -g -O0
all: TTT
CXX = g++

TTT: $(OBJ)
		$(CXX) $(CPPFLAGS) $(OBJ) PlayGames.cpp -o output

%.o: %.cpp 
		$(CXX) -c $(CPPFLAGS) $< -o $@

TicTacToe.o: TicTacToe.h TicTacToe.cpp XO.h
		$(CXX) -c $(CPPFLAGS) TicTacToe.cpp -o $@

MiniMax.o: MiniMax.h MiniMax.cpp XO.h
		$(CXX) -c $(CPPFLAGS) MiniMax.cpp -o $@

clean: 
		rm *.o