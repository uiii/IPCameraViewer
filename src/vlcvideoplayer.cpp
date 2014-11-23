/*
 * This file is part of IPCameraViewer project (https://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */

#include "vlcvideoplayer.h"

#include <vlc/vlc.h>

#include <QWidget>
#include <QMessageBox>

#include "vlcinstance.h"

VlcInstance VlcVideoPlayer::instance = VlcInstance();

VlcVideoPlayer::VlcVideoPlayer() :
    VideoPlayer(),
    player(0)
{
}

VlcVideoPlayer::~VlcVideoPlayer()
{
    stop();
}

void VlcVideoPlayer::play()
{
    if (getUri().isEmpty()) {
        return;
    }

    /* Stop if something is playing */
    if (player && libvlc_media_player_is_playing(player))
        stop();

    /* Create a new Media */
    libvlc_media_t* media = libvlc_media_new_location(instance, getUri().toUtf8().constData());

    if (! media) {
        return;
    }

    /* Create a new libvlc player */
    player = libvlc_media_player_new_from_media(media);

    /* Release the media */
    libvlc_media_release(media);

    /* Integrate the video in the interface */
#if defined(Q_OS_MAC)
    libvlc_media_player_set_nsobject(player, (void *)videoWidget->winId());
#elif defined(Q_OS_UNIX)
    libvlc_media_player_set_xwindow(player, videoWidget->winId());
#elif defined(Q_OS_WIN)
    libvlc_media_player_set_hwnd(player, videoWidget->winId());
#endif

    /* And start playback */
    libvlc_media_player_play (player);
}

void VlcVideoPlayer::setWidget(QWidget* widget)
{
    videoWidget = widget;
}

void VlcVideoPlayer::stop()
{
    if(player) {
        /* stop the media player */
        libvlc_media_player_stop(player);

        /* release the media player */
        libvlc_media_player_release(player);

        player = 0;
    }
}
