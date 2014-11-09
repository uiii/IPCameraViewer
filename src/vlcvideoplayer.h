#ifndef VLCVIDEOPLAYER_H
#define VLCVIDEOPLAYER_H

#include "videoplayer.h"

class VlcInstance;

class libvlc_media_player_t;

class QWidget;

class VlcVideoPlayer : public VideoPlayer
{
public:
    explicit VlcVideoPlayer();
    ~VlcVideoPlayer();

    void play();
    void setWidget(QWidget* widget);

protected:
    void stop();

private:
    static VlcInstance instance;
    libvlc_media_player_t* player;

    QWidget* videoWidget;
};

#endif // VLCVIDEOPLAYER_H
