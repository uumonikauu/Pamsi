#ifndef ASOCJACYJNA_H
#define ASOCJACYJNA_H
#include <iostream>

using namespace std;

template <class K, class V>
class ael {
public:
  K klucz;
  V wartosc;
  ael<K,V>* nxt;
  ael(K key, V value) {klucz=key;wartosc=value;}
};

template <class K, class V>
class aiter {
  ael<K,V>* wsk;
public:
  aiter() {wsk=NULL;}
  void operator= (ael<K,V>* el) {wsk = el;}
  void operator= (aiter<K,V> it) {wsk = it.wsk;}
  bool operator== (ael<K,V>* el) {return (wsk==el);}
  bool operator== (aiter<K,V> it) {return (wsk==it.wsk);}
  bool operator!= (ael<K,V>* el) {return (wsk!=el);}
  bool operator!= (aiter<K,V> it) {return (wsk!=it.wsk);}
  aiter<K,V> operator++(int) {
  aiter<K,V> tmp;
  tmp=(*this);
  wsk=wsk->nxt;
  return tmp;  
  }
  V operator*() {return wsk->wartosc;}
};

template <class K, class V>
class ATablica {
  ael<K,V>* glowa;
  int i_elem;
public:
  aiter<K,V> begin();
  aiter<K,V> end();
  ATablica() {glowa=NULL; i_elem=0;}
  void dodaj(K key,V value);
  void usun(K key);
  V pobierz(K key);
  bool czypusta();
  int zliczelementy();
  V operator[] (K key);
};

#endif
