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
                                                     "Graphic designer : Romanovskiy Roman"));
}

