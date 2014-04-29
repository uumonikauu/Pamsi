#include "stos.hh"
/*!
\brief Definicja metod klasy stos.
*/
template <class Typ>
/*!
\brief Definicja funkcji wyswietlajacej tablice.
*/
tab<Typ>::tab(int w) {
  wym=w;
  T = new int [wym];
}

template <class Typ>
/*!
\brief Definicja funkcji zamieniajacej i, j. 
*/
void tab<Typ>::zamien(Typ i, Typ j) {
  Typ tmp;
  tmp = T[i];
  T[i] = T[j];
  T[j] = tmp;
}

template <class Typ>
/*!
\brief Definicja funkcji odwracajacej tablice
*/
void tab<Typ>::odwroc() {
  for (int i=0;i<(wym/2);i++) {
    zamien(i,wym-i-1);
  }
}

template <class Typ>
/*!
\brief Definicja funkcji dodajacej elementy.
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
/*!
\brief Definicja funkcji dodajacej elementy.
*/
tab<Typ> tab<Typ>::dodaj(tab B) {
/*!
\brief Zmienna w.
*/
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
/*!
\brief Definicja funkcji usuwajacej. 
*/
void tab<Typ>::usun(int ind) {
  for (int i=ind;i<wym-1;i++) {
    T[i]=T[i+1];
  }
  wym--;
}

template <class Typ>
/*!
\brief Definicja funkcji porownania.
*/
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
\brief Definicja funkcji przypisania.
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


/********************************************************/


template <class T>
/*!
\brief Definicja funkcji sprawdzajacej rozmiar stosu.
*/
int StosT<T>::size() {
  return Tab.wymiar();
}

template <class T>
/*!
\brief Definicja funkcji sprawdzajacej czy stos pusty.
*/
bool StosT<T>::empty() {
  if (Tab.wymiar() == 0)
    return true;
  else
    return false;
}

template <class T>
/*!
\brief Definicja funkcji dodajacej na stos.
*/
void StosT<T>::push(T e) {
  Tab.dodaj(e);
}

template <class T>
/*!
\brief Definicja funkcji sciagajacej ze stosu.
*/
T StosT<T>::pop() {
  T tmp;
  tmp=Tab[Tab.wymiar()-1];
  Tab.usun(Tab.wymiar()-1);
  return tmp;
}
/*************************************/


template <class T>
/*!
\brief Definicja funkcji sprawdzajacej czy lista jest pusta.
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
/*!
\brief Definicja funkcji sprawdzajacej rozmiar listy.
*/
int lista<T>::size() {
  if (empty())
    return 0;
  el<T>* wsk=glowa;
/*!
\brief zmienna wielkosci.
*/
  int wielkosc=0;
  while (wsk!=NULL) {
    wielkosc++;
    wsk=wsk->nxt;
  }
  return wielkosc;
}

template <class T>
/*!
\brief Definicja funkcji dodajacej na przod listy.
*/
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
/*!
\brief Definicja funkcji dodajacej na tyl listy.
*/
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
/*!
\brief Definicja funkcji usuwajacej element z przodu listy.
*/
void lista<T>::usun_przod() {
  el<T>* tmp;
  if (glowa==NULL) {
    return;
  } else {
    tmp=glowa;
    glowa=tmp->nxt;
    if (glowa != NULL) { 
      tmp->nxt->prv=NULL;
    }
    delete tmp;
  }  
}

template <class T>
/*!
\brief Definicja funkcji usuwajacej element z tylu listy.
*/
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
/*!
\brief Definicja funkcji pokazujacej przod listy.
*/
T lista<T>::zobacz_przod() {
  return glowa->dana; 
}

template <class T>
/*!
\brief Definicja funkcji pokazujacej tyl listy.
*/
T lista<T>::zobacz_tyl() {
  return ogon->dana; 
}

template <class T>
/*!
\brief usuwa 'stara' listę L
*/
void lista<T>::operator=(lista<T> L2) {
  el<T>* E1,E2,E3;
  E1=glowa;
  for (int i=0;i<size();i++) { 
    E2=E1;
    E1=E1->nxt;
    delete E2;
  }
  this.glowa=NULL;
  this.ogon=NULL;
  E1=L2.glowa;
/*!
\brief kopiuje 'nowa' liste L2 na L
*/
  for (int i=0;i<L2.size();i++) { 
    this.dodaj_tyl(E1->dana);
    E1=E1->nxt;
  }
}

/************************************************************/


template <class T>
/*!
\brief Definicja funkcji sprawdzajacej rozmiar Stosu.
*/
int StosL<T>::size() {
  return L.size();
}

template <class T>
/*!
\brief Definicja funkcji sprawdzajacej czy stos pusty.
*/
bool StosL<T>::empty() {
  if (L.size() == 0)
    return true;
  else
    return false;
}

template <class T>
/*!
\brief Definicja funkcji dodajacej element.
*/
void StosL<T>::push(T e) {
  L.dodaj_tyl(e);
}

template <class T>
/*!
\brief Definicja funkcji usuwajacej element.
*/
T StosL<T>::pop() {
  T tmp;
  tmp=L.zobacz_tyl();
  L.usun_tyl();
  return tmp;
}


/****************************************************/


template <class T>
/*!
\brief Definicja funkcji sprawdzajacej rozmiar kolejki.
*/
int kolejka<T>::size() {
  return L.size();
}

template <class T>
/*!
\brief Definicja funkcji sprawdzającej czy kolejka jest "pusta". 
*/
bool kolejka<T>::empty() {
  if (L.size() == 0)
    return true;
  else
    return false;
}

template <class T>
/*!
\brief Definicja funkcji wrzucająca elemnty na kolejke. 
*/
void kolejka<T>::push(T e) {
  L.dodaj_tyl(e);
}

template <class T>
/*!
\brief Definicja funkcji zdejmująca elementy z kolejki. 
*/
T kolejka<T>::pop() {
  T tmp;
  tmp=L.zobacz_przod();
  L.usun_przod();
  return tmp;
}


template <class T>
/*!
\brief Definicja funkcji ustawiającej elemty w kolejce. 
*/
void kolejka<T>::queue(lista<T> L2) {
  L=L2;
}

template <class T>
/*!
\brief Definicja funkcji usuwajacej element z kolejki. 
*/
lista<T> kolejka<T>::dequeue() {
  return L;
}
