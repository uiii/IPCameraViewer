/*
 * This file is part of IPCameraViewer project (http://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file (http://github.com/uiii/IPCameraViewer/LICENSE) for details.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QList>

namespace Ui {
    class Screen;
}

class View;
class QGridLayout;

class Screen : public QWidget
{
    Q_OBJECT

public:
    explicit Screen(QWidget *parent = 0);
    ~Screen();

    const QList<View*>& getViews() const;
    View* getZoomedView() const;

public slots:
    View* addView(QString title = QString());

    void zoomView(View* view = 0);

    void moveUp(View* view = 0);
    void moveDown(View* view = 0);
    void moveLeft(View* view = 0);
    void moveRight(View* view = 0);

    void removeView(View* view = 0);

private:
    void moveView(int from, int to);
    void updateLayout();

    Ui::Screen *ui;

    QList<View*> views;
    QGridLayout* grid;

    View* zoomedView;

    int columnsCount;
    int lastMaxViewIndex;
};

#endif // SCREEN_H
