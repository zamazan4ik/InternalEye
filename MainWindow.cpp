#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    pvbx = new QVBoxLayout(this);
    pMenuBar = new MenuBar(this);

    pvbx->addWidget(pMenuBar);
    setLayout(pvbx);
    setWindowTitle("Internal Eye");
    readSettings();
}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::writeSettings() const
{
    QSettings sett;
    sett.beginGroup("Settings");
    qDebug() << geometry();
    sett.setValue("/geometry", geometry());
    sett.endGroup();
}

void MainWindow::readSettings()
{
    QSettings sett;
    sett.beginGroup("Settings");
    qDebug() << sett.value("/geometry", QRect()).toRect();
    setGeometry(sett.value("/geometry", QRect()).toRect());
    sett.endGroup();
}
