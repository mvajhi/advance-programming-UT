BIN = ./bin
OUT = main
CXX = g++ --std=c++11

$(OUT): main.o makedir
	$(CXX) $(BIN)/*.o -o $@ -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp makedir
	$(CXX) -c $< -o $(BIN)/$@

makedir:
	mkdir $(BIN)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OUT)
