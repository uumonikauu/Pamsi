all: graf.o main.o przeszukiwanie.o timer.o
	clang++ graf.o main.o przeszukiwanie.o timer.o -Wall -std=c++11
graf.o: graf.h graf.cpp
	clang++ -c graf.cpp -Wall -std=c++11
main.o: main.cpp
	clang++ -c main.cpp -Wall -std=c++11
przeszukiwanie.o: przeszukiwanie.h przeszukiwanie.cpp
	clang++ -c przeszukiwanie.cpp -Wall -std=c++11
timer.o: timer.h timer.cpp
	clang++ -c timer.cpp -Wall -std=c++11
