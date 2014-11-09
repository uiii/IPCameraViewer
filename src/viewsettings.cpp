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
