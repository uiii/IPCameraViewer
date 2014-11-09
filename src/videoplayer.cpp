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
