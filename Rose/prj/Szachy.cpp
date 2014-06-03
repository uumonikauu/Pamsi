#include "Szachy.h"

Pole::Pole (char x=0, char y=0) {
    _x=x;
    _y=y;
}

Pole::Pole (std::string nazwa) {
    _x=nazwa[0]-64;
    _y=nazwa[1]-48;
}

bool operator== (Pole P1, Pole P2) {
    return ((P1.x() == P2.x()) && (P1.y() == P2.y()));
}

bool operator!= (Pole P1, Pole P2) {
    return ((P1.x() != P2.x()) || (P1.y() != P2.y()));
}

Figura::Figura(Pole p, char iden=0, bool kolor=0) {
    _kolor=kolor;
    _iden=iden;
    _p=p;
    _ruszona=1;
}

Figura::Figura(char x=0, char y=0, char iden=0, bool kolor=0) {
    _kolor=kolor;
    _iden=iden;
    _p=Pole(x,y);
    _ruszona=1;
}

void Figura::awansuj(char iden) {
    assert(_iden==PION);
    _iden = iden;
}

Figura &Wiersz::operator[] (unsigned char ind) {
    return tab[ind-1];
}

const Figura &Wiersz::operator[] (unsigned char ind) const {
    return tab[ind-1];
}

Wiersz &Plansza::operator[] (unsigned char ind) {
    return tab[ind-1];
}

const Wiersz &Plansza::operator[] (unsigned char ind) const {
    return tab[ind-1];
}

Rozgrywka::Rozgrywka() {
    wyb = NULL;
    rekursja = 3;
    ocena =0;
    awans_typ = GONIEC;
    log = logtmp = "";
    next=0;
    P[1][1]=Figura(1,1,WIEZA,WHITE);
    P[2][1]=Figura(2,1,SKOCZEK,WHITE);
    P[3][1]=Figura(3,1,GONIEC,WHITE);
    P[4][1]=Figura(4,1,HETMAN,WHITE);
    P[5][1]=Figura(5,1,KROL,WHITE);
    wking = Pole(5,1);
    P[6][1]=Figura(6,1,GONIEC,WHITE);
    P[7][1]=Figura(7,1,SKOCZEK,WHITE);
    P[8][1]=Figura(8,1,WIEZA,WHITE);
    P[1][2]=Figura(1,2,PION,WHITE);
    P[2][2]=Figura(2,2,PION,WHITE);
    P[3][2]=Figura(3,2,PION,WHITE);
    P[4][2]=Figura(4,2,PION,WHITE);
    P[5][2]=Figura(5,2,PION,WHITE);
    P[6][2]=Figura(6,2,PION,WHITE);
    P[7][2]=Figura(7,2,PION,WHITE);
    P[8][2]=Figura(8,2,PION,WHITE);
    P[1][8]=Figura(1,8,WIEZA,BLACK);
    P[2][8]=Figura(2,8,SKOCZEK,BLACK);
    P[3][8]=Figura(3,8,GONIEC,BLACK);
    P[4][8]=Figura(4,8,HETMAN,BLACK);
    P[5][8]=Figura(5,8,KROL,BLACK);
    bking = Pole(5,8);
    P[6][8]=Figura(6,8,GONIEC,BLACK);
    P[7][8]=Figura(7,8,SKOCZEK,BLACK);
    P[8][8]=Figura(8,8,WIEZA,BLACK);
    P[1][7]=Figura(1,7,PION,BLACK);
    P[2][7]=Figura(2,7,PION,BLACK);
    P[3][7]=Figura(3,7,PION,BLACK);
    P[4][7]=Figura(4,7,PION,BLACK);
    P[5][7]=Figura(5,7,PION,BLACK);
    P[6][7]=Figura(6,7,PION,BLACK);
    P[7][7]=Figura(7,7,PION,BLACK);
    P[8][7]=Figura(8,7,PION,BLACK);
    P[1][1].zeruj_ruszona();
    P[5][1].zeruj_ruszona();
    P[8][1].zeruj_ruszona();
    P[1][8].zeruj_ruszona();
    P[5][8].zeruj_ruszona();
    P[8][8].zeruj_ruszona();
}

Rozgrywka::Rozgrywka(Rozgrywka &R1, Pole start, Pole cel) {
    wyb = NULL;
    awans_typ = HETMAN;
    ocena =0;
    st=start;
    cl=cel;
    bking = R1.bking;
    wking = R1.wking;
    rekursja = R1.rekursja-1;
    next = R1.next;
    P = R1.P;
    bicie_w_przelocie = R1.bicie_w_przelocie;
    ruch(start,cel);
}

