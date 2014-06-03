#include "graf.h"
#include "przeszukiwanie.h"
#include <iostream>
#include "timer.h"

/*!
* \file
* \brief Plik ten zawiera glowna funkcje programu.
*/

int main(int argc, char** argv) {

	Graf cos(16);
	cos.dodaj_krawedz(0, 1, 1);
	cos.dodaj_krawedz(1, 4, 4);
	cos.dodaj_krawedz(4, 5, 5);
	cos.dodaj_krawedz(4, 6, 6);
	cos.dodaj_krawedz(4, 7, 7);
	cos.dodaj_krawedz(6, 8, 8);
	cos.dodaj_krawedz(7, 2, 9);
	cos.dodaj_krawedz(2, 15, 10);
	cos.dodaj_krawedz(2, 9, 11);
	cos.dodaj_krawedz(2, 10, 12);
	cos.dodaj_krawedz(0, 2, 2);
	cos.dodaj_krawedz(0, 3, 3);
	cos.dodaj_krawedz(3, 11, 13);
	cos.dodaj_krawedz(11, 13, 14);
	cos.dodaj_krawedz(11, 14, 15);
	cos.dodaj_krawedz(3, 12, 16);
	cos.dodaj_krawedz(12, 1, 17);

	timer(cos, 0, 15, std::cout);
	return 0;
}
