#include "pathlistmodel.hpp"

PathListModel::PathListModel(QList<QDir>& l, QObject* parent) : QAbstractListModel(parent), list(l)
{
}

int PathListModel::rowCount(const QModelIndex&) const
{
    return list.count();
}

QVariant PathListModel::data(const QModelIndex& index, int role) const
{
    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
        return list.at(index.row()).absolutePath();

    return QVariant();
}

void PathListModel::update()
{
    emit dataChanged(index(0), index(list.count()));
}
