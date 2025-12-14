#include "mainwindow.h"
#include "keylistener.h"

#include <QApplication>
#include <QkeyEvent>

MainWindow::MainWindow(QWidget *parent)
{
    setWindowIcon(QIcon(QApplication::applicationDirPath() + "/res/Ynnkie.png"));

    setWindowTitle("云可工具");
    setFixedSize(800, 600);

    m_keyListener = KeyListener::instance();
    connect(m_keyListener, &KeyListener::keyPressed, this, [](const QString& key){
        qDebug() << "Key Pressed:" << key;
    });
    connect(m_keyListener, &KeyListener::keyReleased, this, [](const QString& key){
        qDebug() << "Key Released:" << key;
    });
}

MainWindow::~MainWindow()
{
}
