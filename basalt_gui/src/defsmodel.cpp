#include "defsmodel.hpp"

DefsModel::DefsModel(QMap<QString, QString>* m, QObject* parent) : QAbstractTableModel(parent), map(m)
{
}

QVariant DefsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        switch (section)
        {
            case 0: return "Name";
            case 1: return "Value";
        }

    return QVariant();
}

int DefsModel::rowCount(const QModelIndex&) const
{
    return map->count();
}

int DefsModel::columnCount(const QModelIndex&) const
{
    return 2;
}

QVariant DefsModel::data(const QModelIndex& index, int role) const
{
    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
        return index.column() == 1 ? map->value(map->keys()[index.row()]) : map->keys()[index.row()];

    return QVariant();
}

bool DefsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (data(index, role) != value)
    {
        if (index.column() == 0)
        {
            const QString first  = map->keys()[index.row()];
            const QString second = (*map)[first];
            map->remove(first);
            (*map)[value.toString()] = second;
        }
        else
        {
            (*map)[map->keys()[index.row()]] = value.toString();
        }
        emit changed();
        emit dataChanged(this->index(0, 0), this->index(10000, 10000), {role});
        return true;
    }
    return false;
}

Qt::ItemFlags DefsModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void DefsModel::update()
{
    emit dataChanged(index(0, 0), index(map->count(), 1));
    emit layoutChanged();
}
