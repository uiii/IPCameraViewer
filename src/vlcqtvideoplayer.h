#ifndef VLCQTVIDEOPLAYER_H
#define VLCQTVIDEOPLAYER_H

#include <QWidget>

#include "videoplayer.h"

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class VlcQtVideoPlayer : public VideoPlayer
{
public:
    explicit VlcQtVideoPlayer();
    ~VlcQtVideoPlayer();

    void play();
    void setWidget(QWidget* widget);

private:
    static VlcInstance* instance;
    VlcMedia* media;
    VlcMediaPlayer* player;
};

#endif // VLCQTVIDEOPLAYER_H