std::vector<Pole> Rozgrywka::ruchy(Figura Fig) { //0 biały, 1 czarny
    std::vector<Pole> wynik;
    unsigned char x=Fig.p().x();
    unsigned char y=Fig.p().y();
    Rozgrywka tmp;
    switch (Fig.figtype()) {
        case PION:{
            if (Fig.kolor() == WHITE) {
                if (P[x][y+1].figtype()==0) {
                    tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+1));
                    if (!tmp.szach(tmp.wking)) {
                        wynik.push_back(Pole(x,y+1));
                    }
                }
                if (x!=1) {
                    if (P[x-1][y+1].figtype()!=0 && Fig.kolor()!=P[x-1][y+1].kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x-1,y+1));
                        }
                    }
                    if (!bicie_w_przelocie.empty())
                        if (Pole(x-1,y+1) == bicie_w_przelocie[0]) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x-1,y+1));///////////////////////////////////musze o tym pamietac przy ruchu.
                            }
                        }
                }
                if (x!=8) {
                    if (P[x+1][y+1].figtype()!=0 && Fig.kolor()!=P[x+1][y+1].kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x+1,y+1));
                        }
                    }
                    if (!bicie_w_przelocie.empty())
                        if (Pole(x+1,y+1) == bicie_w_przelocie[0]) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x+1,y+1));///////////////////////////////////musze o tym pamietac przy ruchu.
                            }
                        }
                }
                if (y==2) {
                    if (P[x][y+1].figtype()==0) {
                        if (P[x][y+2].figtype()==0) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+2));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,y+2));
                            }
                        }
                    }
                }
            }
            else {
                if (P[x][y-1].figtype()==0) {
                    tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-1));
                    if (!tmp.szach(tmp.bking)) {
                        wynik.push_back(Pole(x,y-1));
                    }
                }
                if (x!=1) {
                    if (P[x-1][y-1].figtype()!=0 && Fig.kolor()!=P[x-1][y-1].kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x-1,y-1));
                        }
                    }
                    if (!bicie_w_przelocie.empty())
                        if (Pole(x-1,y-1) == bicie_w_przelocie[0]) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x-1,y-1));
                            }
                        }
                }
                if (x!=8) {
                    if (P[x+1][y-1].figtype()!=0 && Fig.kolor()!=P[x+1][y-1].kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x+1,y-1));
                        }
                    }
                    if (!bicie_w_przelocie.empty()) {
                        if (Pole(x+1,y-1) == bicie_w_przelocie[0]) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x+1,y-1));
                            }
                        }
                    }
                }
                if (y==7) {
                    if (P[x][y-1].figtype()==0) {
                        if (P[x][y-2].figtype()==0) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-2));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,y-2));
                            }
                        }
                    }
                }
            }
        };break;
        case WIEZA:{
            for (int i=x+1;i<=8;i++) {
                if (P[i][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,y));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,y));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,y));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,y));
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=x-1;i>=1;i--) {
                if (P[i][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,y));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,y));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,y));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,y));
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=y+1;i<=8;i++) {
                if (P[x][i].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,i));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,i));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][i].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,i));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,i));
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=y-1;i>=1;i--) {
                if (P[x][i].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,i));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,i));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][i].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,i));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,i));
                            }
                        }
                    }
                    break;
                }
            }
        };break;
        case SKOCZEK:{
            char i;
            char j;
            i=x+2;
            j=y+1;
            if (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor()!= P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                }
            }
            i=x+2;
            j=y-1;
            if (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                }
            }
            i=x+1;
            j=y+2;
            if (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                }
            }
            i=x-1;
            j=y+2;
            if (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                }
            }
            i=x-2;
            j=y+1;
            if (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                }
            }
            i=x-2;
            j=y-1;
            if (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                }
            }
            i=x-1;
            j=y-2;
            if (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                }
            }
            i=x+1;
            j=y-2;
            if (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                }
            }
        };break;
        case GONIEC:{
            char i=x+1;
            char j=y+1;
            while (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                    break;
                }
                i++;
                j++;
            }
            i=x-1;
            j=y+1;
            while (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                    break;
                }
                i--;
                j++;
            }
            i=x+1;
            j=y-1;
            while (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                    break;
                }
                i++;
                j--;
            }
            i=x-1;
            j=y-1;
            while (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                    break;
                }
                i--;
                j--;
            }
        };break;
        case HETMAN:{
            char i=x+1;
            char j=y+1;
            while (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                    break;
                }
                i++;
                j++;
            }
            i=x-1;
            j=y+1;
            while (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                    break;
                }
                i--;
                j++;
            }
            i=x+1;
            j=y-1;
            while (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                    break;
                }
                i++;
                j--;
            }
            i=x-1;
            j=y-1;
            while (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                            }
                        }
                    }
                    break;
                }
                i--;
                j--;
            }
            for (int i=x+1;i<=8;i++) {
                if (P[i][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,y));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,y));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,y));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,y));
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=x-1;i>=1;i--) {
                if (P[i][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,y));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,y));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,y));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,y));
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=y+1;i<=8;i++) {
                if (P[x][i].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,i));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,i));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][i].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,i));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,i));
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=y-1;i>=1;i--) {
                if (P[x][i].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,i));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,i));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][i].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,i));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,i));
                            }
                        }
                    }
                    break;
                }
            }
        };break;
        case KROL:{
            bool m_roszp=1;
            bool m_roszl=1;
            if (x+1<=8 && y+1<=8) {
                if (P[x+1][y+1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x+1,y+1));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x+1,y+1));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x+1][y+1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x+1,y+1));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x+1,y+1));
                            }
                        }
                    }
                }
            }
            if (x+1<=8) {
                if (P[x+1][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x+1,y));
                            if (Fig.ruszona() == 0) {
                                if (P[8][y].ruszona() == 0) {
                                    for (int i=7;i>x;i--) {
                                        if (P[i][y].figtype() != 0) {
                                            m_roszl=0;
                                        }
                                    }
                                    if (m_roszl) {
                                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+2,y));
                                        if (!tmp.szach(tmp.bking)) {
                                            wynik.push_back(Pole(x+2,y));
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x+1,y));
                            if (Fig.ruszona() == 0) {
                                if (P[8][y].ruszona() == 0) {
                                    for (int i=7;i>x;i--) {
                                        if (P[i][y].figtype() != 0) {
                                            m_roszl=0;
                                        }
                                    }
                                    if (m_roszl) {
                                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+2,y));
                                        if (!tmp.szach(tmp.wking)) {
                                            wynik.push_back(Pole(x+2,y));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x+1][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x+1,y));
                                if (Fig.ruszona() == 0) {
                                    if (P[8][y].ruszona() == 0) {
                                        for (int i=7;i>x;i--) {
                                            if (P[i][y].figtype() != 0) {
                                                m_roszl=0;
                                            }
                                        }
                                        if (m_roszl) {
                                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+2,y));
                                            if (!tmp.szach(tmp.bking)) {
                                                wynik.push_back(Pole(x+2,y));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x+1,y));
                                if (Fig.ruszona() == 0) {
                                    if (P[8][y].ruszona() == 0) {
                                        for (int i=7;i>x;i--) {
                                            if (P[i][y].figtype() != 0) {
                                                m_roszl=0;
                                            }
                                        }
                                        if (m_roszl) {
                                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+2,y));
                                            if (!tmp.szach(tmp.wking)) {
                                                wynik.push_back(Pole(x+2,y));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (x+1<=8 && y-1>=1) {
                if (P[x+1][y-1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x+1,y-1));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x+1,y-1));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x+1][y-1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x+1,y-1));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x+1,y-1));
                            }
                        }
                    }
                }
            }
            if (y+1<=8) {
                if (P[x][y+1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,y+1));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,y+1));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][y+1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,y+1));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,y+1));
                            }
                        }
                    }
                }
            }
            if (y-1>=1) {
                if (P[x][y-1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,y-1));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,y-1));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][y-1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,y-1));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,y-1));
                            }
                        }
                    }
                }
            }
            if (x-1>=1 && y+1<=8) {
                if (P[x-1][y+1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x-1,y+1));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x-1,y+1));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x-1][y+1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x-1,y+1));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x-1,y+1));
                            }
                        }
                    }
                }
            }
            if (x-1>=1) {
                if (P[x-1][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x-1,y));
                            if (Fig.ruszona() == 0) {
                                if (P[1][y].ruszona() == 0) {
                                    for (int i=2;i<x;i++) {
                                        if (P[i][y].figtype() != 0) {
                                            m_roszp=0;
                                        }
                                    }
                                    if (m_roszp) {
                                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-2,y));
                                        if (!tmp.szach(tmp.bking)) {
                                            wynik.push_back(Pole(x-2,y));
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x-1,y));
                            if (Fig.ruszona() == 0) {
                                if (P[1][y].ruszona() == 0) {
                                    for (int i=2;i<x;i++) {
                                        if (P[i][y].figtype() != 0) {
                                            m_roszp=0;
                                        }
                                    }
                                    if (m_roszp) {
                                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-2,y));
                                        if (!tmp.szach(tmp.wking)) {
                                            wynik.push_back(Pole(x-2,y));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x-1][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x-1,y));
                                if (Fig.ruszona() == 0) {
                                    if (P[1][y].ruszona() == 0) {
                                        for (int i=2;i<x;i++) {
                                            if (P[i][y].figtype() != 0) {
                                                m_roszp=0;
                                            }
                                        }
                                        if (m_roszp) {
                                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-2,y));
                                            if (!tmp.szach(tmp.bking)) {
                                                wynik.push_back(Pole(x-2,y));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x-1,y));
                                if (Fig.ruszona() == 0) {
                                    if (P[1][y].ruszona() == 0) {
                                        for (int i=2;i<x;i++) {
                                            if (P[i][y].figtype() != 0) {
                                                m_roszp=0;
                                            }
                                        }
                                        if (m_roszp) {
                                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-2,y));
                                            if (!tmp.szach(tmp.wking)) {
                                                wynik.push_back(Pole(x-2,y));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (x-1>=1 && y-1>=1) {
                if (P[x-1][y-1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x-1,y-1));
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x-1,y-1));
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x-1][y-1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x-1,y-1));
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x-1,y-1));
                            }
                        }
                    }
                }
            }
        };break;
    }
    return wynik;
}

