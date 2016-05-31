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
 
 
#include "MenuBar.h"
#include <QApplication>
#include <QMessageBox>

MenuBar::MenuBar(QWidget* parent) : QMenuBar(parent)
{
    pFile = createFileMenu();
    pHelp = createHelpMenu();

    addMenu(pFile);
    addMenu(pHelp);
}


QMenu* MenuBar::createFileMenu()
{
    QMenu* menu = new QMenu(tr("&General"));

    QAction* pReport = menu->addAction(tr("&Generate report"));
    pReport->setShortcut(Qt::CTRL + Qt::Key_R);
    //connect(pReport, SIGNAL(triggered()), SLOT(slotGenerateReport()));

    menu->addAction(tr("&Quit"), qApp, SLOT(quit()), Qt::CTRL + Qt::Key_Q);

    return menu;
}

QMenu* MenuBar::createHelpMenu()
{
    QMenu* menu = new QMenu(tr("&Help"));

    QAction* pAbout = menu->addAction(tr("&About program"));
    connect(pAbout, SIGNAL(triggered()), SLOT(slotAboutProgram()));

    menu->addAction(tr("&About Qt"), qApp, SLOT(aboutQt()));

    return menu;
}


void MenuBar::slotAboutProgram()
{
    QMessageBox::about(this, tr("About program"), tr("Author : Zaitsev Alexander\nTranslator : Zaitsev Alexander\n"
                                                     "Icon designer : Romanovskiy Roman"));
}

