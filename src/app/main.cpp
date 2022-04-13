//
// Created by Angelo DeLuca on 4/5/22.
//

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gwd::MainWindow w;
    w.show();
    return a.exec();
}
