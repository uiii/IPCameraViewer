#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QDebug>
#include <QInputDialog>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "QtAwesome.h"

#include "view.h"
#include "screen.h"
#include "videoplayer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    lastMaxScreenIndex(0)
{
    ui->setupUi(this);

    awesome = new QtAwesome(this);
    awesome->initFontAwesome();
    /*awesome->setDefaultOption("color", QColor(0,0,0));
    awesome->setDefaultOption("color-disabled", QColor(127,127,127));
    awesome->setDefaultOption("color-active", QColor(255,255,255));
    awesome->setDefaultOption("color-selected", QColor(255,255,255));*/

    ui->actionAddScreen->setIcon(awesome->icon(fa::th));
    ui->actionAddView->setIcon(awesome->icon(fa::videocamera));
    ui->actionFullscreen->setIcon(awesome->icon(fa::arrowsalt));

    this->addScreen();

    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->actionAddScreen, SIGNAL(triggered()), this, SLOT(addScreen()));
    connect(ui->actionAddView, SIGNAL(triggered()), this, SLOT(addView()));
    connect(ui->actionFullscreen, SIGNAL(triggered()), this, SLOT(toggleFullscreen()));

    connect(ui->screens, SIGNAL(tabCloseRequested(int)), this, SLOT(removeScreen(int)));
    connect(ui->screens, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(renameScreen(int)));
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

void MainWindow::save()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save screens", "save.json", "JSON (*.json)");

    if (! filename.isEmpty()) {
        // create JSON object
        QJsonArray screensJson;
        for(int i = 0; i < ui->screens->count(); ++i) {
        Screen* screen = (Screen*) ui->screens->widget(i);

        QJsonArray viewsJson;
        for(View* view : screen->getViews()) {
            QJsonObject viewJson;
            viewJson["title"] = view->getTitle();
            viewJson["uri"] = view->getPlayer()->getUri();

            viewsJson.append(viewJson);
        }

        QJsonObject screenJson;
        screenJson["title"] = ui->screens->tabText(i);
        screenJson["views"] = viewsJson;
        screensJson.append(screenJson);
        }

        QJsonObject json;
        json["screens"] = screensJson;

        // save JSON document
        QJsonDocument jsonDoc(json);

        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open save file.");
            return;
        }

        file.write(jsonDoc.toJson());

        qDebug() << json;
    }
}

void MainWindow::load()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), "JSON (*.json)");

    if (! filename.isEmpty()) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open save file.");
            return;
        }

        QByteArray data = file.readAll();

        QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
        QJsonObject json = jsonDoc.object();

        while(ui->screens->count() > 0) {
            removeScreen(0);
        }

        for(QJsonValueRef screenValueRef : json["screens"].toArray()) {
            QJsonObject screenJson = screenValueRef.toObject();

            Screen* screen = addScreen(screenJson["title"].toString());
            screen->removeView(screen->getViews()[0]);

            for(QJsonValueRef viewValueRef : screenJson["views"].toArray()) {
                QJsonObject viewJson = viewValueRef.toObject();

                View* view = screen->addView(viewJson["title"].toString());
                view->getPlayer()->setUri(viewJson["uri"].toString());
                view->getPlayer()->play();
            }
        }
    }
}

void MainWindow::updateTabBar()
{
    ui->screens->tabBar()->setVisible(ui->screens->count() > 1);
}
