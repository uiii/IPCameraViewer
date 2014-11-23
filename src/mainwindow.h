/*
 * This file is part of IPCameraViewer project (https://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file (https://raw.githubusercontent.com/uiii/IPCameraViewer/master/LICENSE) for details.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
    class About;
}

class QtAwesome;
class Screen;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    Screen* addScreen(QString title = QString());
    void removeScreen(int index);
    void renameScreen(int index = -1);

    void addView();

    void toggleFullscreen();

    void save(QString filename = QString());
    void load(QString filename = QString());

private:
    void updateTabBar();

    Ui::MainWindow* ui;
    Ui::About* aboutUi;

    QDialog* about;

    QtAwesome* awesome;

    int lastMaxScreenIndex;
};

#endif // MAINWINDOW_H
