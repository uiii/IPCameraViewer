#include "qmediaplayerview.h"
#include "ui_view.h"

#include <QMediaPlayer>
#include <QVideoWidget>

#include "QtAwesome.h"

#include "viewsettings.h"

QMediaPlayerView::QMediaPlayerView(QString title, QString uri, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::View),
    uri(uri)
{
    // setup UI
    ui->setupUi(this);

    ui->title->setText(title);

    awesome = new QtAwesome(this);
    awesome->initFontAwesome();
    awesome->setDefaultOption("color", QColor(255,255,255));
    awesome->setDefaultOption("color-disabled", QColor(127,127,127));
    awesome->setDefaultOption("color-active", QColor(255,255,255));
    awesome->setDefaultOption("color-selected", QColor(255,255,255));

    ui->playButton->setIcon(awesome->icon(fa::play));
    ui->settingsButton->setIcon(awesome->icon(fa::cog));
    ui->closeButton->setIcon(awesome->icon(fa::times));

    player = new QMediaPlayer();
    player->setVideoOutput(ui->video);

    play();

    connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(openSettings()));
}

QMediaPlayerView::~QMediaPlayerView()
{
    delete player;
    delete awesome;
    delete ui;
}

void QMediaPlayerView::openSettings()
{
    ViewSettings* settings = new ViewSettings(this);
    settings->open();
}

void QMediaPlayerView::play()
{
    if (uri.isEmpty()) {
        return;
    }

    player->setMedia(QUrl(uri));
    player->play();
}
