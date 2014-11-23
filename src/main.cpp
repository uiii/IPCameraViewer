/*
 * This file is part of IPCameraViewer project (https://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file (https://github.com/uiii/IPCameraViewer/LICENSE) for details.
 */

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
