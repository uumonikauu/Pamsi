#include <QApplication>
#include "mainwindow.h"
/*!
* 
* \brief Zawiera glowna funkcje programu.
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.display();
    
    return a.exec();
}
