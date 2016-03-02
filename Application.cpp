#include "Application.h"
#include <QApplication>
#include <QWidget>

Application::Application()
{
    QCoreApplication::setApplicationName("InternalEye");
    QCoreApplication::setOrganizationDomain("https://github.com/ZaMaZaN4iK/InternalEye");
    QCoreApplication::setOrganizationName("ZamSoft");
    window = new MainWindow;


    window->show();
}

Application::~Application()
{
    delete window;
}
