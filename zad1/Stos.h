/*! \file Stos.h
\brief Jest to plik, który zawiera definicje klasy stos */
#include <iostream>

using namespace std;
/*!
\brief Definicja klasy przechowującej tablice
*/
template <class Typ>
class tab {
  int wym;
  Typ* T;
public:
/*!
\brief Definicja wymiaru
*/
  int wymiar() {return wym;};

  tab(int wymiar=0);
/*!
\brief Zamienia miejscami i, j 
*/
  void zamien(Typ i, Typ j);
/*!
\brief Odwraca tablicę
*/
  void odwroc();
/*!
\brief Dodaje element
*/
  void dodaj(Typ e);

  tab dodaj(tab B);

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
\brief wymiar tablicy
*/
template <class Typ>
tab<Typ>::tab(int w) {
  wym=w;
  T = new int [wym];
}

template <class Typ>
/*!
\brief zamienia elementy
*/
void tab<Typ>::zamien(Typ i, Typ j) {
  Typ tmp;
  tmp = T[i];
  T[i] = T[j];
  T[j] = tmp;
}

template <class Typ>
void tab<Typ>::odwroc() {
  for (int i=0;i<(wym/2);i++) {
    zamien(i,wym-i-1);
  }
}

template <class Typ>
/*!
\brief dodaje elementy 
*/
void tab<Typ>::dodaj(Typ e) {
  wym++;
  Typ* tmp;
  tmp=T;
  T = new Typ [wym];
  for (int i=0;i<wym-1;i++) {
    T[i]=tmp[i];
  }
  T[wym-1]=e;
  delete [] tmp;
}
template <class Typ>
tab<Typ> tab<Typ>::dodaj(tab B) {
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

template <class Typ>
void tab<Typ>::usun(int ind) {
  for (int i=ind;i<wym-1;i++) {
    T[i]=T[i+1];
  }
  wym--;
}

template <class Typ>
tab<Typ> tab<Typ>::operator= (tab B) {
  wym=B.wymiar();
  Typ* tmp;
  tmp=T;
  delete [] tmp;
  T = new Typ [wym];
  for (int i=0;i<wym;i++) {
    T[i]=B[i];
  }
  return *this;  
}

template <class Typ>
/*!
\brief Operator porównania  
*/
bool tab<Typ>::operator== (tab B) {
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

/*!
\brief Definicja klasy przechowującej Stos
*/
template <class T>
class StosT {
private:
  tab<T> Tab;
public:
/*!
\brief Rozmiar Stosu
*/
  int size();
/*!
\brief Sprawdza czy stos jest pusty
*/
  bool empty();
/*!
\brief Dodaje elementy
*/
  void push(T e);
  T pop();
  StosT() {};
};

template <class T>
int StosT<T>::size() {
  return Tab.wymiar();
}
/*!
\brief Sprawdza czy stos jest pusty
*/
template <class T>
bool StosT<T>::empty() {
  if (Tab.wymiar() == 0)
    return true;
  else
    return false;
}
/*!
\brief Definicja klasy ściągającej element
*/
template <class T>
void StosT<T>::push(T e) {
  Tab.dodaj(e);
}
/*!
\brief Definicja klasy dodającej element
*/
template <class T>
T StosT<T>::pop() {
  T tmp;
  tmp=Tab[Tab.wymiar()-1];
  Tab.usun(Tab.wymiar()-1);
  return tmp;
}
/*!
\brief Definicja klasy przechowującej element
*/
template <class T>
class el {
public:
  T dana;
  el* prv;
  el* nxt;
  el(T d) {dana=d;prv=NULL;nxt=NULL;}
};
/*!
\brief Definicja klasy przechowującej liste
*/
template <class T>
class lista {
  el<T>* glowa;
  el<T>* ogon;
public:
  lista() {glowa=NULL;ogon=NULL;}
/*!
\brief dodaje element na przodzie tzn. głowie
*/
  void dodaj_przod(T dana);
/*!
\brief usuwa element z przodzie tzn. głowy
*/
  void usun_przod();
/*!
\brief dodaje element na tyle tzn. ogon
*/
  void dodaj_tyl(T dana);
/*!
\brief usuwa element z tyłu tzn. ogon
*/
  void usun_tyl();
  T zobacz_przod();
  T zobacz_tyl();
/*!
\brief Rozmiar Stosu
*/
  int size();
/*!
\brief Sprawdza czy Stos jest pusty
*/
  bool empty();
/*!
\brief operator ma za zadanie, przypisywać jedną listę do drugiej (de facto tworzyć kopie).
*/
  void operator=(lista<T> L2); 
};

template <class T>
/*!
\brief Sprawdza czy lista jest pusta 
*/
bool lista<T>::empty() {
  if (glowa==NULL) {
    return true;
  }
  else {
    return false;
  }
}

template <class T>
int lista<T>::size() {
  if (empty())
    return 0;
  el<T>* wsk=glowa;
  int wielkosc=0;
  while (wsk!=NULL) {
    wielkosc++;
    wsk=wsk->nxt;
  }
  return wielkosc;
}

template <class T>
void lista<T>::dodaj_przod(T dana) {
  el<T>* tmp= new el<T>(dana);
  if (glowa==NULL) {
    glowa=tmp;
    ogon=tmp;
  } else {
    tmp->nxt=glowa;
    glowa=tmp;
    tmp->nxt->prv=tmp;    
  }  
}

template <class T>
void lista<T>::dodaj_tyl(T dana) {
  el<T>* tmp= new el<T>(dana);
  if (glowa==NULL) {
    glowa=tmp;
    ogon=tmp;
  } else {
    tmp->prv=ogon;
    ogon=tmp;
    tmp->prv->nxt=tmp;    
  }  
}

template <class T>
void lista<T>::usun_przod() {
  el<T>* tmp;
  if (glowa==NULL) {
    return;
  } else {
    tmp=glowa;
    glowa=tmp->nxt;
    if (glowa != NULL) { 
      tmp->nxt->prv=NULL;//zmiana pop na prv
    }
    delete tmp;
  }  
}

template <class T>
void lista<T>::usun_tyl() {
  el<T>* tmp;
  if (glowa==NULL) {
    return;
  } else {
    tmp=ogon;

    ogon=tmp->prv;//zamiana pop na prv 
    if (ogon != NULL ) {//analogicznie do sytuacji przerobionej w funkcji wyżej.
      tmp->prv->nxt=NULL; //to co wyżej
    }
    delete tmp;
  }  
}

template <class T>
T lista<T>::zobacz_przod() {
  return glowa->dana; 
}

template <class T>
T lista<T>::zobacz_tyl() {
  return ogon->dana; 
}

template <class T>
void lista<T>::operator=(lista<T> L2) {
  el<T>* E1,E2,E3;
  E1=glowa;
/*!
\brief Usuwa "starą" listę L
*/
  for (int i=0;i<size();i++) { 
    E2=E1;
    E1=E1->nxt;
    delete E2;
  }
  this.glowa=NULL;
  this.ogon=NULL;
  E1=L2.glowa;
/*!
\brief Kopiuję "nową" listę L2 na L
*/
  for (int i=0;i<L2.size();i++) { 
    this.dodaj_tyl(E1->dana);
    E1=E1->nxt;
  }
}

//niżej skopiowane na zasadzie zamień StosT na StosL, tablica<T> Tab na lista<T> L i funkcji z Tab.funkcja() na odpowiadające jej L.funkcja()
/*!
\brief Definicja klasy przechowyjącej liste 
*/
template <class T>
class StosL {
private:
  lista<T> L;
public:
/*!
\brief Sprawdza rozmiar
*/
  int size();
/*!
\brief Sprawdza czy lista jest pusta 
*/
  bool empty();
/*!
\brief Dodaje element 
*/
  void push(T e);
  T pop();
  StosL() {};
};

template <class T>
int StosL<T>::size() {
  return L.size();
}

template <class T>
bool StosL<T>::empty() {
  if (L.size() == 0)
    return true;
  else
    return false;
}

template <class T>
void StosL<T>::push(T e) {
  L.dodaj_tyl(e);
}

template <class T>
T StosL<T>::pop() {
  T tmp;
  tmp=L.zobacz_tyl();
  L.usun_tyl();
  return tmp;
}

// pop zabiera i zwraca z początku a nie z końca jak w stosie
/*!
\brief Definicja klasy przechowującej kolejke
*/
template <class T>
class kolejka {
  lista<T> L;
public:
  int size();
  bool empty();
  void push(T e);
  T pop();
  kolejka() {};
  void queue(lista<T> L2);
  lista<T> dequeue();
};

template <class T>
int kolejka<T>::size() {
  return L.size();
}

template <class T>
bool kolejka<T>::empty() {
  if (L.size() == 0)
    return true;
  else
    return false;
}

template <class T>
void kolejka<T>::push(T e) {
  L.dodaj_tyl(e);
}

template <class T>
T kolejka<T>::pop() {
  T tmp;
  tmp=L.zobacz_przod();
  L.usun_przod();
  return tmp;
}


/*!
\brief funkcja tworząca listy kolejke i z kolejki listę.
*/

template <class T>
void kolejka<T>::queue(lista<T> L2) {
  L=L2;
}

template <class T>
lista<T> kolejka<T>::dequeue() {
  return L;
}
