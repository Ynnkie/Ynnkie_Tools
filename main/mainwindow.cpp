#include "mainwindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
{
    setWindowIcon(QIcon(QApplication::applicationDirPath() + "/res/Ynnkie.png"));

    setWindowTitle("云可工具");
    setFixedSize(800, 600);
}

MainWindow::~MainWindow()
{
}
