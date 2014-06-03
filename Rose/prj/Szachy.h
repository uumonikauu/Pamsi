#ifndef SZACHY_H
#define SZACHY_H
#include <vector>
#include <cassert>
#include <string>
#include <iostream>
#include <algorithm>
//normalne ułożenie szachownicy //zaimpelentowane obrocone o -90*
//  A B C D E F G H     //  1 2 3 4 5 6 7 8
//8                     //A
//7                     //B
//6                     //C
//5                     //D
//4                     //E
//3                     //F
//2                     //G
//1                     //H
#define MAT 100000
#define SZACH 0
#define PAT 0
#define WHITE 0
#define BLACK 1
#define PION 1
#define WIEZA 2
#define SKOCZEK 3
#define GONIEC 4
#define HETMAN 5
#define KROL 6
#define CIECIA 1

class Pole {
    char _x;//A,B,C,...
    char _y;//1,2,3,...
    public:
    Pole(char x, char y);
    Pole(std::string nazwa);
    char x() const {return _x;}
    char y() const {return _y;}
};

bool operator== (Pole P1, Pole P2);
bool operator!= (Pole P1, Pole P2);

class Figura {
    bool _kolor; //0 - bialy, 1 czarny;
    char _iden; //0 - brak, 1-pion, 2-wieza, 3-skoczek, 4-goniec, 5-hetman, 6-krol;
    Pole _p;
    bool _ruszona;
    public:
    Figura(Pole p, char iden, bool kolor);//przy iden =0 bool nie ma znaczenia
    Figura(char x,char y, char iden, bool kolor);//przy iden =0 bool nie ma znaczenia
    Pole p() const {return _p;}
    bool kolor() const {return _kolor;}
    char figtype() const {return _iden;}
    void zeruj_ruszona() {_ruszona =0;}
    bool ruszona() const {return _ruszona;}
    void clear() {_iden=0;}
    void awansuj(char iden);
};

class Wiersz {
    Figura tab[8];
    public:
    Figura &operator[] (unsigned char ind);
    const Figura &operator[] (unsigned char ind) const;
};

class Plansza {
    Wiersz tab[8];
    public:
    Wiersz &operator[] (unsigned char ind);
    const Wiersz &operator[] (unsigned char ind) const;
};

class Rozgrywka {
    char awans_typ;
public:
    Pole wking;
    Pole bking;
    Rozgrywka *wyb;
    Pole st;
    Pole cl;
    int ocena;
    bool next; //0 biale, 1 czarne
    Plansza P;
    char rekursja;
    std::string logtmp;
    std::string log;
    std::vector<Figura> Biale;
    std::vector<Figura> Czarne;
    std::vector<Pole> bicie_w_przelocie;
    Rozgrywka();
    Rozgrywka(Rozgrywka &R1, Pole start, Pole cel);
    ~Rozgrywka();
    std::vector<Pole> ruchy(Figura Fig);
    std::vector<Pole> ruchy_tr(Figura Fig); //juz budujaca drzewo, WYWOLYWAC TYLKO W PETLI PO baza_fig();
    std::vector<Pole> ruchybs(Figura Fig);
    void ruch(Pole start, Pole cel);
    void baza_fig();
    char typ_awans() const;
    char zmien_awanstyp(char nowy);
    void addlog(Pole start, Pole cel);
    void addlog(std::string napis);
    std::vector <std::vector<Pole> >mozliwe;
    std::vector<Rozgrywka> wsk;
    void rebulid_tree();
    void bulid_tree();
    void bulid_one();
    int ocen();
    void minmax();
    bool szach(Pole spr); //uzyc bazy figur najpierw!!
};

int wmin(int a,int b);
int wmax(int a,int b);


#endif // SZACHY_H
