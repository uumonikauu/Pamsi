/**
*\file
*\brief Szukajki 
* Zawiera najważniejsze fukcje programu.
* Trzy przeszukiwania grafu - depth first, breadth first, A* 
*/


#include  "graf.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <limits>
#include <set>

#define WALLY 15


std::list<int> breadth_first(Graf& cos, const int rozpoczecie, const int zakonczenie) {
	int* kolor = new int [cos.rozmiar()]();
	int* rodzic = new int [cos.rozmiar()]();

	kolor[rozpoczecie] = 1;
	rodzic[rozpoczecie] = -1;

	std::list<int> wiersz = { rozpoczecie };

	while(!wiersz.empty() ) {
		auto w = wiersz.back();
		if(w == zakonczenie) break;
		wiersz.pop_back();
		for(auto ws : cos.sasiedztwo(w) ) {
			if(kolor[ws] == 0) {
				kolor[ws] = 1;
				rodzic[ws] = w;
				wiersz.push_back(ws);
			}
		}
		kolor[w] = 2;
	}

	std::list<int> ret;
	for(int i = zakonczenie; i != -1; i = rodzic[i]) ret.push_front(i);
	delete[] kolor;
	delete[] rodzic;
	return ret;

}

double liczKoszt(Graf& cos, std::list<int> droga) {
	double koszt = 0;
	auto it = droga.begin();
	for(int i = 0; i < droga.size()-1; i++)
		koszt += cos.czy_sasiad( *it, *++it ); 
	return koszt;
 }

 std::list<int> depth_first(Graf& cos, int rozpoczecie, int zakonczenie, std::list<int> historia) {
	historia.push_back(rozpoczecie);
	 for( auto t : cos.sasiedztwo(rozpoczecie) )
		  if(std::find(historia.begin(), historia.end(), t) == historia.end() ) {
			auto copy = depth_first(cos, t, zakonczenie, historia);
			if(copy.back() == zakonczenie) return copy;
		}
	 return historia;
 }

 std::list<int> depth_first(Graf& cos, int rozpoczecie, int zakonczenie) {
	return depth_first(cos, rozpoczecie, zakonczenie, std::list<int>() );
}


    std::list<int> a_star(Graf& cos, int rozpoczecie, int zakonczenie) {
	int* odleglosc = new int[cos.rozmiar()]; 
		std::fill(odleglosc, odleglosc+cos.rozmiar(), std::numeric_limits<int>::max() );
	int* f = new int[cos.rozmiar()];
		std::fill(f, f+cos.rozmiar(), std::numeric_limits<int>::max() );
	int* kolor = new int[cos.rozmiar()]();
	int* rodzic = new int[cos.rozmiar()]; for(int i = 0; i < cos.rozmiar(); ++i) rodzic[i] = i;
	class heurestic {
		public:
	int operator()(int n) { return 0; }
	} h;

  kolor[rozpoczecie] = 1;
	rodzic[rozpoczecie] = -1;
	odleglosc[rozpoczecie] = 0;

	f[rozpoczecie] = h(rozpoczecie);
	
	 std::set<int> Q;
	 Q.insert(rozpoczecie);
	 while(!Q.empty() ) {
		  for( auto it = Q.begin(); it != Q.end(); ++it )
		std::cerr << *it << ", "; std::cerr << "\n";
		auto u = *Q.begin();
		Q.erase(Q.begin());
		  for(auto v : cos.sasiedztwo(u) ) {
			   if(cos.czy_sasiad(u,v) + odleglosc[u] < odleglosc[v]) {
				 odleglosc[v] = cos.czy_sasiad(u,v) + odleglosc[u];
				 f[v] = odleglosc[v] + h(v);
				 rodzic[v] = u;
				 if(kolor[v] == 0) {
					kolor[v] = 1;
					Q.insert(v);
				}
				 else if( kolor[v] == 2 ) {
					kolor[v] = 1;
					Q.insert(v);
				}
			} else {

			}
		}
		kolor[u] = 2;
	}
	  std::list<int> ret;
	  for(int i = zakonczenie; i != -1; i = rodzic[i]) ret.push_front(i);
	  return ret;
}
