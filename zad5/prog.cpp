#include "asocjacyjna.h"
#include "asocjacyjna.cpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
  ATablica<string,string> T;
  if (T.czypusta()) {
    cout << "TAK" << endl;
  } else {
    cout << "NIE" << endl;
  }
  T.dodaj("Gollnik","Monika");
  T.dodaj("Kowalski","Aleksy");
  T.dodaj("Nowak","Bogdan");
  cout << T.zliczelementy() << endl;
  cout << T["Gollnik"] << endl;
  cout << T["Kowalski"] << endl;
  T.dodaj("Kowalski","Oleksy");
  cout << T["Kowalski"] << endl;
  T.usun("Kowalski");
  cout << T.zliczelementy() << endl;
  aiter<string,string> it;
  for (it=T.begin();it!=T.end();it++) {
    cout << *it << endl;
  }
}
