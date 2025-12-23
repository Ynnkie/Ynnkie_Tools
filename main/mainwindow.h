#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// 主窗口

#include <QMainWindow>

class QPushButton;
class QSystemTrayIcon;
class KeyListener;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

protected:
    // 拖动窗口
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    void uiInit();  // 初始化UI
    void systemTrayIconInit();  // 初始化系统托盘图标

private:
    QPushButton* m_closeBtn; // 关闭按钮
    QSystemTrayIcon* m_systemTrayIcon;   // 系统托盘图标

    KeyListener* m_keyListener; // 按键监听器

    QPoint m_dragPosition;  // 拖动位置
    bool m_isDragging;  // 是否正在拖动
};

#endif // MAINWINDOW_H
