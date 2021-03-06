#include <queue>
#include <iostream>
#include "Stos.h"

using namespace std;

template <class Typ>
/*!
\brief sortowanie merge
*/
void merge_sort(Typ *wsk, int size) {
	
	int size1=size/2;
	int size2=(size/2)+(size%2); //dzieli tablice
	if (size>1) {
		merge_sort(wsk,size1); //rekurencja dla n/2
		merge_sort(&wsk[size1],size2);
	}
	int i=0,j=0;
	queue <Typ> tmp;
	while (i<size1 && j<size2) { //laczy tablice
		if (wsk[i] < wsk[size1+j]) {
			tmp.push(wsk[i]);
			i++;
		}
		else {
			tmp.push(wsk[size1+j]);
			j++;
		}
	}
	if (i>=size1) { //gdy jedna sie skonczy
		while(j<size2) {
			tmp.push(wsk[size1+j]);
			j++;
		}
	}
	else {
		while(i<size1) {
			tmp.push(wsk[i]);
			i++;
		}
	}
	for (int k=0;k<size;k++) {
		wsk[k]=tmp.front();
		tmp.pop();
	}
}
//dla nietablicowych - różni się tylko tym, że zamiast stosować wyrażenie wsk[i] stosuje sie inkrementowanie wskaźników wsk=wsk->nxt;
template <class Typ>
void merge_sort(el<Typ> *wsk, int size) {
	
	int size1=size/2;
	int size2=(size/2)+(size%2); //dzieli tablice
	el<Typ>* wsk2=wsk;
	el<Typ>* owsk=wsk;
	for (int i=0;i<size1;i++) {
	  wsk2=wsk2->nxt;
	}
	if (size>1) {
		merge_sort(wsk,size1); //rekurencja dla n/2
		merge_sort(wsk2,size2);
	}
	int i=0,j=0;
	queue <Typ> tmp;
	while (i<size1 && j<size2) { //laczy tablice
		if (wsk->dana < wsk2->dana) {
			tmp.push(wsk->dana);
			i++;
			wsk=wsk->nxt;
		}
		else {
			tmp.push(wsk2->dana);
			j++;
			wsk2=wsk2->nxt;
		}
	}
	if (i>=size1) { //gdy jedna sie skonczy
		while(j<size2) {
			tmp.push(wsk2->dana);
			j++;
			wsk2=wsk2->nxt;
		}
	}
	else {
		while(i<size1) {
			tmp.push(wsk->dana);
			i++;
			wsk=wsk->nxt;
		}
	}
	for (int k=0;k<size;k++) {
		owsk->dana=tmp.front();
		tmp.pop();
		owsk=owsk->nxt;
	}
}


template <class Typ>
/*!
\brief sortowanie szybkie 
*/
void qsort(Typ *wsk, int size) { 

  queue <Typ> l1;
  queue <Typ> l2;
  Typ osiowy;
  osiowy=wsk[size/2]; //wybor osiowego
  int sl1=0;
  int sl2=0;
  for (int i=0;i<size;i++) { //podzial na podtablice
    if (i == size/2) {
      i++;
    }
    if (wsk[i] < osiowy) {
      l1.push(wsk[i]);
      sl1++;
    }
    else {
      l2.push(wsk[i]);
      sl2++;
    }
  }
  for (int i=0;i<sl1;i++) { //powrot do tablicy macierzystej
    wsk[i] = l1.front();
    l1.pop();
  }
  wsk[sl1] = osiowy;
  for (int i=0;i<sl2;i++) {
    wsk[sl1+1+i] =l2.front();
    l2.pop();
  }
  if (sl1>1) //jesli jest tylko jeden element to go nie sortuje
  qsort(wsk,sl1);
  if (sl2>1)
  qsort(&wsk[sl1+1],sl2);
}
//dla nietablicowych - różni się tylko tym, że zamiast stosować wyrażenie wsk[i] stosuje sie inkrementowanie wskaźników wsk=wsk->nxt;
template <class Typ>
void qsort(el<Typ> *wsk, int size) { //sortowanie szybkie

  queue <Typ> l1;
  queue <Typ> l2;
  Typ osiowy;
  el<Typ>* tmp;
  tmp=wsk;
  for (int i=0;i<size/2;i++) {
    wsk=wsk->nxt;
  }
  osiowy=wsk->dana; //wybor osiowego
  wsk=tmp;
  int sl1=0;
  int sl2=0;
  for (int i=0;i<size;i++) { //podzial na podtablice
    if (i == size/2) {
      i++;
      wsk=wsk->nxt;
    }
    if (wsk->dana < osiowy) {
      l1.push(wsk->dana);
      sl1++;
    }
    else {
      l2.push(wsk->dana);
      sl2++;
    }
    wsk=wsk->nxt;
  }
  wsk=tmp;
  for (int i=0;i<sl1;i++) { //powrot do tablicy macierzystej
    wsk->dana = l1.front();
    l1.pop();
    wsk=wsk->nxt;
  }
  wsk->dana = osiowy;
  wsk=wsk->nxt;
  for (int i=0;i<sl2;i++) {
    wsk->dana =l2.front();
    l2.pop();
    wsk=wsk->nxt;
  }
  if (sl1>1)
  qsort(tmp,sl1);
  for (int i=0;i<=sl1;i++) {
    tmp=tmp->nxt;
  }
  if (sl2>1)
  qsort(tmp,sl2);
}
