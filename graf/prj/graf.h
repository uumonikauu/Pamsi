#ifndef GRAF_H
#define GRAF_H
#include <vector>
#include <iostream>
#include "Sasiad.h"

template <class T>
/*!
\brief Definicja klasy reprezentującej Graf
*/
class Graf {
  std::vector<std::vector <Sasiad <T> > > L;
public:
  //Graf();
/*!
\brief Prototyp funkcji sprawdzajacej czy sa sasiadami
*/
  bool CzySasiad(int V1, int V2);
  std::vector<Sasiad<T> > Sasiedztwo(int V);
/*!
\brief Prototyp funkcji dodającej wierzchołek
*/
  void dodaj_wierzcholek();
/*!
\brief Prototyp funkcji dodającej krawedz
*/
  void dodaj_krawedz(int V1, int V2, T C);
/*!
\brief Prototyp funkcji dousuwającej krawedz
*/
  void usun_krawedz(int V1, int V2);
/*!
\brief Prototyp funkcji usuwajacej wierzchołek
*/
  void usun_wierzcholek(int V);
  //~Graf();
};

#endif
