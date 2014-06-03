/*!
*\file
*\brief Definicja modułu odpowiedzialnego za implementacje przeszukiwania.
*/


#include  "graf.h"
#include <list>
#include <iostream>



std::list<int> breadth_first(Graf& cos, const int rozpoczecie, const int zakonczenie);
std::list<int> depth_first(Graf& cos, int rozpoczecie, int zakonczenie, std::list<int> historia);
std::list<int> depth_first(Graf& cos, int rozpoczecie, int zakonczenie);
/*!
 * \brief Metoda pozwalajaca na policzenie kosztu drogi czy ona sie oplaca.
 * 
 */
double liczKoszt(Graf& cos, std::list<int> droga);

std::list<int> a_star(Graf& cos, int rozpoczecie, int zakonczenie);
