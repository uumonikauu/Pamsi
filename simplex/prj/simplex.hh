
#ifndef SIMPLEX_HH_
#define SIMPLEX_HH_

#include <vector>
#include <string>



/*!
 * \brief Klasa simplex posiada metody pozwalające na rozwiązywanie zadań metodą SIMPLEX.
 */
class simplex {

	std::vector<double> funkcja_max;
	std::vector<std::vector<double> > sim;
	std::vector<double> wynik;
	std::vector<double> wektor_ograniczen;
  std::vector<std::vector<double> > macierz;
	double wynik_max;
public:
  /*!
	 * \brief Metoda pozwalająca utworzyć simplex.
	 */
	void utworz_simplex();
  /*!
	 * \brief Metoda pozwalająca obliczyć simplex.
	 */
	bool oblicz_simplex();
	std::string usun_spacje(std::string str);
	std::vector<double> string_do_double(std::string str);
	friend std::ostream & operator <<(std::ostream &str_wy, simplex &klasa);
	friend std::istream & operator >>(std::istream &str_we, simplex &klasa);
};

#endif 
