/*!
*\file 
*\brief Definicja modułu odpowiedzialnego za implementacje Grafu. 
*
*Plik zawiera deklaracje klas oraz metod odpowiedzialnych za wykonywanie operacji na Grafie.
*/
#ifndef GRAF_H
#define GRAF_H
#include<list>

/*!
*\brief Deklaracje klasy Graf.
*/

 class Graf {
		double dane [1000][1000];
		int rozm;
	 public:
		Graf(int rozm);
		~Graf();
/*!
 * \brief Metoda pozwalajaca na dodawanie nowego wierzcholka.
 * 
 */
		bool dodaj_wierzcholek (int V);
/*!
 * \brief Metoda pozwalajaca na usuwanie danego wierzcholka.
 * 
 */
    bool usun_wierzcholek (int V);
/*!
 * \brief Metoda pozwalajaca na dodawanie nowej krawedzi.
 * 
 */
		bool dodaj_krawedz (int V1, int V2, double c);
/*!
 * \brief Metoda pozwalajaca na usuwanie danej krawedzi.
 * 
 */
		bool usun_krawedz (int V1, int V2);
/*!
 * \brief Metoda pozwalajaca na sprawdzic czy dany wierzcholek jest "sasiadem".
 * 
 */
		double czy_sasiad (int V1, int V2);
/*!
 * \brief Metoda pozwalajaca na sprawdzic "sasiedztwo" danego wierzcholka.
 * 
 */
		std::list<int> sasiedztwo (int V);
/*!
 * \brief Metoda pozwalajaca na sprawdzenie rozmiaru.
 * 
 */
		const int rozmiar() const;
};
#endif
