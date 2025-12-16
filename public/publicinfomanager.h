#ifndef PUBLICINFOMANAGER_H
#define PUBLICINFOMANAGER_H

// 公共信息管理类 单例模式

#include <QObject>
#include <QJsonObject>
#include <mutex>

// 添加导出宏定义
#ifdef PUBLIC_LIBRARY
#define PUBLIC_EXPORT Q_DECL_EXPORT
#else
#define PUBLIC_EXPORT Q_DECL_IMPORT
#endif

class PUBLIC_EXPORT Publicinfomanager : public QObject
{
    Q_OBJECT
public:
    // 单例模式 禁止拷贝构造函数和赋值运算符
    Publicinfomanager(const Publicinfomanager&) = delete;
    Publicinfomanager& operator=(const Publicinfomanager&) = delete;

    static Publicinfomanager* instance();   // 获取单例实例
    static QJsonValue get(const QString& key); // 获取公共信息

private:
    explicit Publicinfomanager();
    ~Publicinfomanager();

private:
    static std::atomic<Publicinfomanager*> m_instance; // 单例实例
    static std::mutex m_mutex;  // 互斥锁
    static QJsonObject m_publicInfo;    // 公共信息存储对象
};

using info = Publicinfomanager;

#endif // PUBLICINFOMANAGER_H
