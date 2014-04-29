#ifndef POMIARY_HH
#define POMIARY_HH

#include "pomiary.hh"
#include "sortowania.hh"
#include "stos.hh"
#include "main.hh"
/*!
\brief Definicja klasy pomiary.
*/
template <class T>
/*!
\brief  Prototyp funkcji wczytujacej 
*/
int wczytaj(tab<T>& Tab, string NazwaPliku);

template <class T>
/*!
\brief  Prototyp funkcji wyswietlajacej
*/
void wyswietl(tab<T> Tab);

template <class T>
/*!
\brief Prototyp funkcji mnozacej 
*/
void pomnoz(tab<T>& Tab);

timespec diff(timespec start, timespec end);
/*!
\brief  Prototyp funkcji mierzacej czas 
*/
void pomiar();

#endif
