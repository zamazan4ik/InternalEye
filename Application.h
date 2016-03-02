#ifndef APPLICATION_H
#define APPLICATION_H

#include "MainWindow.h"
#include "Computer.h"
#include <QWidget>
#include <QSettings>
#include <QObject>

class MainWindow;

class Application : public QObject
{
    Q_OBJECT
private:
    MainWindow* window;
    Computer computer;
public:
    Application();
    ~Application();
};

#endif // APPLICATION_H
