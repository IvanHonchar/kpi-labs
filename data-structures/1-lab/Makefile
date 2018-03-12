test: test.o
	g++ test.o -o test

test.o: test.cpp
	g++ -std=gnu++0x -c test.cpp

clean:
	rm -rf *.o test
