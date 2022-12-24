#pragma once

#include <QObject>

class IgnoreWheelEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit IgnoreWheelEventFilter(QObject* parent = nullptr);
    bool eventFilter(QObject* o, QEvent* e) override;
};
