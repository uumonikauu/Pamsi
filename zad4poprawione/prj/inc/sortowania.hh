#ifndef SORTOWANIA_HH
#define SORTOWANIA_HH

#include "pomiary.hh"
#include "sortowania.hh"
#include "stos.hh"
#include "main.hh"
/*!
\brief Definicje klasy sortowania.
*/
template <class Typ>
/*!
\brief Prototyp funkcji sortowania merge 
*/
void merge_sort(Typ *wsk, int size);

template <class Typ>
/*!
\brief Prototyp funkcji sortowania merge 
*/
void merge_sort(el<Typ> *wsk, int size);

template <class Typ>
/*!
\brief Prototyp funkcji sortowania szybkiego 
*/
void qsort(Typ *wsk, int size);

template <class Typ>
/*!
\brief Prototyp funkcji sortowania szybkiego 
*/
void qsort(el<Typ> *wsk, int size);

#endif