std::vector<Pole> Rozgrywka::ruchy_tr(Figura Fig) { //0 biały, 1 czarny
    std::vector<Pole> wynik;
    unsigned char x=Fig.p().x();
    unsigned char y=Fig.p().y();
    Rozgrywka tmp;
    switch (Fig.figtype()) {
        case PION:{
            if (Fig.kolor() == WHITE) {
                if (P[x][y+1].figtype()==0) {
                    tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+1));
                    if (!tmp.szach(tmp.wking)) {
                        wynik.push_back(Pole(x,y+1));
                        wsk.push_back(tmp);
                    }
                }
                if (x!=1) {
                    if (P[x-1][y+1].figtype()!=0 && Fig.kolor()!=P[x-1][y+1].kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x-1,y+1));
                            wsk.push_back(tmp);
                        }
                    }
                    if (!bicie_w_przelocie.empty())
                        if (Pole(x-1,y+1) == bicie_w_przelocie[0]) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x-1,y+1));///////////////////////////////////musze o tym pamietac przy ruchu.
                                wsk.push_back(tmp);
                            }
                        }
                }
                if (x!=8) {
                    if (P[x+1][y+1].figtype()!=0 && Fig.kolor()!=P[x+1][y+1].kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x+1,y+1));
                            wsk.push_back(tmp);
                        }
                    }
                    if (!bicie_w_przelocie.empty())
                        if (Pole(x+1,y+1) == bicie_w_przelocie[0]) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x+1,y+1));///////////////////////////////////musze o tym pamietac przy ruchu.
                                wsk.push_back(tmp);
                            }
                        }
                }
                if (y==2) {
                    if (P[x][y+1].figtype()==0) {
                        if (P[x][y+2].figtype()==0) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+2));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,y+2));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            else {
                if (P[x][y-1].figtype()==0) {
                    tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-1));
                    if (!tmp.szach(tmp.bking)) {
                        wynik.push_back(Pole(x,y-1));
                        wsk.push_back(tmp);
                    }
                }
                if (x!=1) {
                    if (P[x-1][y-1].figtype()!=0 && Fig.kolor()!=P[x-1][y-1].kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x-1,y-1));
                            wsk.push_back(tmp);
                        }
                    }
                    if (!bicie_w_przelocie.empty())
                        if (Pole(x-1,y-1) == bicie_w_przelocie[0]) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x-1,y-1));
                                wsk.push_back(tmp);
                            }
                        }
                }
                if (x!=8) {
                    if (P[x+1][y-1].figtype()!=0 && Fig.kolor()!=P[x+1][y-1].kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x+1,y-1));
                            wsk.push_back(tmp);
                        }
                    }
                    if (!bicie_w_przelocie.empty()) {
                        if (Pole(x+1,y-1) == bicie_w_przelocie[0]) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x+1,y-1));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
                if (y==7) {
                    if (P[x][y-1].figtype()==0) {
                        if (P[x][y-2].figtype()==0) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-2));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,y-2));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
        };break;
        case WIEZA:{
            for (int i=x+1;i<=8;i++) {
                if (P[i][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,y));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,y));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,y));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,y));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=x-1;i>=1;i--) {
                if (P[i][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,y));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,y));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,y));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,y));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=y+1;i<=8;i++) {
                if (P[x][i].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,i));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,i));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][i].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,i));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,i));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=y-1;i>=1;i--) {
                if (P[x][i].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,i));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,i));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][i].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,i));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,i));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
            }
        };break;
        case SKOCZEK:{
            char i;
            char j;
            i=x+2;
            j=y+1;
            if (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor()!= P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            i=x+2;
            j=y-1;
            if (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            i=x+1;
            j=y+2;
            if (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            i=x-1;
            j=y+2;
            if (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            i=x-2;
            j=y+1;
            if (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            i=x-2;
            j=y-1;
            if (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            i=x-1;
            j=y-2;
            if (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            i=x+1;
            j=y-2;
            if (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
        };break;
        case GONIEC:{
            char i=x+1;
            char j=y+1;
            while (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
                i++;
                j++;
            }
            i=x-1;
            j=y+1;
            while (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
                i--;
                j++;
            }
            i=x+1;
            j=y-1;
            while (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
                i++;
                j--;
            }
            i=x-1;
            j=y-1;
            while (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
                i--;
                j--;
            }
        };break;
        case HETMAN:{
            char i=x+1;
            char j=y+1;
            while (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
                i++;
                j++;
            }
            i=x-1;
            j=y+1;
            while (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
                i--;
                j++;
            }
            i=x+1;
            j=y-1;
            while (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
                i++;
                j--;
            }
            i=x-1;
            j=y-1;
            while (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,j));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,j));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,j));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
                i--;
                j--;
            }
            for (int i=x+1;i<=8;i++) {
                if (P[i][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,y));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,y));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,y));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,y));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=x-1;i>=1;i--) {
                if (P[i][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(i,y));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(i,y));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(i,y));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(i,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(i,y));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=y+1;i<=8;i++) {
                if (P[x][i].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,i));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,i));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][i].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,i));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,i));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
            }
            for (int i=y-1;i>=1;i--) {
                if (P[x][i].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,i));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,i));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][i].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,i));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,i));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,i));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                    break;
                }
            }
        };break;
        case KROL:{
            bool m_roszp=1;
            bool m_roszl=1;
            if (x+1<=8 && y+1<=8) {
                if (P[x+1][y+1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x+1,y+1));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x+1,y+1));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x+1][y+1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x+1,y+1));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y+1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x+1,y+1));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            if (x+1<=8) {
                if (P[x+1][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x+1,y));
                            wsk.push_back(tmp);
                            if (Fig.ruszona() == 0) {
                                if (P[8][y].ruszona() == 0) {
                                    for (int i=7;i>x;i--) {
                                        if (P[i][y].figtype() != 0) {
                                            m_roszl=0;
                                        }
                                    }
                                    if (m_roszl) {
                                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+2,y));
                                        if (!tmp.szach(tmp.bking)) {
                                            wynik.push_back(Pole(x+2,y));
                                            wsk.push_back(tmp);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x+1,y));
                            wsk.push_back(tmp);
                            if (Fig.ruszona() == 0) {
                                if (P[8][y].ruszona() == 0) {
                                    for (int i=7;i>x;i--) {
                                        if (P[i][y].figtype() != 0) {
                                            m_roszl=0;
                                        }
                                    }
                                    if (m_roszl) {
                                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+2,y));
                                        if (!tmp.szach(tmp.wking)) {
                                            wynik.push_back(Pole(x+2,y));
                                            wsk.push_back(tmp);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x+1][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x+1,y));
                                wsk.push_back(tmp);
                                if (Fig.ruszona() == 0) {
                                    if (P[8][y].ruszona() == 0) {
                                        for (int i=7;i>x;i--) {
                                            if (P[i][y].figtype() != 0) {
                                                m_roszl=0;
                                            }
                                        }
                                        if (m_roszl) {
                                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+2,y));
                                            if (!tmp.szach(tmp.bking)) {
                                                wynik.push_back(Pole(x+2,y));
                                                wsk.push_back(tmp);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x+1,y));
                                wsk.push_back(tmp);
                                if (Fig.ruszona() == 0) {
                                    if (P[8][y].ruszona() == 0) {
                                        for (int i=7;i>x;i--) {
                                            if (P[i][y].figtype() != 0) {
                                                m_roszl=0;
                                            }
                                        }
                                        if (m_roszl) {
                                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+2,y));
                                            if (!tmp.szach(tmp.wking)) {
                                                wynik.push_back(Pole(x+2,y));
                                                wsk.push_back(tmp);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (x+1<=8 && y-1>=1) {
                if (P[x+1][y-1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x+1,y-1));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x+1,y-1));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x+1][y-1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x+1,y-1));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x+1,y-1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x+1,y-1));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            if (y+1<=8) {
                if (P[x][y+1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,y+1));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,y+1));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][y+1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,y+1));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y+1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,y+1));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            if (y-1>=1) {
                if (P[x][y-1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x,y-1));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x,y-1));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x][y-1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x,y-1));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x,y-1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x,y-1));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            if (x-1>=1 && y+1<=8) {
                if (P[x-1][y+1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x-1,y+1));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x-1,y+1));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x-1][y+1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x-1,y+1));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y+1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x-1,y+1));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
            if (x-1>=1) {
                if (P[x-1][y].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x-1,y));
                            wsk.push_back(tmp);
                            if (Fig.ruszona() == 0) {
                                if (P[1][y].ruszona() == 0) {
                                    for (int i=2;i<x;i++) {
                                        if (P[i][y].figtype() != 0) {
                                            m_roszp=0;
                                        }
                                    }
                                    if (m_roszp) {
                                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-2,y));
                                        if (!tmp.szach(tmp.bking)) {
                                            wynik.push_back(Pole(x-2,y));
                                            wsk.push_back(tmp);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x-1,y));
                            wsk.push_back(tmp);
                            if (Fig.ruszona() == 0) {
                                if (P[1][y].ruszona() == 0) {
                                    for (int i=2;i<x;i++) {
                                        if (P[i][y].figtype() != 0) {
                                            m_roszp=0;
                                        }
                                    }
                                    if (m_roszp) {
                                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-2,y));
                                        if (!tmp.szach(tmp.wking)) {
                                            wynik.push_back(Pole(x-2,y));
                                            wsk.push_back(tmp);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x-1][y].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x-1,y));
                                wsk.push_back(tmp);
                                if (Fig.ruszona() == 0) {
                                    if (P[1][y].ruszona() == 0) {
                                        for (int i=2;i<x;i++) {
                                            if (P[i][y].figtype() != 0) {
                                                m_roszp=0;
                                            }
                                        }
                                        if (m_roszp) {
                                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-2,y));
                                            if (!tmp.szach(tmp.bking)) {
                                                wynik.push_back(Pole(x-2,y));
                                                wsk.push_back(tmp);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x-1,y));
                                wsk.push_back(tmp);
                                if (Fig.ruszona() == 0) {
                                    if (P[1][y].ruszona() == 0) {
                                        for (int i=2;i<x;i++) {
                                            if (P[i][y].figtype() != 0) {
                                                m_roszp=0;
                                            }
                                        }
                                        if (m_roszp) {
                                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-2,y));
                                            if (!tmp.szach(tmp.wking)) {
                                                wynik.push_back(Pole(x-2,y));
                                                wsk.push_back(tmp);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (x-1>=1 && y-1>=1) {
                if (P[x-1][y-1].figtype()==0) {
                    if (Fig.kolor()) {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                        if (!tmp.szach(tmp.bking)) {
                            wynik.push_back(Pole(x-1,y-1));
                            wsk.push_back(tmp);
                        }
                    }
                    else {
                        tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                        if (!tmp.szach(tmp.wking)) {
                            wynik.push_back(Pole(x-1,y-1));
                            wsk.push_back(tmp);
                        }
                    }
                }
                else {
                    if (Fig.kolor() != P[x-1][y-1].kolor()) {
                        if (Fig.kolor()) {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                            if (!tmp.szach(tmp.bking)) {
                                wynik.push_back(Pole(x-1,y-1));
                                wsk.push_back(tmp);
                            }
                        }
                        else {
                            tmp=Rozgrywka(*this,Fig.p(),Pole(x-1,y-1));
                            if (!tmp.szach(tmp.wking)) {
                                wynik.push_back(Pole(x-1,y-1));
                                wsk.push_back(tmp);
                            }
                        }
                    }
                }
            }
        };break;
    }
    return wynik;
}

