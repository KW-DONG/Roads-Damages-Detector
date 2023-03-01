#include "resultlistmodel.h"
#include "monitor.h"
#include "resultlistdata.h"

ResultListModel::ResultListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

void ResultListModel::refresh()
{
    beginResetModel();
    endResetModel();
}

int ResultListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || pList == nullptr)
        return 0;

    return pList->size();
}

QVariant ResultListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ResultListData_t item = pList->data()->at(index.row());

    switch (role)
    {
        case NameRole:
            return QVariant(item.name);
    }
    return QVariant();
}

bool ResultListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!pList) return false;

    ResultListData_t item = pList->data()->at(index.row());

    switch (role)
    {
        case NameRole:
            item.name = value.toString();
        break;
    }

    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

Qt::ItemFlags ResultListModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ResultListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    return names;
}

ResultListData* ResultListModel::list() const
{
    return pList;
}

void ResultListModel::setList(ResultListData* data)
{
    beginResetModel();

    if (pList)
        pList->disconnect(this);

    pList = data;

    if (pList)
    {
        connect(pList, &ResultListData::preResultAppend, this, [=]() {
            const int index = pList->data()->size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(pList, &ResultListData::postResultAppend, this, [=]() {
            endInsertRows();
        });
        connect(pList, &ResultListData::preResultRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(pList, &ResultListData::postResultRemoved, this, [=]() {
            endRemoveRows();
        });
    }
    endResetModel();
}

