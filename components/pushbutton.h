#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

// 自定义按钮类

#include <QPushButton>

// 添加导出宏定义
#ifdef COMPONENTS_LIBRARY
// 导出符号
#define PUSHBUTTON_EXPORT Q_DECL_EXPORT
#else
// 导入符号
#define PUSHBUTTON_EXPORT Q_DECL_IMPORT
#endif

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton(QWidget *parent = nullptr);
    ~PushButton();
};

#endif // PUSHBUTTON_H