std::vector<Pole> Rozgrywka::ruchybs(Figura Fig) { //0 biały, 1 czarny
    std::vector<Pole> wynik;
    char x=Fig.p().x();
    char y=Fig.p().y();
    switch (Fig.figtype()) {
        case PION:{
            if (Fig.kolor() == WHITE) {
                if (P[x][y+1].figtype()==0) {
                    wynik.push_back(Pole(x,y+1));
                }
                if (x!=1) {
                    if (P[x-1][y+1].figtype()!=0 && Fig.kolor()!=P[x-1][y+1].kolor()) {
                        wynik.push_back(Pole(x-1,y+1));
                    }
                    if (!bicie_w_przelocie.empty())
                        if (Pole(x-1,y+1) == bicie_w_przelocie[0])
                            wynik.push_back(Pole(x-1,y+1));///////////////////////////////////musze o tym pamietac przy ruchu.
                }
                if (x!=8) {
                    if (P[x+1][y+1].figtype()!=0 && Fig.kolor()!=P[x+1][y+1].kolor()) {
                        wynik.push_back(Pole(x+1,y+1));
                    }
                    if (!bicie_w_przelocie.empty())
                        if (Pole(x+1,y+1) == bicie_w_przelocie[0])
                            wynik.push_back(Pole(x+1,y+1));///////////////////////////////////musze o tym pamietac przy ruchu.
                }
                if (y==2) {
                    if (P[x][y+1].figtype()==0) {
                        if (P[x][y+2].figtype()==0)
                            wynik.push_back(Pole(x,y+2));
                    }
                }
            }
            else {
                if (P[x][y-1].figtype()==0) {
                    wynik.push_back(Pole(x,y-1));
                }
                if (x!=1) {
                    if (P[x-1][y-1].figtype()!=0 && Fig.kolor()!=P[x-1][y-1].kolor()) {
                        wynik.push_back(Pole(x-1,y-1));
                    }
                    if (!bicie_w_przelocie.empty())
                        if (Pole(x-1,y-1) == bicie_w_przelocie[0])
                            wynik.push_back(Pole(x-1,y-1));///////////////////////////////////musze o tym pamietac przy ruchu.
                }
                if (x!=8) {
                    if (P[x+1][y-1].figtype()!=0 && Fig.kolor()!=P[x+1][y-1].kolor()) {
                        wynik.push_back(Pole(x+1,y-1));
                    }
                    if (!bicie_w_przelocie.empty())
                        if (Pole(x+1,y-1) == bicie_w_przelocie[0])
                            wynik.push_back(Pole(x+1,y-1));///////////////////////////////////musze o tym pamietac przy ruchu.
                }
                if (y==7) {
                    if (P[x][y-1].figtype()==0) {
                        if (P[x][y-2].figtype()==0)
                            wynik.push_back(Pole(x,y-2));
                    }
                }
            }
        };break;
        case WIEZA:{
            for (int i=x+1;i<=8;i++) {
                if (P[i][y].figtype()==0) {
                    wynik.push_back(Pole(i,y));
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor())
                        wynik.push_back(Pole(i,y));
                    break;
                }
            }
            for (int i=x-1;i>=1;i--) {
                if (P[i][y].figtype()==0) {
                    wynik.push_back(Pole(i,y));
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor())
                        wynik.push_back(Pole(i,y));
                    break;
                }
            }
            for (int i=y+1;i<=8;i++) {
                if (P[x][i].figtype()==0) {
                    wynik.push_back(Pole(x,i));
                }
                else {
                    if (Fig.kolor() != P[x][i].kolor())
                        wynik.push_back(Pole(x,i));
                    break;
                }
            }
            for (int i=y-1;i>=1;i--) {
                if (P[x][i].figtype()==0) {
                    wynik.push_back(Pole(x,i));
                }
                else {
                    if (Fig.kolor()!= P[x][i].kolor())
                        wynik.push_back(Pole(x,i));
                    break;
                }
            }
        };break;
        case SKOCZEK:{
            char i;
            char j;
            i=x+2;
            j=y+1;
            if (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor()!= P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                }
            }
            i=x+2;
            j=y-1;
            if (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                }
            }
            i=x+1;
            j=y+2;
            if (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                }
            }
            i=x-1;
            j=y+2;
            if (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                }
            }
            i=x-2;
            j=y+1;
            if (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                }
            }
            i=x-2;
            j=y-1;
            if (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                }
            }
            i=x-1;
            j=y-2;
            if (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                }
            }
            i=x+1;
            j=y-2;
            if (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                }
            }
        };break;
        case GONIEC:{
            char i=x+1;
            char j=y+1;
            while (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                    break;
                }
                i++;
                j++;
            }
            i=x-1;
            j=y+1;
            while (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                    break;
                }
                i--;
                j++;
            }
            i=x+1;
            j=y-1;
            while (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                    break;
                }
                i++;
                j--;
            }
            i=x-1;
            j=y-1;
            while (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                    break;
                }
                i--;
                j--;
            }
        };break;
        case HETMAN:{
            char i=x+1;
            char j=y+1;
            while (i<=8 && j<=8) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                    break;
                }
                i++;
                j++;
            }
            i=x-1;
            j=y+1;
            while (i>=1 && j<=8) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                    break;
                }
                i--;
                j++;
            }
            i=x+1;
            j=y-1;
            while (i<=8 && j>=1) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                    break;
                }
                i++;
                j--;
            }
            i=x-1;
            j=y-1;
            while (i>=1 && j>=1) {
                if (P[i][j].figtype()==0) {
                    wynik.push_back(Pole(i,j));
                }
                else {
                    if (Fig.kolor() != P[i][j].kolor())
                        wynik.push_back(Pole(i,j));
                    break;
                }
                i--;
                j--;
            }
            for (i=x+1;i<=8;i++) {
                if (P[i][y].figtype()==0) {
                    wynik.push_back(Pole(i,y));
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor())
                        wynik.push_back(Pole(i,y));
                    break;
                }
            }
            for (i=x-1;i>=1;i--) {
                if (P[i][y].figtype()==0) {
                    wynik.push_back(Pole(i,y));
                }
                else {
                    if (Fig.kolor() != P[i][y].kolor())
                        wynik.push_back(Pole(i,y));
                    break;
                }
            }
            for (i=y+1;i<=8;i++) {
                if (P[x][i].figtype()==0) {
                    wynik.push_back(Pole(x,i));
                }
                else {
                    if (Fig.kolor() != P[x][i].kolor())
                        wynik.push_back(Pole(x,i));
                    break;
                }
            }
            for (i=y-1;i>=1;i--) {
                if (P[x][i].figtype()==0) {
                    wynik.push_back(Pole(x,i));
                }
                else {
                    if (Fig.kolor() != P[x][i].kolor())
                        wynik.push_back(Pole(x,i));
                    break;
                }
            }
        };break;
        case KROL:{
            if (x+1<=8 && y+1<=8) { //do dopracowania pod kątem wejścia na szach i roszady "po szachu". pomysł roboczy: sprawdzać czy przeciwnik moze uzyskac wartośc #MAT
                if (P[x+1][y+1].figtype()==0) {
                    wynik.push_back(Pole(x+1,y+1));
                }
                else {
                    if (Fig.kolor() != P[x+1][y+1].kolor())
                        wynik.push_back(Pole(x+1,y+1));
                }
            }
            if (x+1<=8) {
                if (P[x+1][y].figtype()==0) {
                    wynik.push_back(Pole(x+1,y));
                }
                else {
                    if (Fig.kolor() != P[x+1][y].kolor())
                        wynik.push_back(Pole(x+1,y));
                }
            }
            if (x+1<=8 && y-1>=1) {
                if (P[x+1][y-1].figtype()==0) {
                    wynik.push_back(Pole(x+1,y-1));
                }
                else {
                    if (Fig.kolor() != P[x+1][y-1].kolor())
                        wynik.push_back(Pole(x+1,y-1));
                }
            }
            if (y+1<=8) {
                if (P[x][y+1].figtype()==0) {
                    wynik.push_back(Pole(x,y+1));
                }
                else {
                    if (Fig.kolor() != P[x][y+1].kolor())
                        wynik.push_back(Pole(x,y+1));
                }
            }
            if (y-1>=1) {
                if (P[x][y-1].figtype()==0) {
                    wynik.push_back(Pole(x,y-1));
                }
                else {
                    if (Fig.kolor() != P[x][y-1].kolor())
                        wynik.push_back(Pole(x,y-1));
                }
            }
            if (x-1>=1 && y+1<=8) {
                if (P[x-1][y+1].figtype()==0) {
                    wynik.push_back(Pole(x-1,y+1));
                }
                else {
                    if (Fig.kolor() != P[x-1][y+1].kolor())
                        wynik.push_back(Pole(x-1,y+1));
                }
            }
            if (x-1>=1) {
                if (P[x-1][y].figtype()==0) {
                    wynik.push_back(Pole(x-1,y));
                }
                else {
                    if (Fig.kolor() != P[x-1][y].kolor())
                        wynik.push_back(Pole(x-1,y));
                }
            }
            if (x-1>=1 && y-1>=1) {
                if (P[x-1][y-1].figtype()==0) {
                    wynik.push_back(Pole(x-1,y-1));
                }
                else {
                    if (Fig.kolor() != P[x-1][y-1].kolor())
                        wynik.push_back(Pole(x-1,y-1));
                }
            }
            bool m_roszp=1;
            bool m_roszl=1;
            if (Fig.ruszona() == 0) {
                if (P[1][y].ruszona() == 0) {
                    for (int i=2;i<x;i++) {
                        if (P[i][y].figtype() != 0) {
                            m_roszp=0;
                        }
                    }
                    if (m_roszp)
                        wynik.push_back(Pole(x-2,y));
                }
                if (P[8][y].ruszona() == 0) {
                    for (int i=7;i>x;i--) {
                        if (P[i][y].figtype() != 0) {
                            m_roszl=0;
                        }
                    }
                    if (m_roszl)
                        wynik.push_back(Pole(x+2,y));
                }
            }
        };break;
    }
    return wynik;
}

