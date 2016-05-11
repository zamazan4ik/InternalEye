/***************************************************************************
 *   Copyright (C) 2016 by Zaitsev Alexander                               *
 *   zamazan4ik@tut.by	                                                   *
 *                                                                         *
 *   This file is part of InternalEye.                                     *
 *                                                                         *
 *   InternalEye is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   InternalEye is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with InternalEye.  If not, see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/
 
 
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

