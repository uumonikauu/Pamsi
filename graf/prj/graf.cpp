#include "graf.h"

template <class T>
/*!
\brief Definicja funkcji dodającej wierzchołek
*/
void Graf<T>::dodaj_wierzcholek() {
  std::vector<Sasiad<T> > L1;
  L.push_back(L1);
  return;
}
/*!
\brief Sprawdzamy po liscie sasiadow pierwszego wierzcholka czy ktorys z siasiadow nie jest drugim wierzcholkiem.
*/
template <class T>

/*!
\brief Definicja funkcji sprawdzajacej czy sa sasiadami.
*/
bool Graf<T>::CzySasiad(int V1, int V2) {
/*!
\brief sprawdzamy dlugosc listy.
*/
  int w=L.size();
  if (V1>=w && V2>=w) {
    std::cerr << "Błąd: proba sprawdzenia krawedzi między nieistniejącymi wierzcholkami" <<  std::endl;
  return 0;
  }
  for (int i=0;i<L[V1].size();i++) {
    if (L[V1][i].V == V2) {
      return 1;
    }
  }
  return 0;
}

template <class T>
/*!
\brief Definicja funkcji dodajacej krawedz
*/
void Graf<T>::dodaj_krawedz(int V1, int V2, T C) {
/*!
\brief sprawdzamy dlugosc listy.
*/
  int w=L.size();
  if (V1>=w && V2>=w) {
    std::cerr << "Błąd: proba utworzenia krawedzi między nieistniejącymi wierzcholkami" <<  std::endl;
  return;
  }
  if (!CzySasiad(V1,V2)) {
    L[V1].push_back(Sasiad<T>(V2,C));
    L[V2].push_back(Sasiad<T>(V1,C));
  }
}
/*!
\brief sprawdzamy po liscie sasiadow pierwszego wierzcholka czy ktorys z siasiadow nie jest drugim wierzcholkiem. Jesli tak usuwamy go.
*/
template <class T>

/*!
\brief Definicja funkcji usuwajacej krawedz
*/
void Graf<T>::usun_krawedz(int V1, int V2) {
/*!
\brief sprawdzamy dlugosc listy.
*/
  int w=L.size();
  if (V1>=w && V2>=w) {
    std::cerr << "Błąd: proba usuniecia krawedzi między nieistniejącymi wierzcholkami" <<  std::endl;
  return;  
  }
  for (int i=0;i<L[V1].size();i++) {
    if (L[V1][i].V == V2) {
      L[V1].erase(L[V1].begin()+i);
      break;
    }
  }
/*!
\brief sprawdzamy po liscie sasiadow drugiego wierzcholka czy ktorys z siasiadow nie jest pierwszym wierzcholkiem. Jesli tak usuwamy go.
*/
  for (int i=0;i<L[V2].size();i++) {
    if (L[V2][i].V == V1) {
      L[V2].erase(L[V2].begin()+i);
      return;
    }
  }
  std::cerr << "Błąd: próba usuniecia nieistniejacej krawedzi." << std::endl;  
}

template <class T>
std::vector<Sasiad<T> > Graf<T>::Sasiedztwo(int V) {
/*!
\brief sprawdzamy dlugosc listy.
*/
  int w=L.size();
  if (V>=w) {
    std::cerr << "Błąd: proba pokazania sasiedztwa nieistniejacego wierzcholka" <<  std::endl;
  std::vector<Sasiad<T> > tmp;
  return tmp;
  }
  return L[V];
}
/*!
\brief zwraca liste wszystkich sasiadow usuwanego wierzcholka potem bazujac na tej liscie usuwa ten wierzcholek z listy sasiedztwa swoich sasiadow. 
*/
template <class T>
/*!
\brief Definicja funkcji usuwajacej wierzcholek 
*/
void Graf<T>::usun_wierzcholek(int V) {
/*!
\brief sprawdzamy dlugosc listy.
*/
  int w=L.size();
  if (V>=w) {
    std::cerr << "Błąd: proba usuniecia nieistniejacego wierzcholka" <<  std::endl;
  return;
  }
  std::vector<Sasiad<T> > tmp=Sasiedztwo(V);
  L[V].clear();  
  for (int i=0;i<tmp.size();i++) {
    for (int j=0;j<L[tmp[i].V].size();j++) {
      if(L[tmp[i].V][j].V == V) {
        L[tmp[i].V].erase(L[tmp[i].V].begin()+j);
      }
    }
  }   
}