void Rozgrywka::ruch(Pole start, Pole cel) {
    baza_fig();
    next=!next;
    if (P[start.x()][start.y()].figtype() == PION) {
        if (!bicie_w_przelocie.empty()) {
            if (bicie_w_przelocie[0]==cel) {
                if (P[start.x()][start.y()].kolor()) {
                    P[cel.x()][cel.y()+1].clear();
                }
                else {
                    P[cel.x()][cel.y()-1].clear();
                }
            }
        }
    }
    if (P[start.x()][start.y()].figtype() == KROL) {
        if (P[start.x()][start.y()].kolor()) {
            bking=cel;
        }
        else {
            wking=cel;
        }
        if ((cel.x()-start.x() == 2)) {
            P[start.x()+1][start.y()]=Figura(start.x()+1,start.y(),P[8][start.y()].figtype(),P[8][start.y()].kolor());
            P[8][start.y()].clear();
        }
        if ((start.x()-cel.x() == 2)) {
            P[start.x()-1][start.y()]=Figura(start.x()-1,start.y(),P[1][start.y()].figtype(),P[1][start.y()].kolor());
            P[1][start.y()].clear();
        }
    }
    bicie_w_przelocie.clear();
    if (P[start.x()][start.y()].figtype()==PION && ((start.y() - cel.y() == 2) || (cel.y() - start.y() == 2)))
        bicie_w_przelocie.push_back(Pole(cel.x(),(cel.y()+start.y())/2));
    P[cel.x()][cel.y()]=Figura(cel,P[start.x()][start.y()].figtype(),P[start.x()][start.y()].kolor());
    P[start.x()][start.y()].clear();
    if (P[cel.x()][cel.y()].figtype() == PION) {
        if (P[cel.x()][cel.y()].kolor()) {
            if (cel.y()==1)
                P[cel.x()][cel.y()].awansuj(HETMAN/*typ_awans()*/); //na stałe dla CPU
        }
        else {
            if (cel.y()==8)
                P[cel.x()][cel.y()].awansuj(typ_awans());
        }
    }
}

