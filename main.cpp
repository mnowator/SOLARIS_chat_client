#include "mainwindow.h"
#include <QApplication>
#include <QDialog>

//128.199.57.86:10000

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    return a.exec();
}
