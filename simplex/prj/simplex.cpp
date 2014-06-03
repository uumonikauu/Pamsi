#include <iostream>
#include <cstdlib>
#include "simplex.hh" 

using namespace std;

/*!
 * \brief Pobiera dane od uzytkownika a nastepnie tworzy macierz simplex.
 *
 */
     istream & operator >>(istream &str_we, simplex &klasa)
{
	int ilosc_rownan;
	string tmp;
	cout << "Podaj ilosc rownan:\n";
	str_we >> ilosc_rownan;
	for(int i = 1;i<=ilosc_rownan;++i)
	{
	cout << "Podaj wartosci wektora numer " << i << ":\n";
	str_we >> tmp;
	klasa.macierz.push_back(klasa.string_do_double(tmp));
	}
	cout << "Podaj wartosci funkcji maksymalnej:\n";
	str_we >> tmp;
	klasa.funkcja_max = klasa.string_do_double(tmp);
	cout << "Podaj wartosci wektora ograniczen:\n";
	str_we >> tmp;
	klasa.wektor_ograniczen = klasa.string_do_double(tmp);
	klasa.utworz_simplex();
	return str_we;
}

/*!
 * \brief Metoda podaje wynik operacji
 *
 */
  ostream & operator <<(ostream &str_wy, simplex &klasa)
  {
	cout << "Wynik maksymalny = " << klasa.wynik_max <<"\n";
	for(int i = 0; i < klasa.wynik.size(); ++i)
	{
		cout << "x" << i << "=" << klasa.wynik[i] << "\n";
	}
	return str_wy;
  }

/*!
 * \brief Metoda tworzy macierz simplex na podstawie otrzymanych danych wejsciowych
 */
  void simplex::utworz_simplex()
  {
	  int ilosc_zmiennych = this->funkcja_max.size();
	  int ilosc_rownan = this->macierz.size();
	  int liczba_kolumn = ilosc_zmiennych + ilosc_rownan + 1 + 1;
	  for(int i = 0; i < ilosc_rownan; ++i)
	  {
		vector<double> wiersz(liczba_kolumn, 0);
		for(int j = 0; j < ilosc_zmiennych; ++j)
		{
			wiersz[j] = this->macierz[i][j];
		}
		wiersz[ilosc_zmiennych + i] = 1;
		wiersz[liczba_kolumn - 1] = wektor_ograniczen[i];
		this->sim.push_back(wiersz);
	  }
	  vector<double> ostatni_wiersz(liczba_kolumn, 0);
	  for(int i = 0; i < ilosc_zmiennych; ++i)
	  {
		ostatni_wiersz[i] = 0 - this->funkcja_max[i];
	  }
	  ostatni_wiersz[ilosc_zmiennych + ilosc_rownan] = 1;
	  this->sim.push_back(ostatni_wiersz);
}


/*!
 * \brief Metoda oblicza rozwiązanie oraz uzyskaną wartość maksymalną
 *
 */
bool simplex::oblicz_simplex()
{
	int kolumna_wierzcholka, wiersz_wierzcholka;
	int liczba_wierszy = sim.size();
	int liczba_kolumn = sim[0].size();
	int i;
	bool brak_rozwiazania = false;
	double wierzcholek;
	while( (brak_rozwiazania = znajdz_wierzcholki(kolumna_wierzcholka, wiersz_wierzcholka)) )
	{
		wierzcholek = sim[wiersz_wierzcholka][kolumna_wierzcholka];
		for(i = 0; i < liczba_kolumn; ++i)
		{
			sim[wiersz_wierzcholka][i] /= wierzcholek;
		}
		for(i = 0; i < liczba_wierszy; ++i)
		{
			if(i != wiersz_wierzcholka)
			{
				double odniesienie =  -1 * sim[i][kolumna_wierzcholka];
				for(int j = 0; j < liczba_kolumn; j++)
				{
					sim[i][j] = sim[wiersz_wierzcholka][j] * odniesienie + sim[i][j];
				}
			}
		}
	}
	if(brak_rozwiazania)
	{
		return !brak_rozwiazania;
	}
	this->wynik_max = sim[liczba_wierszy-1][liczba_kolumn-1];
	int liczba_zmiennych = liczba_kolumn - liczba_wierszy - 1;
	vector<double> x(liczba_zmiennych, 0);
	bool jest_liczba;
	bool pierwszy;
	double war;
	for(int i = 0; i < liczba_zmiennych; ++i)
	{
		jest_liczba = true;
		pierwszy = true;
		war = 0;
		for(int j = 0; j < liczba_wierszy; ++j)
		{
			if(sim[j][i] == 1.0 && pierwszy)
			{
				pierwszy = false;
				war = sim[j][liczba_kolumn - 1];
			}
			else if(sim[j][i] != 0.0)
			{
				jest_liczba = false;
			}
		}
		if(jest_liczba && !pierwszy)
			x[i] = war;
		else
			x[i] = 0.0;
	}
	wynik = x;
	return brak_rozwiazania;
}

/*!
 * \brief Metoda pobiera dane ze stringa a następnie umieszcza je w wektorze
 * 
 */
vector<double> simplex::string_do_double(string str)
{
	vector<double> wek;

	while(str.length() > 0)
	{
		int pos = str.find(",");
		if (pos!=string::npos)
		{
			string liczba = str.substr(0, pos);
			liczba = usun_spacje(liczba);
			wek.push_back(atof(liczba.c_str()));
			str = str.substr(pos+1);
		}
		else
		{
			string liczba = usun_spacje(str.c_str());
			wek.push_back(atof(liczba.c_str()));
			break;
		}
	}
	return wek;
}

/*!
 * \brief Metoda wyszukuje i usuwa spacje w podanym stringu.
 *
 */
  string simplex::usun_spacje(string str)
  {
	int pos;
	string spacja = " ";
	while((pos = str.find(spacja)) != string::npos)
	{
		str = str.erase(pos, 1);
	}
	return str;
  }

