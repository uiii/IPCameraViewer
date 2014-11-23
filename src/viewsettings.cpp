/*
 * This file is part of IPCameraViewer project (https://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file (https://github.com/uiii/IPCameraViewer/LICENSE) for details.
 */

#include "viewsettings.h"
#include "ui_viewsettings.h"
#include "ui_view.h"

#include <QDebug>

#include "view.h"
#include "videoplayer.h"

ViewSettings::ViewSettings(View* view) :
    QDialog(view),
    ui(new Ui::ViewSettings),
    view(view)
{
    ui->setupUi(this);

    connect(this, SIGNAL(accepted()), this, SLOT(apply()));
}

ViewSettings::~ViewSettings()
{
    delete ui;
}

void ViewSettings::open()
{
    ui->titleEdit->setText(view->getTitle());
    ui->uriEdit->setText(view->getPlayer()->getUri());

    QDialog::open();
}

void ViewSettings::apply()
{
    view->setTitle(ui->titleEdit->text());

    view->getPlayer()->setUri(ui->uriEdit->text());
    view->getPlayer()->play();
}
