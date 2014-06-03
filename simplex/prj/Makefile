PROG=simplex

__start__: ${PROG} 
	./simplex

${PROG}: main.o simplex.o
	g++ -Wall -o ${PROG} main.o simplex.o

simplex.o: simplex.hh simplex.cpp
	g++ -c -Wall -pedantic -iquote inc -o simplex.o simplex.cpp

main.o: simplex.hh main.cpp 
	g++ -c -Wall -pedantic -Iinc -o main.o main.cpp
