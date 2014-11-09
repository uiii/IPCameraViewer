#include "view.h"
#include "ui_view.h"
#include "ui_viewoverlay.h"

#include <QDebug>
#include <QRect>

#include "QtAwesome.h"

#include "screen.h"
#include "videoplayer.h"
#include "viewsettings.h"

View::View(VideoPlayer* player, Screen* screen) :
    QWidget(screen),
    ui(new Ui::View),
    overlayUi(new Ui::ViewOverlay),
    screen(screen),
    player(player),
    overlay(new QWidget),
    isMovable(false),
    awesome(0)
{
    // setup UI
    ui->setupUi(this);
    overlayUi->setupUi(overlay);

    overlay->setParent(this);

    ui->zoomedLabel->hide();

    QVBoxLayout* layout = new QVBoxLayout;
    ui->video->setLayout(layout);

    player->setWidget(ui->video);

    awesome = new QtAwesome(this);
    awesome->initFontAwesome();
    awesome->setDefaultOption("color", QColor(255,255,255));
    awesome->setDefaultOption("color-disabled", QColor(127,127,127));
    awesome->setDefaultOption("color-active", QColor(255,255,255));
    awesome->setDefaultOption("color-selected", QColor(255,255,255));

    ui->moveButton->setIcon(awesome->icon(fa::arrows));
    ui->settingsButton->setIcon(awesome->icon(fa::cog));
    ui->zoomButton->setIcon(awesome->icon(fa::expand));
    ui->removeButton->setIcon(awesome->icon(fa::times));

    overlayUi->moveUpButton->setIcon(awesome->icon(fa::arrowcircleup));
    overlayUi->moveDownButton->setIcon(awesome->icon(fa::arrowcircledown));
    overlayUi->moveLeftButton->setIcon(awesome->icon(fa::arrowcircleleft));
    overlayUi->moveRightButton->setIcon(awesome->icon(fa::arrowcircleright));

    connect(ui->moveButton, SIGNAL(toggled(bool)), this, SLOT(setMovable(bool)));
    connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(openSettings()));

    connect(overlayUi->settingsButton, SIGNAL(clicked()), this, SLOT(openSettings()));

    connect(ui->zoomButton, SIGNAL(toggled(bool)), this, SLOT(setZoomed(bool)));
    connect(ui->removeButton, SIGNAL(clicked()), this, SIGNAL(removed()));
    connect(overlayUi->moveUpButton, SIGNAL(clicked()), this, SIGNAL(movedUp()));
    connect(overlayUi->moveDownButton, SIGNAL(clicked()), this, SIGNAL(movedDown()));
    connect(overlayUi->moveLeftButton, SIGNAL(clicked()), this, SIGNAL(movedLeft()));
    connect(overlayUi->moveRightButton, SIGNAL(clicked()), this, SIGNAL(movedRight()));

}

View::~View()
{
    delete player;
    delete overlay;
    delete ui;
    delete overlayUi;
    delete awesome;
}

QString View::getTitle()
{
    return ui->title->text();
}

VideoPlayer*View::getPlayer()
{
    return player;
}

void View::setTitle(QString title)
{
    ui->title->setText(title);
}

void View::openSettings()
{
    ViewSettings* settings = new ViewSettings(this);
    settings->open();

    connect(settings, SIGNAL(accepted()), this, SLOT(updateOverlay()));
}

void View::setZoomed(bool flag)
{
    qDebug() << "zoomed";
    qDebug() << flag;
    ui->zoomButton->setIcon(awesome->icon(flag ? fa::compress : fa::expand));
    ui->removeButton->setHidden(flag);
    ui->moveButton->setHidden(flag);
    ui->zoomedLabel->setVisible(flag);

    screen->zoomView(flag ? this : 0);
}

void View::setMovable(bool flag)
{
    isMovable = flag;
    updateOverlay();
}

void View::setExpandable(bool flag)
{
    ui->zoomButton->setEnabled(flag);
}

void View::setRemoveable(bool flag)
{
    ui->removeButton->setEnabled(flag);
}

void View::resizeEvent(QResizeEvent*)
{
    updateOverlay();
}

void View::showEvent(QShowEvent*)
{
    updateOverlay();
}

void View::updateOverlay()
{
    bool showOverlay = false;

    if (player->getUri().isEmpty()) {
        overlayUi->pages->setCurrentWidget(overlayUi->noUriPage);
        showOverlay = true;
    }

    if (isMovable) {
        overlayUi->pages->setCurrentWidget(overlayUi->movePage);
        showOverlay = true;

    }

    if (showOverlay) {
        QRect rect = ui->video->geometry();
        qDebug() << rect;
        overlay->move(rect.topLeft());
        overlay->setFixedSize(rect.size());
        overlay->setVisible(true);
    } else {
        qDebug() << "set hidden";
        overlay->setHidden(true);
    }
}
