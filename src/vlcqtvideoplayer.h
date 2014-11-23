/*
 * This file is part of IPCameraViewer project (http://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file (http://github.com/uiii/IPCameraViewer/LICENSE) for details.
 */

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
