#ifndef haszujaca_HH
#define haszujaca_HH


#include <string>

static const int rozmiartablicy = 10;

/*!
 * \file
 * \brief Definicja modułu odpowiedzialnego za implementacje tablicy asocjacyjnej na strukturze tablicy haszujacej.
 *
 *  Plik zawiera deklaracje klas oraz metod odpowiedzialnych za wykonywanie operacji na  
 *  tablicy asocjacyjnej.
 */


     template <class T>
     class Asocjacyjna     {
     private:

/*!
 * \brief Struktura tworzaca tablice asocjacyjna.
 *
 *  Struktura zajmujaca sie przechowywaniem elementow tablicy asocjacyjnej czyli 
 *  klucza, przypisanej do niego wartosci, a także wskaźniku na element następny. 
 */
	  struct item 
	  {
		string nazwa;
		T data;
		item* nastepny;
	  };

    item* TablicaHaszujaca[rozmiartablicy];

    public:

/*
 * \brief Konstruktor, który tworzy tablice asocjacyjna.
 *
 */
	Asocjacyjna();

/*!
 * \brief Metoda pozwalajaca na dodawanie nowego elementu do tablicy.
 *
 */
	bool Dodaj_Element(string nazwa, T data);

/*!
 * \brief Metoda pozwalajaca na sprawdzenie czy tablica jest pusta
 * 
 */
	bool Czy_Pusty();

/*!
 * \brief Metoda pozwalajaca na wyswietlenie elementow tablicy.
 *
 */
	bool WyswietlTablice();

/*!
 * \brief Metoda odpowiedzialna za haszowanie elementów tablicy.
 * 
 */
	int haszujaca(string klucz);

/*!
 * \brief Metoda odpowiedzialna za zliczanie elementow pod danym indeksem.
 * 
 */
	int ZliczElementy(int indeks);

/*!
 * \brief Metoda pozwalajaca wyszukac element w tablicy na podstawie klucza.
 * 
 */
	T WyszukajWartosc(string nazwa);

/*!
 * \brief Metoda pozwalajaca wyszukac klucz w tablicy na podstawie podanej wartosci.
 * 
 */
	bool ZanajdzKlucz(T data);

/*!
 * \brief Metoda pozwalajaca na usuwanie elementu z tablicy.
 *
 */
	bool UsunElement(string nazwa);



};

#endif
