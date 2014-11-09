#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QList>
#include <QJsonObject>

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
