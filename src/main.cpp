#include <QApplication>
#include <QProcess>
#include <QDebug>
#include <QByteArray>
#include "Computer.h"
#include "Application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application app;
    return a.exec();
}
