BIN = ./bin
OUT = main
CXX = g++ --std=c++11

$(OUT): main.o game_manager.o game_board.o
	$(CXX) $(BIN)/*.o -o $@ -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp 
	$(CXX) -c $< -o $(BIN)/$@

game_manager.o

makedir:
	mkdir $(BIN)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OUT)
