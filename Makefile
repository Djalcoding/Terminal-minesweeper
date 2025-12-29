output: main.o graphics.o grid.o grid_element.o vectorUtils.o
	g++ main.o graphics.o grid.o grid_element.o vectorUtils.o -std=c++20 -o output 
	./output
main.o: main.cpp
	g++ -c main.cpp -std=c++20
graphics.o: src/graphics.cpp src/graphics.h
	g++ -c src/graphics.cpp -std=c++20
grid.o: src/grid.cpp src/grid.h
	g++ -c src/grid.cpp -std=c++20
grid_element.o: src/grid_element.cpp src/grid_element.h
	g++ -c src/grid_element.cpp -std=c++20
vectorUtils.o: lib/vectorUtils.cpp lib/vectorUtils.h
	g++ -c lib/vectorUtils.cpp -std=c++20

clean:
	rm *.o output
run:
	./output
