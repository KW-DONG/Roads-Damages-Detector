#ifndef RESULTLISTMODEL_H
#define RESULTLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include "resultlistdata.h"

class ResultListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ResultListData* list READ list WRITE setList)

    enum {
        NameRole = Qt::UserRole,
        DateRole
    };

    Q_INVOKABLE void refresh();
public:
    explicit ResultListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ResultListData* list() const;

    void setList(ResultListData* list);

private:
    ResultListData* pList = nullptr;
};




#endif
