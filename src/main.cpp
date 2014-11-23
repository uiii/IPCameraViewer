#include "mainwindow.h"
#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    QStringList arguments = a.arguments();
    if (arguments.size() > 1 && arguments[1][0] != '-') {
        w.load(arguments[1]);
    }

    return a.exec();
}
