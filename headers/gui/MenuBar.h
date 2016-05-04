#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include <QMenu>

class MenuBar : public QMenuBar
{
    Q_OBJECT
private:
    QMenu *pFile, *pHelp;
    QMenu* createFileMenu();
    QMenu* createHelpMenu();

private slots:
    void slotAboutProgram();

public:
    MenuBar(QWidget* parent = 0);
};

#endif // MENUBAR_H
