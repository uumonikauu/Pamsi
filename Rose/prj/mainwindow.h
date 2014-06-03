#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QApplication>
#include <QTextBrowser>
#include "Szachy.h"
#include <string>

namespace Ui {
/*!
\brief Definicja klasy MainWindow 
*/
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void display();
/*!
\brief Prototyp funkcji odpowiedzialny za wyglad szachownicy 
*/
    void szachownica();
    void szachownica(std::vector<Pole> light);
    
private slots:
    void qruch();
    void tawans();
    void displog();

private:
    bool end;
    static const int pole_wymiar=80;
    std::vector<Pole> qmozliwe;
    Pole start;
    Pole cel;
    Ui::MainWindow *ui;
    QPushButton ***pole;
    QPushButton *awans;
    QTextBrowser *log;
    Rozgrywka R;
};

#endif // MAINWINDOW_H
