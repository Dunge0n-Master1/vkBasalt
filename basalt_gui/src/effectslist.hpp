#pragma once

#include <QAbstractListModel>

#include "effect.hpp"

class EffectsList : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit EffectsList(QList<Effect*>* effects, QObject* parent = nullptr);

    int           rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant      data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    void          update();
    Qt::ItemFlags flags(const QModelIndex& index) const;

private:
    QList<Effect*>* list;
};
