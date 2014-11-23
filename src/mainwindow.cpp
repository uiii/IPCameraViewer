#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_about.h"

#include <iostream>

#include <QDebug>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>

#include <qjson/parser.h>
#include <qjson/serializer.h>

#include "QtAwesome.h"

#include "view.h"
#include "screen.h"
#include "videoplayer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    aboutUi(new Ui::About),
    about(new QDialog(this)),
    lastMaxScreenIndex(0)
{
    ui->setupUi(this);
    aboutUi->setupUi(about);

    awesome = new QtAwesome(this);
    awesome->initFontAwesome();
    /*awesome->setDefaultOption("color", QColor(0,0,0));
    awesome->setDefaultOption("color-disabled", QColor(127,127,127));
    awesome->setDefaultOption("color-active", QColor(255,255,255));
    awesome->setDefaultOption("color-selected", QColor(255,255,255));*/

    /*ui->actionAddScreen->setIcon(awesome->icon(fa::th));
    ui->actionAddView->setIcon(awesome->icon(fa::videocamera));
    ui->actionFullscreen->setIcon(awesome->icon(fa::arrowsalt));*/

    this->addScreen();

    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->actionAddScreen, SIGNAL(triggered()), this, SLOT(addScreen()));
    connect(ui->actionAddView, SIGNAL(triggered()), this, SLOT(addView()));
    connect(ui->actionRenameScreen, SIGNAL(triggered()), this, SLOT(renameScreen()));
    connect(ui->actionFullscreen, SIGNAL(triggered()), this, SLOT(toggleFullscreen()));
    connect(ui->actionAbout, SIGNAL(triggered()), about, SLOT(show()));

    connect(ui->screens, SIGNAL(tabCloseRequested(int)), this, SLOT(removeScreen(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

Screen* MainWindow::addScreen(QString title)
{
    ++lastMaxScreenIndex;

    if (title.isEmpty()) {
        title = QString("Screen %1").arg(lastMaxScreenIndex);
    }

    Screen* screen = new Screen;
    int index = ui->screens->addTab(screen, awesome->icon(fa::th), title);
    ui->screens->setCurrentIndex(index);

    updateTabBar();

    return screen;
}

void MainWindow::removeScreen(int index)
{
    // TODO ask if not empty

    ui->screens->removeTab(index);

    updateTabBar();
}

void MainWindow::renameScreen(int index)
{
    QString text = QInputDialog::getText(this, tr("Rename screen"), tr("New screen title"));

    if (text != NULL) {
        if (index == -1) {
            index = ui->screens->currentIndex();
        }

        ui->screens->setTabText(index, text);
    }
}

void MainWindow::addView()
{
    Screen* currentScreen = (Screen*) ui->screens->currentWidget();
    currentScreen->addView();
}

void MainWindow::toggleFullscreen()
{
    if (isFullScreen()) {
        showNormal();
        //menuWidget()->show();
    }
    else {
        showFullScreen();
        //menuWidget()->hide();
    }
}

void MainWindow::save(QString filename)
{
    if (filename.isEmpty()) {
        filename = QFileDialog::getSaveFileName(this, "Save screens", "save.json", "JSON (*.json)");
    }

    if (! filename.isEmpty()) {
        // create JSON object
        QVariantList screensJson;
        for(int i = 0; i < ui->screens->count(); ++i) {
            Screen* screen = (Screen*) ui->screens->widget(i);

            QVariantList viewsJson;
            for(View* view : screen->getViews()) {
                QVariantMap viewJson;
                viewJson.insert("title", view->getTitle());
                viewJson.insert("uri", view->getPlayer()->getUri());

                viewsJson.append(viewJson);
            }

            QVariantMap screenJson;
            screenJson.insert("title", ui->screens->tabText(i));
            screenJson.insert("views", viewsJson);
            screensJson.append(screenJson);
        }

        QVariantMap json;
        json.insert("screens", screensJson);

        // save JSON document
        QJson::Serializer serializer;
        serializer.setIndentMode(QJson::IndentFull);

        bool ok;
        QByteArray data = serializer.serialize(json, &ok);

        if (! ok) {
            QMessageBox::critical(this, "Save failure", "Save failed.");
            return;
        }

        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "Save failure", QString("Couldn't open file '%1'.").arg(filename));
            return;
        }

        file.write(data);
    }
}

void MainWindow::load(QString filename)
{
    if (filename.isEmpty()) {
        filename = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), "JSON (*.json)");
    }

    if (! filename.isEmpty()) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, "Load failure", QString("Couldn't open file '%1'.").arg(filename));
            return;
        }

        QByteArray data = file.readAll();

        QJson::Parser parser;

        bool ok;
        QVariantMap json = parser.parse(data, &ok).toMap();

        if (! ok) {
            QMessageBox::critical(this, "Load failure", QString("File '%1' isn't valid save file.").arg(filename));
            return;
        }

        while(ui->screens->count() > 0) {
            removeScreen(0);
        }

        for(QVariant item : json["screens"].toList()) {
            QVariantMap screenJson = item.toMap();

            Screen* screen = addScreen(screenJson["title"].toString());
            screen->removeView(screen->getViews()[0]);

            for(QVariant item : screenJson["views"].toList()) {
                QVariantMap viewJson = item.toMap();

                View* view = screen->addView(viewJson["title"].toString());
                view->getPlayer()->setUri(viewJson["uri"].toString());
                view->getPlayer()->play();
            }
        }
    }
}

void MainWindow::updateTabBar()
{
    //ui->screens->tabBar()->setVisible(ui->screens->count() > 1);
}
