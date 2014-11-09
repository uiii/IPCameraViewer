#ifndef VIEWSETTINGS_H
#define VIEWSETTINGS_H

#include <QDialog>

namespace Ui {
    class ViewSettings;
}

class View;

class ViewSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ViewSettings(View* view);
    ~ViewSettings();

public slots:
    void open();

private:
    Ui::ViewSettings *ui;
    View* view;

private slots:
    void apply();
};

#endif // VIEWSETTINGS_H
