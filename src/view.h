#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QString>

namespace Ui {
    class View;
    class ViewOverlay;
}

class Screen;
class ViewSettings;
class VideoPlayer;
class QtAwesome;

class View : public QWidget
{
    Q_OBJECT

public:
    explicit View(VideoPlayer* player, Screen* screen = 0);
    ~View();

    QString getTitle();
    VideoPlayer* getPlayer();

    bool isZoomed();

signals:
    void zoomed();
    void removed();
    void movedUp();
    void movedDown();
    void movedLeft();
    void movedRight();

public slots:
    void setTitle(QString title);
    void openSettings();
    void setZoomed(bool flag);
    void setMovable(bool flag);
    void setExpandable(bool flag);
    void setRemoveable(bool flag);

protected:
    void mouseDoubleClickEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void showEvent(QShowEvent *);

protected slots:
    void updateOverlay();

private:
    Ui::View* ui;
    Ui::ViewOverlay* overlayUi;

    Screen* screen;

    VideoPlayer* player;
    QWidget* overlay;

    bool isMovable;

    QtAwesome* awesome;
};

#endif // VIEW_H
