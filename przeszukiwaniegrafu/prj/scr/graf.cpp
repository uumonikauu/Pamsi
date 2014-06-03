/*!
*\file 
*\brief Definicje poszczegolnych funkcji dla klasy Graf.
*/

#include<list>
#include "graf.h"

Graf::Graf(int rozm) : rozm(rozm) { }

Graf::~Graf() {}
/*!
 * \brief Opis metody pozwalajacej na dodanie nowego wierzcholka.
 * 
 */
bool Graf::dodaj_wierzcholek (int V) {
	return true;
	}
/*!
 * \brief Opis metody pozwalajacej na usunięcie danego wierzcholka.
 * 
 */
bool Graf::usun_wierzcholek (int V) {
	return true;
	}
/*!
 * \brief Opis metody pozwalajacej na dodanie nowej krawedzi.
 * 
 */
bool Graf::dodaj_krawedz (int V1, int V2, double c) {
	dane[V1][V2] = c;
	dane[V2][V1] = c; 
	return true;
	}
/*!
 * \brief Opis metody pozwalajacej na usunięcie danej krawedzi.
 * 
 */
bool Graf::usun_krawedz (int V1, int V2) {
	dane[V1][V2] = 0;

	dane[V2][V1] = 0; 
	return true;
	}
/*!
 * \brief Opis metody pozwalajacej sprawdzic czy dany wierzcholek jest "sasiadem".
 * 
 */
double Graf::czy_sasiad (int V1, int V2) {
	return dane[V1][V2];
	}
/*!
 * \brief Opis metody pozwalajacej na sprawdzic sasiedztwo danego wierzcholka.
 * 
 */
     std::list<int> Graf::sasiedztwo (int V) {
	std::list<int> ret;
	for(int i = 0; i<rozm; i++)
		if(czy_sasiad(V, i)) ret.push_back(i);
	return ret;
	}

/*!
 * \brief Opis metody pozwalajacej sprawdzic rozmiar grafu.
 * 
 */

const int Graf::rozmiar() const {
	return rozm;
}
