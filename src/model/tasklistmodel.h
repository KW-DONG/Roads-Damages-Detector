#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include "tasklistdata.h"

class TaskListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TaskListData* list READ list WRITE setList)

    enum {
        NameRole = Qt::UserRole,
    };

    Q_INVOKABLE void refresh();

public:
    explicit TaskListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    TaskListData* list() const;

    void setList(TaskListData* list);

private:
    TaskListData* pList = nullptr;
};

#endif // TASKLISTMODEL_H
