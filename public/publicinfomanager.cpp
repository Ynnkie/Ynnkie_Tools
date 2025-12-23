#include "publicinfomanager.h"

#include <QApplication>

std::atomic<Publicinfomanager*> Publicinfomanager::m_instance = nullptr;
std::mutex Publicinfomanager::m_mutex;
QJsonObject Publicinfomanager::m_publicInfo;

Publicinfomanager *Publicinfomanager::instance()
{
    Publicinfomanager* instance = m_instance.load();    // 加载单例实例
    if (instance == nullptr)
    {
        std::lock_guard<std::mutex> lock(m_mutex);  // 加锁
        instance = m_instance.load();   // 再次加载单例实例
        if (instance == nullptr)    // 双重检查
        {
            instance = new Publicinfomanager(); // 创建单例实例
            m_instance.store(instance); // 存储单例实例
        }
    }
    return instance;
}

QJsonValue Publicinfomanager::get(const QString &key)
{
    return instance()->m_publicInfo.value(key);
}

Publicinfomanager::Publicinfomanager()
{
    m_publicInfo.insert("name", "云可工具");
    m_publicInfo.insert("iconPath", QApplication::applicationDirPath() + "/res/Ynnkie.png");
    m_publicInfo.insert("resPath", QApplication::applicationDirPath() + "/res/");
}

Publicinfomanager::~Publicinfomanager()
{
}
