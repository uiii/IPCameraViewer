#include "screen.h"
#include "ui_screen.h"

#include <cmath>

#include <QDebug>
#include <QGridLayout>

#include "view.h"
#include "vlcvideoplayer.h"
#include "vlcqtvideoplayer.h"

Screen::Screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Screen),
    grid(0),
    zoomedView(0),
    columnsCount(0),
    lastMaxViewIndex(0)
{
    ui->setupUi(this);

    addView();
}

Screen::~Screen()
{
    qDebug() << "destruct screen";

    delete grid;

    for (View* view : views) {
        delete view;
    }

    delete ui;
}

const QList<View*>& Screen::getViews() const
{
    return views;
}

View* Screen::addView(QString title)
{
    ++lastMaxViewIndex;

    if (title.isEmpty()) {
        title = QString("View %1").arg(lastMaxViewIndex);
    }

    View* view = new View(new VlcVideoPlayer(), this);
    view->setTitle(title);
    views.append(view);

    connect(view, SIGNAL(removed()), this, SLOT(removeView()));
    connect(view, SIGNAL(movedUp()), this, SLOT(moveUp()));
    connect(view, SIGNAL(movedDown()), this, SLOT(moveDown()));
    connect(view, SIGNAL(movedLeft()), this, SLOT(moveLeft()));
    connect(view, SIGNAL(movedRight()), this, SLOT(moveRight()));

    updateLayout();

    return view;
}

void Screen::zoomView(View* view)
{
    qDebug() << "zoom";
    zoomedView = view;

    updateLayout();
}

void Screen::moveUp(View* view)
{
    if (! view) {
        view = (View*) sender();
    }

    int index = views.indexOf(view);
    moveView(index, index - columnsCount);
}

void Screen::moveDown(View* view)
{
    if (! view) {
        view = (View*) sender();
    }

    int index = views.indexOf(view);
    moveView(index, index + columnsCount);
}

void Screen::moveLeft(View* view)
{
    if (! view) {
        view = (View*) sender();
    }

    int index = views.indexOf(view);
    qDebug() << index;
    moveView(index, index - 1);
}

void Screen::moveRight(View* view)
{
    if (! view) {
        view = (View*) sender();
    }

    int index = views.indexOf(view);
    moveView(index, index + 1);
}

void Screen::removeView(View* view)
{
    if (! view) {
        view = (View*) sender();
    }

    grid->removeWidget(view);
    views.removeAt(views.indexOf(view));
    delete view;

    updateLayout();
}

void Screen::moveView(int from, int to)
{
    bool validFrom = 0 <= from && from < views.size();
    bool validTo = 0 <= to && to < views.size();

    if (validFrom && validTo) {
        views.move(from, to);
        grid->invalidate();
        updateLayout();
    }
}

void Screen::updateLayout()
{
    qDebug() << "update";
    // clear layout
    delete grid;
    grid = new QGridLayout;
    grid->setContentsMargins(0,0,0,0);
    grid->setSpacing(1);

    columnsCount = ceil(sqrt(views.count()));

    if (zoomedView) {
        grid->addWidget(zoomedView, 0, 0);

        for (View* view : views) {
            view->setHidden(view != zoomedView);
        }
    } else {
        int count = views.count();

        for(int i = 0; i < count; ++i) {
            views[i]->show();
            views[i]->setExpandable(count > 1);
            views[i]->setRemoveable(count > 1);
            grid->addWidget(views[i], i / columnsCount, i % columnsCount);
        }
    }

    setLayout(grid);
}
