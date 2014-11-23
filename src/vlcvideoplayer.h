/*
 * This file is part of IPCameraViewer project (https://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file (https://github.com/uiii/IPCameraViewer/LICENSE) for details.
 */

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
