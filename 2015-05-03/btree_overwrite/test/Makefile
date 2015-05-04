all:main

main: main.o
	g++ -g -std=c++11 main.o -o main

main.o: main.cpp
	g++ -c -g -std=c++11 main.cpp

clean:
	rm *.o *~ main