void Rozgrywka::baza_fig() {
    Czarne.clear();
    Biale.clear();
    for (int i=1;i<=8;i++) {
        for (int j=1;j<=8;j++) {
            if (P[i][j].figtype() !=0) {
                if (P[i][j].kolor()) {
                    Czarne.push_back(Figura(i,j,P[i][j].figtype(),BLACK));
                }
                else {
                    Biale.push_back(Figura(i,j,P[i][j].figtype(),WHITE));
                }
            }
        }
    }
}

char Rozgrywka::typ_awans() const {
    return awans_typ;
}

char Rozgrywka::zmien_awanstyp(char nowy) {
    assert(nowy<6 || nowy>1);
    if (nowy>5 || nowy<2)
        return -1;
    awans_typ = nowy;
    return nowy;
}

void Rozgrywka::addlog(Pole start, Pole cel) {
    logtmp=64+start.x();
    logtmp+=48+start.x();
    logtmp+="-";
    logtmp+=64+cel.x();
    logtmp+=48+cel.y();
    logtmp+="\n";
    log+=logtmp;
}

void Rozgrywka::addlog(std::string napis) {
    logtmp+=napis;
    log+=napis;
}

int gwaga[7]={0,10,50,30,30,90,10000};

int Rozgrywka::ocen() { //czarne +/białe -
    int wynik=0;
    char wruch=0;
    char bruch=0;
    for (int i=1;i<9;i++) {
        for (int j=1;j<9;j++) {
            if (P[i][j].kolor()) {
                wynik+=gwaga[P[i][j].figtype()];
            }
            else {
                wynik-=gwaga[P[i][j].figtype()];
            }
        }
    }
    baza_fig();
    for (unsigned int i=0;i<Czarne.size();i++) {
        bruch=ruchy(Czarne[i]).size();
        wynik+=bruch;
        if (Czarne[i].figtype() == PION) {
            Pole tp(Czarne[i].p());
            if (tp.x()+1<9)
                if (P[tp.x()+1][tp.y()-1].figtype() && P[tp.x()+1][tp.y()-1].kolor())
                    wynik+=3;
        }
        if (Czarne[i].figtype() == PION) {
            Pole tp(Czarne[i].p());
            if (tp.x()-1>0)
                if (P[tp.x()-1][tp.y()-1].figtype() && P[tp.x()+1][tp.y()-1].kolor())
                    wynik+=3;
        }
    }
    for (unsigned int i=0;i<Biale.size();i++) {
        wruch=ruchy(Biale[i]).size();
        wynik+=wruch;
        if (Biale[i].figtype() == PION) {
            Pole tp(Biale[i].p());
            if (tp.x()+1<9)
                if (P[tp.x()+1][tp.y()+1].figtype() && !(P[tp.x()+1][tp.y()+1].kolor()))
                    wynik-=3;
        }
        if (Biale[i].figtype() == PION) {
            Pole tp(Biale[i].p());
            if (tp.x()-1>0)
                if (P[tp.x()-1][tp.y()+1].figtype() && !(P[tp.x()+1][tp.y()+1].kolor()))
                    wynik-=3;
        }
    }
    if (szach(wking)) {
        if (wruch>0) {
        wynik+=SZACH;
        }
        else {
        wynik=MAT;
        ocena=wynik;
        return wynik;
        }
    }
    if (szach(bking)) {
        if (bruch>0) {
        wynik-=SZACH;
        }
        else {
        wynik=-MAT;
        ocena=wynik;
        return wynik;
        }
    }
    ocena = wynik;
    return wynik;
}

