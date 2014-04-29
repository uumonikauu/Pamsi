#ifndef STOS_HH
#define STOS_HH

#include "main.hh"
/*!
\brief Definicja klasy tablica.
*/
template <class Typ>
class tab {
/*!
\brief Zmienna przechowujaca wymiar.
*/
  int wym;
  Typ* T;
public:
/*!
\brief Prototyp funkcji przedstawiajacej wymiar.
*/
  int wymiar() {return wym;};

  tab(int wymiar=0);
/*!
\brief Prototyp funkcji zamieniajacej miejscami i, j. 
*/
  void zamien(Typ i, Typ j);
/*!
\brief Prototyp funkcji odwracajacej tablicę.
*/
  void odwroc();
/*!
\brief Prototyp funkcji dodajacej elementy.
*/
  void dodaj(Typ e);

  tab dodaj(tab B);
/*!
\brief Prototyp funkcji usuwajacej elementy.
*/
  void usun(int ind);
/*!
\brief Operator przypisania
*/
  tab operator= (tab B);
/*!
\brief Operator porównania 
*/
  bool operator== (tab B);
/*!
\brief Operatory odwołania się do danego pola 
*/
  Typ & operator[](int ind) {return T[ind];}

  const Typ & operator[](int ind) const {return T[ind];}
  
};

/*!
\brief Definicja klasy stos na tablicy.
*/
template <class T>
class StosT {
private:
  tab<T> Tab;
public:
/*!
\brief Zmienna przechowujaca rozmiar.
*/
  int size();
/*!
\brief Sprawdza czy puste.
*/
  bool empty();
/*!
\brief dodaje element.
*/
  void push(T e);
  T pop();
  StosT() {};
  T* pocz() {return &Tab[0];}
};
/*!
\brief Definicja klasy elementu.
*/
template <class T>
class el {
public:
  T dana;
  el* prv;
  el* nxt;
  el(T d) {dana=d;prv=NULL;nxt=NULL;}
  bool operator<(el<T> B) {return (dana < B.dana);}
};
/*!
\brief Definicja klasy lista.
*/
template <class T>
class lista {
  el<T>* glowa;
  el<T>* ogon;
public:
  lista() {glowa=NULL;ogon=NULL;}
/*!
\brief Prototyp funkcji dodajacej na przod. 
*/
  void dodaj_przod(T dana);
/*!
\brief Prototyp funkcji usuwajacej element z przodu. 
*/
  void usun_przod();
/*!
\brief Prototyp funkcji dodajacej element na tyle. 
*/
  void dodaj_tyl(T dana);
/*!
\brief Prototyp funkcji usuwajacej element z tylu. 
*/
  void usun_tyl();
/*!
\brief Prototyp funkcji pokazujacej przod. 
*/
  T zobacz_przod();
/*!
\brief Prototyp funkcji pokazujacej tyl. 
*/
  T zobacz_tyl();
/*!
\brief Zmienna przechowujaca rozmiar.
*/
  int size();
/*!
\brief Sprawdza czy puste.
*/
  bool empty();
/*!
\brief ma za zadanie przypisywać jedna liste do drugiej (de facto tworzyć kopie).
*/
  void operator=(lista<T> L2); 
  el<T>* pocz() {return glowa;}
};

/*!
\brief Definicja klasy stos na liscie.
*/
template <class T>
class StosL {
private:
  lista<T> L;
public:
/*!
\brief Zmienna przechowujaca rozmiar.
*/
  int size();
/*!
\brief Sprawdza czy puste.
*/
  bool empty();
/*!
\brief Dodaje element.
*/
  void push(T e);
  T pop();
  StosL() {};
  el<T>* pocz() {return L.pocz();}
};

/*!
\brief Definicja klasy kolejka.
*/
template <class T>
class kolejka {
  lista<T> L;
public:
/*!
\brief Zmienna przechowujaca rozmiar.
*/
  int size();
/*!
\brief Sprawdza czy puste..
*/
  bool empty();
/*!
\brief Dodaje element.
*/
  void push(T e);
  T pop();
  kolejka() {};
/*!
\brief Dodaje do kolejki.
*/
  void queue(lista<T> L2);
  lista<T> dequeue();
  el<T>* pocz() {return L.pocz();}
};

#endif


