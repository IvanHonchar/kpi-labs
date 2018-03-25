OBJ_FLAGS = -std=gnu++0x -c

test: test.o graph.o
	g++ test.o graph.o -o test

test.o: test.cpp
	g++ $(OBJ_FLAGS) test.cpp

graph.o: graph.cpp
	g++ $(OBJ_FLAGS) graph.cpp

clean:
	rm -rf *.o draft test
