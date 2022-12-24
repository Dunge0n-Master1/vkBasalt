#pragma once

#include <QAbstractListModel>
#include <QDir>

class PathListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PathListModel(QList<QDir>& list, QObject* parent = nullptr);

    int      rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void     update();

private:
    QList<QDir>& list;
};
