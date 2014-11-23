/*
 * This file is part of IPCameraViewer project (https://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file (https://raw.githubusercontent.com/uiii/IPCameraViewer/master/LICENSE) for details.
 */

#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QString>

class QWidget;

class VideoPlayer
{
public:
    explicit VideoPlayer();
    virtual ~VideoPlayer();

    QString getUri();

    void setUri(QString uri);
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void setWidget(QWidget* widget) = 0;

private:
    QString uri;
};

#endif // VIDEOPLAYER_H
