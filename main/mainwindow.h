#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// 主窗口

#include <QMainWindow>

class KeyListener;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    KeyListener* m_keyListener; // 按键监听器
};

#endif // MAINWINDOW_H
