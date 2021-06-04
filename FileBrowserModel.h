#ifndef FILEBROWSERMODEL_H
#define FILEBROWSERMODEL_H
#include <QAbstractTableModel>
#include <QList>
#include "Data.h"

class FileBrowserModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QList<Data> _data;
    enum class ColumnName {
        NAME = 0,
        SIZE,
        PERCENT
    };

    void setModelData(const QList<Data>& data);
public:
    explicit FileBrowserModel(const QList<Data>& data, QObject* parent = nullptr);
    ~FileBrowserModel() = default;
    // методы необходимые для переопределения
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

};

#endif // FILEBROWSERMODEL_H
