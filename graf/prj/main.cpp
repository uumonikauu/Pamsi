#include "graf.h"
#include "graf.cpp"
#include "Sasiad.h"
#include "Sasiad.cpp"

using namespace std;

int main() {
  Graf<int> G;
  G.dodaj_wierzcholek();
  G.dodaj_wierzcholek();
  G.dodaj_wierzcholek();
  G.dodaj_krawedz(1,2,5);
  G.dodaj_krawedz(0,1,10);
  cout << G.CzySasiad(0,1) << endl;
  cout << G.CzySasiad(0,2) << endl;
  vector<Sasiad <int> > S=G.Sasiedztwo(1);
  for (int i=0;i<S.size();i++) {
    cout << S[i].V << " " << S[i].odleglosc << endl;
  }
  G.usun_krawedz(0,1);
  S=G.Sasiedztwo(1);
  for (int i=0;i<S.size();i++) {
    cout << S[i].V << " " << S[i].odleglosc << endl;
  }
  G.usun_wierzcholek(2);
  S=G.Sasiedztwo(1);
  for (int i=0;i<S.size();i++) {
    cout << S[i].V << " " << S[i].odleglosc << endl;
  }  
}
