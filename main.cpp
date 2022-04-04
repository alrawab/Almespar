#include "mainwindow.h"

#include <QApplication>
//#include <QPlastiqueStyle>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

   // QApplication::setStyle(new QPlastiqueStyle());
    w.show();
    w.move ((QApplication::desktop()->width() - w.width())/2,
    (QApplication::desktop()->height() - w.height())/2);
    return a.exec();
}
