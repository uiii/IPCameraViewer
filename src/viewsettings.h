/*
 * This file is part of IPCameraViewer project (https://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file (https://github.com/uiii/IPCameraViewer/LICENSE) for details.
 */

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
