/*
 * This file is part of IPCameraViewer project (https://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */

#include "videoplayer.h"

VideoPlayer::VideoPlayer()
{
}

VideoPlayer::~VideoPlayer()
{
}

QString VideoPlayer::getUri()
{
    return uri;
}

void VideoPlayer::setUri(QString uri)
{
    this->uri = uri;
    stop();
}
