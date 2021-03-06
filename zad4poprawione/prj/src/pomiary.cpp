#include "pomiary.hh"
#include "sortowania.hh"
#include "stos.hh"
#include "stos.cpp"
#include "sortowania.cpp"

/*!
\brief Definicja funkcji metody klasy Pomiar. 
*/
template <class T>
/*!
\brief Definicja funkcji wczytującej tablicę. 
*/
int wczytaj(tab<T>& Tab, string NazwaPliku) {
/*!
\brief Zmienna x. 
*/
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


template <class T>
/*!
\brief Definicja funkcji wyświetlającej tablicę.
*/
void wyswietl(tab<T> Tab) {
	for(int i = 0; i < Tab.wymiar(); i++ ) 
        cout << Tab[ i ] << endl;   
}

template <class T>
/*!

\brief Definicja funkcji mnożącej tablicę przez 2.
*/
void pomnoz(tab<T>& Tab) {
	for(unsigned long long int i = 0; i < Tab.wymiar(); i++ ) 
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
void pomiar() {
struct timespec time1, time2;
//tab<int> S; //wybieramy jaki typ danych odkomentowywujac
//lista<int> S; 
//StosT<int> S;
//StosL<int> S;
kolejka<int> S;
/*!

\brief Pomocnicza zmienna tmp.
*/
int tmp;



for (unsigned long long int i=0;i<1000;i++) {
  tmp =( rand() % 1000 ) + 1;
  //S.dodaj(tmp); //pobieramy dane z klawiatury: dla tablicy - dodaj, dla listy - dodaj_tyl, dla stosów i kolejki - push
  //S.dodaj_tyl(tmp);
  S.push(tmp);
}
cout << endl;

//merge_sort(&S[0],S.wymiar()); //wywolywanie sortowania przez scalanie lub szybkiego: dla tablicy (&S[0],S.wymiar() dla reszty (S.pocz(),S.size())
//merge_sort(S.pocz(),S.size());
//qsort(&S[0],S.wymiar());
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1); // start zegar
qsort(S.pocz(),S.size());
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2); // zatrzymanie zegara

cout << ((double)diff(time1, time2).tv_nsec)/1000000000 << "s" << endl;

/*for (int i=0;i<10;i++) { //wyrzucanie danych posortowanych na ekran: dla tablicy S[i} dla listy S.zobacz_przod() dla stosow i kolejki S.pop()
  cout << S[i] << " ";
}*/

/*for (int i=0;i<10;i++) {
  cout << S.zobacz_przod() << " ";
  S.usun_przod();
}*/

for (unsigned long long int i=0;i<1000;i++) {
  cout << S.pop() << " ";
}

  cout << endl;  
}
