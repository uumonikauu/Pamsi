#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    end(0),
    start(0,0),
    cel(0,0),
   ui(new Ui::MainWindow)
{
    QString nazwa;
    ui->setupUi(this);
    this->setGeometry(0,0,1300,700);
    pole = new QPushButton**[8];
    for (int i=0;i<8;i++) {
        pole[i] = new QPushButton*[8];
        for (int j=0;j<8;j++) {
            pole[i][j] = new QPushButton(this);
            pole[i][j]->setGeometry(15+pole_wymiar*i,pole_wymiar*7+15-pole_wymiar*j,pole_wymiar,pole_wymiar);
            pole[i][j]->setIconSize(QSize(pole_wymiar,pole_wymiar));
            nazwa=(i+65);
            nazwa+=(j+49);
            pole[i][j]->setObjectName(nazwa);
            connect(pole[i][j],SIGNAL(clicked()),this,SLOT(qruch()));
        }
    }
    awans = new QPushButton(this);
    awans->setGeometry(100+8*pole_wymiar,15+4*pole_wymiar,pole_wymiar,pole_wymiar);
    awans->setIconSize((QSize(pole_wymiar,pole_wymiar)));
    connect(awans,SIGNAL(clicked()),this,SLOT(tawans()));
    log = new QTextBrowser(this);
    log->setGeometry(100+8*pole_wymiar,15,300,300);
    log->setStyleSheet("background-color: white; border: 3px solid grey");
    log->isReadOnly();
    szachownica();
    tawans();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*!
* 
* \brief Definicja funkcji reprezentująca wygląd szachownicy.
*/

void MainWindow::szachownica() {
    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++) {
            if ((i+j)%2) {
                pole[i][j]->setStyleSheet("background-color: white; border: none");
            }
            else {
                pole[i][j]->setStyleSheet("background-color: green; border: none");
            }
        }
    }
}
/*!
* 
* \brief Definicja funkcji reprezentująca wygląd szachownicy.
*/

void MainWindow::szachownica(std::vector<Pole> light) {
    for (unsigned int i=0;i<light.size();i++)
        if ((light[i].x()+light[i].y())%2)
            pole[light[i].x()-1][light[i].y()-1]->setStyleSheet("background-color: white; border: 4px solid lightblue");
        else
            pole[light[i].x()-1][light[i].y()-1]->setStyleSheet("background-color: green; border: 4px solid lightblue");
}
/*!
* 
* \brief Definicja funkcji reprezentująca wygląd figur.
*/
void MainWindow::tawans() {
    char i=R.typ_awans();
    i++;
    if (i==6)
        i=2;
    R.zmien_awanstyp(i);
    switch (i) {
    case 2: awans->setIcon(QIcon("Graphics/wwieza.svg"));break;
    case 3: awans->setIcon(QIcon("Graphics/wskoczek.svg"));break;
    case 4: awans->setIcon(QIcon("Graphics/wgoniec.svg"));break;
    case 5: awans->setIcon(QIcon("Graphics/whetman.svg"));break;
    default: assert("tu gdzies jest blad");break;
    }
}
/*!
* 
* \brief Definicja funkcji reprezentująca wykonywane ruchy przez figury.
*/
void MainWindow::qruch() {
    Pole tmp(sender()->objectName().toStdString());
    if (!end) {
        if (start == Pole(0,0)) {
            if (R.P[tmp.x()][tmp.y()].figtype()!=0) {
                if (R.P[tmp.x()][tmp.y()].kolor() == R.next) {
                    start = tmp;
                    qmozliwe = R.ruchy(R.P[tmp.x()][tmp.y()]);
                    szachownica(qmozliwe);
                }
            }
        }
        else {
            for (unsigned int i=0;i<qmozliwe.size();i++) {
                if (tmp == qmozliwe[i]) {
                    cel = tmp;
                    break;
                }
            }
            if (cel != Pole(0,0)) {
                R.ruch(start,cel);
                R.bulid_one();
                if (R.wsk.empty()) {
                    if (R.next) {
                        if(R.szach(R.bking)) {
                            R.addlog(start,cel);
                            R.addlog("biale mat");
                        }
                        else {
                            R.addlog(start,cel);
                            R.addlog("pat");
                        }
                    }
                    else {
                        if(R.szach(R.wking)) {
                            R.addlog(start,cel);
                            R.addlog("czarne mat");
                        }
                        else {
                            R.addlog(start,cel);
                            R.addlog("pat");
                        }
                    }
                    displog();
                    display();
                    start=Pole(0,0);
                    cel=Pole(0,0);
                    qmozliwe.clear();
                    szachownica();
                    return;
                }
                R.addlog(start,cel);
                displog();
                display();
                R.bulid_tree();
                R.minmax();
                Pole s=R.wyb->st;
                Pole c=R.wyb->cl;
                R.ruch(s,c);
                R.bulid_one();
                if (R.wsk.empty()) {
                    if (R.next) {
                        if(R.szach(R.bking)) {
                            R.addlog(start,cel);
                            R.addlog("biale mat");
                        }
                        else {
                            R.addlog(start,cel);
                            R.addlog("pat");
                        }
                    }
                    else {
                        if(R.szach(R.wking)) {
                            R.addlog(start,cel);
                            R.addlog("czarne mat");
                        }
                        else {
                            R.addlog(start,cel);
                            R.addlog("pat");
                        }
                    }
                    displog();
                    display();
                    start=Pole(0,0);
                    cel=Pole(0,0);
                    qmozliwe.clear();
                    szachownica();
                    return;
                }
                R.addlog(s,c);
                displog();
                display();
            }
            start=Pole(0,0);
            cel=Pole(0,0);
            qmozliwe.clear();
            szachownica();
            R.Biale.clear();
            R.Czarne.clear();
            R.wsk.clear();
        }
    }
}
/*!
* 
* \brief Definicja funkcji reprezentująca ustawienie figur na szachownicy.
*/
void MainWindow::display() {
    QString ikona;
    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++) {
            ikona = "Graphics/";
            if (R.P[i+1][j+1].figtype() == 0) {
                pole[i][j]->setIcon(QIcon());
                continue;
            };
            if (R.P[i+1][j+1].kolor())
                ikona += "b";
            else
                ikona += "w";
            switch (R.P[i+1][j+1].figtype()) {
                case 1: {
                ikona += "pion.svg";
                };break;
                case 2: {
                ikona += "wieza.svg";
                };break;
                case 3: {
                ikona += "skoczek.svg";
                };break;
                case 4: {
                ikona += "goniec.svg";
                };break;
                case 5: {
                ikona += "hetman.svg";
                };break;
                case 6: {
                ikona += "krol.svg";
                };break;
            }
            pole[i][j]->setIcon(QIcon(ikona));
        }
    }
}

void MainWindow::displog() {
    log->insertPlainText(QString::fromStdString(R.logtmp));
}
