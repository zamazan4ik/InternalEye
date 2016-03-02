#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "MenuBar.h"
#include "Application.h"

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* pvbx;
    QHBoxLayout* genButtons;
    MenuBar* pMenuBar;

    QPushButton* refresh;

    void writeSettings() const;
    void readSettings();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
