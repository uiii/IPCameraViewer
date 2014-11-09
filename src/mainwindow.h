#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
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
    void renameScreen(int index);

    void addView();

    void toggleFullscreen();

    void save();
    void load();

private:
    void updateTabBar();

    Ui::MainWindow *ui;

    QtAwesome* awesome;

    int lastMaxScreenIndex;
};

#endif // MAINWINDOW_H
