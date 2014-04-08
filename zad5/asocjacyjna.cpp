#include "asocjacyjna.h"
#include <iostream>

using namespace std;

template <class K, class V>
aiter<K,V> ATablica<K,V>::begin() {
  aiter<K,V> it; 
  it=glowa;
  return it;  
} 

template <class K, class V>
aiter<K,V> ATablica<K,V>::end() {
  aiter<K,V> it; 
  it=NULL;
  return it;
}

template <class K, class V>
bool ATablica<K,V>::czypusta() {
  if (i_elem ==0) 
    return true;
  else
    return false;
};

template <class K, class V>
int ATablica<K,V>::zliczelementy() {
  return i_elem;
}

template <class K, class V>
void ATablica<K,V>::dodaj(K key, V value) {
  ael<K,V>* wk;
  ael<K,V>* wk2;
  wk=glowa;
  while (wk!=NULL) {
    if (wk->klucz == key) {
      wk->wartosc=value;
      return;
    }
  wk2=wk;
  wk=wk->nxt;  
  }
  ael<K,V>* tmp= new ael<K,V>(key,value);
  wk2->nxt = tmp;
  if(i_elem++) {
  }
  else {
    glowa=tmp;
  }
}

template <class K, class V>
void ATablica<K,V>::usun(K key) {
  ael<K,V>* wk;
  ael<K,V>* wk2;
  wk=glowa;
  while (wk!=NULL) {
    if (wk->klucz == key) {
      wk2->nxt=wk->nxt;
      delete wk;
      i_elem--;
      return;      
    }
    wk2=wk;
    wk=wk->nxt;
  }
}

template <class K, class V>
V ATablica<K,V>::pobierz(K key) {
  ael<K,V>* wk;
  wk=glowa;
  while (wk!=NULL) {
    if (wk->klucz == key) {
      return wk->wartosc;
    }
  wk=wk->nxt;
  }
}

template <class K, class V>
V ATablica<K,V>::operator[] (K key) {
  ael<K,V>* wk;
  wk=glowa;
  while (wk!=NULL) {
    if (wk->klucz == key) {
      return wk->wartosc;
    }
  wk=wk->nxt;
  }  
}
