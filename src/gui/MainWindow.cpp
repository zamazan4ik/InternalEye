#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    pvbx = new QVBoxLayout;
    genButtons = new QHBoxLayout;
    pMenuBar = new MenuBar;

    refresh = new QPushButton(tr("Refresh"));

    genButtons->addWidget(refresh);
    pvbx->addWidget(pMenuBar);
    pvbx->addLayout(genButtons);
    setLayout(pvbx);

    setWindowTitle("Internal Eye");
    setWindowIcon(QIcon(":/images/MainIcon"));

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
    sett.setValue("/geometry", geometry());
    sett.endGroup();
}

void MainWindow::readSettings()
{
    QSettings sett;
    sett.beginGroup("Settings");
    setGeometry(sett.value("/geometry", QRect()).toRect());
    sett.endGroup();
}

