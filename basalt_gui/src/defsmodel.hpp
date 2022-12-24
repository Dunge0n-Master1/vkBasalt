#pragma once

#include <QAbstractTableModel>
#include <QMap>

class DefsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DefsModel(QMap<QString, QString>* map, QObject* parent = nullptr);

    QVariant      headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int           rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int           columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant      data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool          setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    void          update();

private:
    QMap<QString, QString>* map;

signals:
    void changed();
};
