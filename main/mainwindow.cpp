#include "mainwindow.h"
#include "keylistener.h"
#include "publicinfomanager.h"
#include "pushbutton.h"

#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>

MainWindow::MainWindow()
{
    uiInit();   // 初始化UI
    systemTrayIconInit();   // 初始化系统托盘图标

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
    setWindowIcon(QIcon(info::get("iconPath").toString()));
    setWindowTitle(info::get("name").toString());
    setFixedSize(800, 600);
    setWindowFlags(Qt::FramelessWindowHint);   // 无边框窗口

    // 关闭按钮
    m_closeBtn = new PushButton(this);
    m_closeBtn->setGeometry(width() - 50, 0, 50, 50);
    m_closeBtn->show();
    connect(m_closeBtn, &QPushButton::clicked, this, &MainWindow::close);
}

void MainWindow::systemTrayIconInit()
{
    m_systemTrayIcon = new QSystemTrayIcon(this);
    m_systemTrayIcon->setIcon(QIcon(info::get("iconPath").toString()));
    m_systemTrayIcon->setToolTip(info::get("name").toString());

    // 显示
    QAction* showAction = new QAction("显示", this);
    showAction->setIcon(QIcon(info::get("iconPath").toString()));
    connect(showAction, &QAction::triggered, this, &MainWindow::showNormal);
    // 隐藏
    QAction* hideAction = new QAction("隐藏", this);
    hideAction->setIcon(QIcon(info::get("iconPath").toString()));
    connect(hideAction, &QAction::triggered, this, &MainWindow::hide);
    // 退出
    QAction* exitAction = new QAction("退出", this);
    connect(exitAction, &QAction::triggered, this, &QApplication::exit);
    // 菜单
    QMenu* trayMenu = new QMenu(this);
    trayMenu->addAction(showAction);
    trayMenu->addAction(hideAction);
    trayMenu->addAction(exitAction);
    m_systemTrayIcon->setContextMenu(trayMenu);

    // 系统托盘图标点击事件
    connect(m_systemTrayIcon, &QSystemTrayIcon::activated, this, [&](QSystemTrayIcon::ActivationReason reason){
        if (reason == QSystemTrayIcon::DoubleClick)
        {
            showNormal();
        }
    });

    m_systemTrayIcon->show();
}
