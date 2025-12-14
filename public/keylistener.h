#ifndef KEYLISTENER_H
#define KEYLISTENER_H

// 按键监听类 单例模式

#include <QObject>
#include <QMap>
#include <mutex>
#include <Windows.h>

// 添加导出宏定义
#ifdef PUBLIC_LIBRARY
#define PUBLIC_EXPORT Q_DECL_EXPORT
#else
#define PUBLIC_EXPORT Q_DECL_IMPORT
#endif

class PUBLIC_EXPORT KeyListener : public QObject
{
    Q_OBJECT
public:
    // 单例模式 禁止拷贝构造函数和赋值运算符
    KeyListener(const KeyListener&) = delete;
    KeyListener& operator=(const KeyListener&) = delete;

    static KeyListener* instance(); // 获取单例实例

signals:
    void keyPressed(const QString& key);    // 按键按下信号
    void keyReleased(const QString& key);   // 按键释放信号

private:
    static LRESULT CALLBACK keyHookProc(int nCode, WPARAM wParam, LPARAM lParam);   // 键盘钩子回调函数
    explicit KeyListener();
    ~KeyListener();

private:
    static std::atomic<KeyListener*> m_instance;    // 单例实例
    static std::mutex m_mutex;  // 互斥锁
    static HHOOK m_hook;    // 键盘钩子句柄
    static QMap<unsigned int, QString> m_keyMap;    // 按键映射表
};

#endif // KEYLISTENER_H
