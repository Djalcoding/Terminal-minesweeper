output: main.o graphics.o grid.o grid_element.o vectorUtils.o inputUtils.o logging.o
	g++ main.o graphics.o grid.o grid_element.o vectorUtils.o inputUtils.o logging.o -std=c++2c -o output 
	./output
main.o: main.cpp
	g++ -c main.cpp -std=c++2c
graphics.o: src/graphics.cpp src/graphics.h
	g++ -c src/graphics.cpp -std=c++2c
grid.o: src/grid.cpp src/grid.h
	g++ -c src/grid.cpp -std=c++2c
grid_element.o: src/grid_element.cpp src/grid_element.h
	g++ -c src/grid_element.cpp -std=c++2c
logging.o: src/logging.cpp src/logging.h
	g++ -c src/logging.cpp -std=c++2c
vectorUtils.o: lib/vectorUtils.cpp lib/vectorUtils.h
	g++ -c lib/vectorUtils.cpp -std=c++2c
inputUtils.o: lib/inputUtils.cpp lib/inputUtils.h
	g++ -c lib/inputUtils.cpp -std=c++2c

clean:
	rm *.o output
run:
	./output
