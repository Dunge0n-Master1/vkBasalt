#include "ignorewheeleventfilter.hpp"
#include <QEvent>

IgnoreWheelEventFilter::IgnoreWheelEventFilter(QObject* parent) : QObject{parent}
{
    parent->installEventFilter(this);
}

bool IgnoreWheelEventFilter::eventFilter(QObject* o, QEvent* e)
{
    if (e->type() == QEvent::Wheel)
        return true;
    return QObject::eventFilter(o, e);
}
