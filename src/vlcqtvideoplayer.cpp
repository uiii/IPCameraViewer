#include "vlcqtvideoplayer.h"

#include <QWidget>
#include <QVBoxLayout>

#include <vlc-qt/Common.h>
#include <vlc-qt/Instance.h>
#include <vlc-qt/Media.h>
#include <vlc-qt/MediaPlayer.h>
#include <vlc-qt/WidgetVideo.h>

VlcInstance* VlcQtVideoPlayer::instance = 0;

VlcQtVideoPlayer::VlcQtVideoPlayer() :
    VideoPlayer()
{
    /*VlcWidgetVideo* video = new VlcWidgetVideo;
    video->setStyleSheet("background-color: rgb(0,0,0);");
    video->setAttribute(Qt::WA_PaintOnScreen, false);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(video);
    setLayout(layout);*/

    // setup VLC
    if (! instance) {
        instance = new VlcInstance(VlcCommon::args());
    }

    player = new VlcMediaPlayer(instance);

    play();
}

VlcQtVideoPlayer::~VlcQtVideoPlayer()
{
    delete player;
    delete media;
    delete instance;
}

void VlcQtVideoPlayer::play()
{
    if (getUri().isEmpty()) {
        return;
    }

    media = new VlcMedia(getUri(), instance);
    player->open(media);
}

void VlcQtVideoPlayer::setWidget(QWidget* widget)
{
    VlcWidgetVideo* video = new VlcWidgetVideo;
    widget->layout()->addWidget(video);

    player->setVideoWidget(video);
}
