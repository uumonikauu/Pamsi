/*! \file tablica.h
\brief Jest to plik, który zawiera definicje klasy tablica */
#ifndef TABLICA_H
#define TABLICA_H

/*!
\brief Definicja klasy przechowującej tablice
*/

class tab {
  int wym;
  int* T;
public:
/*!
\brief Definicja klasy przechowującej tablice
*/
  int wymiar() {return wym;};
/*!
\brief Definicja klasy przechowującej tablice
*/
  tab(int wymiar=0);
/*!
\brief Definicja klasy przechowującej tablice
*/
  void zamien(int i, int j);
/*!
\brief Definicja klasy przechowującej tablice
*/
  void odwroc();
/*!
\brief Definicja klasy przechowującej tablice
*/
  void dodaj(int e);
/*!
\brief Definicja klasy przechowującej tablice
*/
  tab dodaj(tab B);
/*!
\brief Definicja klasy przechowującej tablice
*/
  tab operator= (tab B);
/*!
\brief Definicja klasy przechowującej tablice
*/
  bool operator== (tab B);
/*!
\brief Definicja klasy przechowującej tablice
*/
  int & operator[](int ind) {return T[ind];}
/*!
\brief Definicja klasy przechowującej tablice
*/
  const int & operator[](int ind) const {return T[ind];}
};

tab::tab(int w) {
  wym=w;
  T = new int [wym];
}

void tab::zamien(int i, int j) {
  int tmp;
  tmp = T[i];
  T[i] = T[j];
  T[j] = tmp;
}

void tab::odwroc() {
  for (int i=0;i<(wym/2);i++) {
    zamien(i,wym-i-1);
  }
}

void tab::dodaj(int e) {
  wym++;
  int* tmp;
  tmp=T;
  T = new int [wym];
  for (int i=0;i<wym-1;i++) {
    T[i]=tmp[i];
  }
  T[wym-1]=e;
  delete [] tmp;
}

tab tab::dodaj(tab B) {
  int w;
  w=wym+B.wymiar();
  tab Tab(w);
  for (int i=0;i<wym;i++) {
    Tab[i]=T[i];
  }
  for (int i=0;i<B.wym;i++) {
    Tab[wym+i]=B[i];
  }
  return Tab;
}

tab tab::operator= (tab B) {
  wym=B.wymiar();
  int* tmp;
  tmp=T;
  delete [] tmp;
  T = new int [wym];
  for (int i=0;i<wym;i++) {
    T[i]=B[i];
  }
  return *this;  
}

bool tab::operator== (tab B) {
  if (wym != B.wymiar()) {
    return false;
  }
  for (int i=0;i<wym;i++) {
    if (T[i] != B[i]) {
      return false;
    }
  }
  return true;
}

#endif
