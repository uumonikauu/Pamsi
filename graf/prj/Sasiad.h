#ifndef SASIAD_H
#define SASIAD_H

template <class T>
/*!
\brief Definicja klasy reprezentującej wierzcholki (sasiadow).
*/
class Sasiad {
public:
/*!
\brief numer wierzcholka (sasiada). 
*/
  int V;
/*!
\brief odleglosci miedzy wierzcholkami (sasiadami)
*/
  T odleglosc;
  Sasiad(int v, T C);
};

#endif
