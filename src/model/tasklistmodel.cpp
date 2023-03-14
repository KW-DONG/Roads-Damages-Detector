#include "tasklistmodel.h"
#include "monitor.h"

TaskListModel::TaskListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

void TaskListModel::refresh()
{
    beginResetModel();
    endResetModel();
}

int TaskListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || pList == nullptr)
        return 0;

    return pList->size();
}

QVariant TaskListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || pList->size() == 0)
        return QVariant();

    TaskListData_t item = pList->data()->at(index.row());

    switch (role)
    {
        case NameRole:
            return QVariant(item.title);
    }
    return QVariant();
}

bool TaskListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!pList || pList->size() == 0) return false;

    switch (role)
    {
        case NameRole:
        {
            QString temp = value.toString();
            pList->setTitle(temp);
            break;
        }
    }
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

Qt::ItemFlags TaskListModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> TaskListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "title";
    return names;
}

TaskListData* TaskListModel::list() const
{
    return pList;
}

void TaskListModel::setList(TaskListData* data)
{
    beginResetModel();

    if (pList)
        pList->disconnect(this);

    pList = data;

    if (pList)
    {
        connect(pList, &TaskListData::preTaskAppend, this, [=]() {
            const int index = pList->data()->size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(pList, &TaskListData::postTaskAppend, this, [=]() {
            endInsertRows();
        });
        connect(pList, &TaskListData::preTaskRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(pList, &TaskListData::postTaskRemoved, this, [=]() {
            endRemoveRows();
        });
        connect(pList, &TaskListData::titleChanged, this, &TaskListModel::refresh);
    }
    endResetModel();
}



