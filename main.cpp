#include "mainwindow.h"
#include "tlist.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tList w;
    w.show();
    return a.exec();
}
