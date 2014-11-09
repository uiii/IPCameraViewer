#ifndef QMEDIAPLAYERVIEW_H
#define QMEDIAPLAYERVIEW_H

#include <QWidget>
#include <QString>

namespace Ui {
    class View;
}

class ViewSettings;

class QMediaPlayer;

class QtAwesome;

class QMediaPlayerView : public QWidget
{
    Q_OBJECT

    friend class ViewSettings;

public:
    explicit QMediaPlayerView(QString title, QString uri = QString(), QWidget* parent = 0);
    ~QMediaPlayerView();

public slots:
    void openSettings();
    void play();

private:
    Ui::View* ui;

    QString uri;

    QMediaPlayer* player;

    QtAwesome* awesome;
};

#endif // QMEDIAPLAYERVIEW_H
