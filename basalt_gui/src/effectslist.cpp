#include "effectslist.hpp"

EffectsList::EffectsList(QList<Effect*>* effects, QObject* parent) : QAbstractListModel(parent), list(effects)
{
}

int EffectsList::rowCount(const QModelIndex&) const
{
    return list->count();
}

QVariant EffectsList::data(const QModelIndex& index, int role) const
{
    if (index.isValid())
    {
        if (role == Qt::DisplayRole)
            return list->at(index.row())->getName();
        else if (role == Qt::ToolTipRole)
            return list->at(index.row())->getDesc();
    }

    return QVariant();
}

void EffectsList::update()
{
    emit dataChanged(index(0), index(list->count()));
}

Qt::ItemFlags EffectsList::flags(const QModelIndex& index) const
{
    if (index.isValid())
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}
