#include "pushbutton.h"
#include "publicinfomanager.h"

PushButton::PushButton(QWidget *parent)
    : QPushButton(parent)
{
    setIcon(QIcon(info::get("resPath").toString() + "Ynnkie.png"));
}

PushButton::~PushButton()
{
}
