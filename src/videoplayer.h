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
