#include "mainwindow.h"
#include "keylistener.h"

#include <QApplication>
#include <QPushButton>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
{
    uiInit();

    m_keyListener = KeyListener::instance();
    connect(m_keyListener, &KeyListener::keyPressed, this, [&](const QString& key){
        qDebug() << "Key Pressed:" << m_keyListener->pressedKeys();
    });
    connect(m_keyListener, &KeyListener::keyReleased, this, [&](const QString& key){
        qDebug() << "Key Released:" << key;
    });
}

MainWindow::~MainWindow()
{
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_isDragging = true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging && (event->buttons() & Qt::LeftButton))
    {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isDragging = false;
    }
}

void MainWindow::uiInit()
{
    // 窗口
    setWindowIcon(QIcon(QApplication::applicationDirPath() + "/res/Ynnkie.png"));
    setWindowTitle("云可工具");
    setFixedSize(800, 600);
    setWindowFlags(Qt::FramelessWindowHint);   // 无边框窗口

    // 关闭按钮
    m_closeBtn = new QPushButton(this);
    m_closeBtn->setText("关闭");
    m_closeBtn->setGeometry(width() - 50, 0, 50, 50);
    m_closeBtn->show();
    connect(m_closeBtn, &QPushButton::clicked, this, &MainWindow::close);
}
