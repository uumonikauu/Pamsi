
KOM=g++

__start__: program
	./program

program: obj obj/stos.o obj/sortowania.o obj/pomiary.o obj/main.o 
	$(KOM) -Wall -o program obj/stos.o obj/sortowania.o obj/pomiary.o obj/main.o -lrt

obj/stos.o: inc/stos.hh src/stos.cpp 
	$(KOM) -c -Wall -pedantic -iquote inc -o obj/stos.o src/stos.cpp 

obj/sortowania.o: inc/sortowania.hh src/sortowania.cpp
	$(KOM) -c -Wall -pedantic -iquote inc -o obj/sortowania.o src/sortowania.cpp 

obj/pomiary.o: inc/pomiary.hh src/pomiary.cpp
	$(KOM) -c -Wall -pedantic -iquote inc -o obj/pomiary.o src/pomiary.cpp

obj/main.o: inc/main.hh src/main.cpp
	$(KOM) -c -Wall -pedantic -iquote inc -o obj/main.o src/main.cpp 

obj:
	mkdir obj

clean:
	rm -f obj/* program

help:
	@echo
	@echo  " Dostarczony plik Makefile pozwala wywolac polecenie make"
	@echo  " w nastepujacy sposob:"
	@echo  
	@echo  "  make        - powoduje kompilacje, konsolidacje i uruchomienie programu,"
	@echo  "  make clean  - powoduj usuniecie produktow komilacji i konsolidacji."
	@echo
