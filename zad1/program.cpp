#include <iostream>
#include <ctime> 
#include <fstream>
#include "tablica.h"
#include <limits>
#include <string>
using namespace std;  
/*!
\brief wczytuje tablicę 
*/
int wczytaj(tab& Tab, string NazwaPliku) {
  int x;
  ifstream StrmWe;
  StrmWe.open(NazwaPliku.c_str());

  if(!StrmWe.is_open()) {
    cerr << " Plik nie zostal otwarty" << endl; 
    return 1;
  }
  StrmWe>>x;
while(!StrmWe.eof()) {
  StrmWe>>x;

  if (StrmWe.fail()) {
      StrmWe.clear();
      StrmWe.ignore(numeric_limits<int>::max( ),'\n');
    } 
    else { 
      Tab.dodaj( x );
    }
  }
  StrmWe.close(); 
}

/*!
\brief Wyświetla tablicę
*/
void wyswietl(tab Tab) {
	for(int i = 0; i < Tab.wymiar(); i++ ) 
        cout << Tab[ i ] << endl;   
}
/*!
\brief Mnoży przez 2 tablicę
*/
void pomnoz(tab& Tab) {
	for(int i = 0; i < Tab.wymiar(); i++ ) 
	Tab[i]=Tab[i]*2;  
}



timespec diff(timespec start, timespec end) {
    timespec temp;
    if((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;    
    }   
    return temp;
}  
/*!
\brief Wczytuje liczby z pliku i porównuje sprawdzajac z zegarem 
*/
int main() {
struct timespec time1, time2;
tab Tab1, Tab2;

wczytaj(Tab1, "1.txt");
wczytaj(Tab2, "2.txt");

clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1); // start zegar

pomnoz(Tab1);

clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2); // zatrzymanie zegara

if (Tab1==Tab2) {
cout << Tab1.wymiar() << ",1," << ((double)diff(time1, time2).tv_nsec)/1000000000 << "s" << endl;
}
else cout << "Tablice sa rozne" << endl;  
return 0;
}
