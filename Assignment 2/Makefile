output: assignment2.o
	g++ assignment2.o -o assignment2 -pthread

assignment1.o: assignment2.cpp
	g++ -c assignment2.cpp

LIBS=		-pthread

clean:
	rm *.o assignment2
