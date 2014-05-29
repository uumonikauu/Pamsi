#include "haszujaca.hh"


/*!
 * \file
 * \brief Modul odpowiedzialny za implementacje tablicy asocjacyjnej na tablicy haszującej.
 *
 *  Plik zawiera opisy metod odpowiedzialnych za wykonywanie operacji na 
 *  tablicy asocjacyjnej.
 */

  template <class T>
  Asocjacyjna<T>::Asocjacyjna()
   {
	 for(int i=0; i<rozmiartablicy; i++)
	{
		TablicaHaszujaca[i] = new item;

		TablicaHaszujaca[i]->nazwa = "pusty";

    TablicaHaszujaca[i]->nastepny = NULL

		TablicaHaszujaca[i]->data = T(NULL);		
		
	}
}

  template <class T>
  bool Asocjacyjna<T>::Dodaj_Element(string nazwa, T data) {
	  if(!ZmienWartosc(nazwa, data))  {
		int indeks=0;
		indeks = haszujaca(nazwa);

		if(TablicaHaszujaca[indeks]->nazwa == "pusty")
		{
			TablicaHaszujaca[indeks]->data = data;	
			TablicaHaszujaca[indeks]->nazwa = nazwa;

		}
	
		else
		{
			item* Etr = TablicaHaszujaca[indeks];
			item* n = new item;
	    n->data = data;
			n->nazwa = nazwa;
			n->nastepny = NULL;

			while(Etr->nastepny != NULL)
			{
				Etr = Etr->nastepny;
			}
			Etr->nastepny = n;
		}
	}
	return true;
}

template <class T>
bool Asocjacyjna<T>::Czy_Pusty()
{
	int warosc=0;
	for(int i=0; i<rozmiartablicy; i++){
		if(TablicaHaszujaca[i]->nazwa != "pusty") warosc=1;
}
	if(warosc == 1) return false;
	else return true;
}

template <class T>
bool Asocjacyjna<T>::WyswietlTablice()
{
	if(!Czy_Pusty()) 
	{
	cout << endl << setw(20) << lewa << "klucz" << setw(20) << "Wartosc" << endl << endl;
	for(int i=0; i<rozmiartablicy; i++)
	{
		item* Etr = TablicaHaszujaca[i];
		while(Etr != NULL){
			cout << setw(20) << lewa << Etr->nazwa << setw(20) << Etr->data << endl;
			Etr = Etr->nastepny;
		}
		cout << endl;
	}
	return true;
	}
	else
	{
		cout << "Tablica jest pusta!" << endl;
		return false;
	}
}

  template <class T>
  int Asocjacyjna<T>::haszujaca(string klucz) {
	long int haszujaca=0;
	int indeks;
	
	for(unsigned int i=0; i<klucz.length(); i++)
	{
		haszujaca = (haszujaca + (int)klucz[i])*12;	
	}
	
	indeks = haszujaca % rozmiartablicy;

	return indeks;
  }


template <class T>
int Asocjacyjna<T>::ZliczElementy(int indeks)
{
	int count = 0;
	
	if(TablicaHaszujaca[indeks]->nazwa == "pusty"){
		return count;
	}
	
	else
	{
		count++;
		item* Etr=TablicaHaszujaca[indeks];
		while(Etr->nastepny != NULL) {
			count++;
			Etr=Etr->nastepny;
		}
	}
	return count;
}

template <class T>
T Asocjacyjna<T>::WyszukajWartosc(string nazwa) {
	int indeks = haszujaca(nazwa);
	bool znajdznazwe = false;
	T data;
	item* Etr=TablicaHaszujaca[indeks];
	cout << endl << setw(20) << lewa << "klucz" << setw(20) << "Wartosc" << endl << endl;	
	while(Etr != NULL)
	{
		if(Etr->nazwa == nazwa)
		{
			znajdznazwe = true;
			data=Etr->data;
		}
		Etr=Etr->nastepny;
	}
	if(znajdznazwe == true) {
		cout << setw(20) << lewa << nazwa << setw(20) << data << endl;
		return data;
	}
	else 
	{
		cout << "Nie znaleziono!" << endl;
		return T(NULL);
	}
}

template <class T>
bool Asocjacyjna<T>::ZanajdzKlucz(T data) {
	bool znajdznazwe = false;
	string nazwa;
	cout << endl << setw(20) << lewa << "klucz" << setw(20) << "Wartosc" << endl << endl;
	for(int i=0; i<rozmiartablicy; i++)
	{
		item* Etr = TablicaHaszujaca[i];
		while(Etr != NULL)
		{
			if(Etr->data == data)
			{
				znajdznazwe = true;
				nazwa = Etr->nazwa;
			}
			Etr = Etr->nastepny;
		}
	}
	if(znajdznazwe == true) {
		cout << setw(20) << lewa << nazwa << setw(20) << data << endl;
		return true;	
	}
	else
{
		cout << "Nie znaleziono!" << endl;
		return false;
	}
}
   template <class T>
   bool Asocjacyjna<T>::UsunElement(string nazwa)
    {
	int indeks = haszujaca(nazwa);
	item* delEtr;
  item* E2;
	item* E1;
	if(TablicaHaszujaca[indeks]->nazwa == "pusty" && TablicaHaszujaca[indeks]->data == T(NULL))
	{
		cout << "Podany klucz nie istnieje!" << endl;
		return false; 
	}
	 else if(TablicaHaszujaca[indeks]->nazwa == "pusty" && TablicaHaszujaca[indeks]->nastepny == NULL){
		TablicaHaszujaca[indeks]->nazwa = "pusty";
		TablicaHaszujaca[indeks]->data = T(NULL);
		cout << "Element został usunięty: " << nazwa << endl;
		return true;
	}

	 else if(TablicaHaszujaca[indeks]->nazwa == nazwa)	{
		delEtr = TablicaHaszujaca[indeks];
		TablicaHaszujaca[indeks] = TablicaHaszujaca[indeks]->nastepny;
		delete delEtr;
		cout << "Element został usunięty: " << nazwa << endl;
		return true;
	}
	else
	{
		E1 = TablicaHaszujaca[indeks]->nastepny;
		E2 = TablicaHaszujaca[indeks];

		while(E1 != NULL && E1->nazwa != nazwa){
			E2 = E1;
			E1 = E1->nastepny;
		}
		if(E1 == NULL) {
			cout << "Podany klucz nie istnieje!" << endl;
			return false;		
		}
		else
		{
			delEtr = E1;
			E1 = E1->nastepny;
			E2->nastepny = E1;
			delete delEtr;
			cout << "Element został usunięty: " << nazwa << endl;
			return true;

		}
	}


}

