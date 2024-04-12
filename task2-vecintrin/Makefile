all: myexp

logger.o: logger.cpp logger.h ECE521intrin.h ECE521intrin.cpp
	g++ -c logger.cpp

ECE521intrin.o: ECE521intrin.cpp ECE521intrin.h logger.cpp logger.h
	g++ -c ECE521intrin.cpp

myexp: ECE521intrin.o logger.o main.cpp
	g++ -I../common logger.o ECE521intrin.o main.cpp -o myexp

clean:
	rm -f *.o myexp *~