bool wieksze(Rozgrywka i, Rozgrywka j) {
    if (i.ocena > j.ocena)
        return true;
    else
        return false;
}

bool mniejsze(Rozgrywka i, Rozgrywka j) {
    if (i.ocena < j.ocena)
        return true;
    else
        return false;
}

void Rozgrywka::bulid_one() {
    Czarne.clear();
    Biale.clear();
    wsk.clear();
    baza_fig();
    int k=-1;
    if (next) {
        //mozliwe = new std::vector<Pole>[Czarne.size()];
        mozliwe.resize(Czarne.size());
        for (unsigned int i=0;i<Czarne.size();i++) {
            mozliwe[i]=ruchy_tr(Czarne[i]);
            for (unsigned int j=0;j<mozliwe[i].size();j++) {
                //wsk.push_back(Rozgrywka(*this,Czarne[i].p(),mozliwe[i][j]));
                wsk[++k].ocen();
            }
        }
    }
    else {
        //mozliwe = new std::vector<Pole>[Biale.size()];
        mozliwe.resize(Biale.size());
        for (unsigned int i=0;i<Biale.size();i++) {
            mozliwe[i]=ruchy_tr(Biale[i]);
            for (unsigned int j=0;j<mozliwe[i].size();j++) {
                //wsk.push_back(Rozgrywka(*this,Biale[i].p(),mozliwe[i][j]));
                wsk[++k].ocen();
            }
        }
    }
}

void Rozgrywka::bulid_tree() {
    if (wsk.empty()) {
        Czarne.clear();
        Biale.clear();
        int k=-1;
        if (rekursja>0) {
            baza_fig();
            if (next) {
                //mozliwe = new std::vector<Pole>[Czarne.size()];
                mozliwe.resize(Czarne.size());
                for (unsigned int i=0;i<Czarne.size();i++) {
                    mozliwe[i]=ruchy_tr(Czarne[i]);
                    for (unsigned int j=0;j<mozliwe[i].size();j++) {
                        //wsk.push_back(Rozgrywka(*this,Czarne[i].p(),mozliwe[i][j]));
                        wsk[++k].ocen();
                    }
                }
            }
            else {
                //mozliwe = new std::vector<Pole>[Biale.size()];
                mozliwe.resize(Biale.size());
                for (unsigned int i=0;i<Biale.size();i++) {
                    mozliwe[i]=ruchy_tr(Biale[i]);
                    for (unsigned int j=0;j<mozliwe[i].size();j++) {
                        //wsk.push_back(Rozgrywka(*this,Biale[i].p(),mozliwe[i][j]));
                        wsk[++k].ocen();
                    }
                }
            }
        }
    }
/*    if (rekursja%2) {
    std::sort(wsk.begin(),wsk.end(),wieksze);
    }
    else {
    std::sort(wsk.begin(),wsk.end(),mniejsze);
    }*/
    for (unsigned int i=0;i<wsk.size()/*/CIECIA*/;i++)
        wsk[i].bulid_tree();
}

void Rozgrywka::rebulid_tree() {
    Czarne.clear();
    Biale.clear();
    wsk.clear();
    int k=-1;
    if (rekursja>0) {
        baza_fig();
        if (next) {
            //mozliwe = new std::vector<Pole>[Czarne.size()];
            mozliwe.resize(Czarne.size());
            for (unsigned int i=0;i<Czarne.size();i++) {
                mozliwe[i]=ruchy_tr(Czarne[i]);
                for (unsigned int j=0;j<mozliwe[i].size();j++) {
                    //wsk.push_back(Rozgrywka(*this,Czarne[i].p(),mozliwe[i][j]));
                    wsk[++k].ocen();
                }
            }
        }
        else {
            //mozliwe = new std::vector<Pole>[Biale.size()];
            mozliwe.resize(Biale.size());
            for (unsigned int i=0;i<Biale.size();i++) {
                mozliwe[i]=ruchy_tr(Biale[i]);
                for (unsigned int j=0;j<mozliwe[i].size();j++) {
                    //wsk.push_back(Rozgrywka(*this,Biale[i].p(),mozliwe[i][j]));
                    wsk[++k].ocen();
                }
            }
        }
    }
/*    if (rekursja%2) {
    std::sort(wsk.begin(),wsk.end(),wieksze);
    }
    else {
    std::sort(wsk.begin(),wsk.end(),mniejsze);
    }*/
    for (unsigned int i=0;i<wsk.size()/*/CIECIA*/;i++)
        wsk[i].bulid_tree();
}

void Rozgrywka::minmax() {
    if (rekursja > 0) {
        for (unsigned int i=0;i<wsk.size()/*/CIECIA*/;i++) {
            wsk[i].minmax();
        }
        if (rekursja%2) {
            wyb=&(*std::max_element(wsk.begin(),wsk.begin()+wsk.size()/*/CIECIA*/,mniejsze));
            if (!wsk.empty())
            ocena=wyb->ocena;
        }
        else {
            wyb=&(*std::min_element(wsk.begin(),wsk.begin()+wsk.size()/*/CIECIA*/,mniejsze));
            if (!wsk.empty())
            ocena=wyb->ocena;
        }
    }
}

bool Rozgrywka::szach(Pole spr) {
    baza_fig();
    if (P[spr.x()][spr.y()].kolor()) {
        //mozliwe = new std::vector<Pole>[Biale.size()];
        mozliwe.resize(Biale.size());
        for (unsigned int i=0;i<Biale.size();i++) {
            mozliwe[i]=ruchybs(Biale[i]);
            for (unsigned int j=0;j<mozliwe[i].size();j++) {
                if (spr == mozliwe[i][j])
                    return 1;
            }
        }
    }
    else {
        //mozliwe = new std::vector<Pole>[Czarne.size()];
        mozliwe.resize(Czarne.size());
        for (unsigned int i=0;i<Czarne.size();i++) {
            mozliwe[i]=ruchybs(Czarne[i]);
            for (unsigned int j=0;j<mozliwe[i].size();j++) {
                if (spr == mozliwe[i][j])
                    return 1;
            }
        }
    }
    return 0;
}

Rozgrywka::~Rozgrywka() {
    wsk.clear();
    Biale.clear();
    Czarne.clear();
    bicie_w_przelocie.clear();
    mozliwe.clear();
}

int wmin(int a, int b) {
    if (a<b)
        return a;
    return b;
}

int wmax(int a, int b) {
    if (a<b)
        return b;
    return a;
}

