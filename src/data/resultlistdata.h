#ifndef RESULTLISTDATA_H
#define RESULTLISTDATA_H

#include <QObject>
#include <QString>
#include <QVector>

struct ResultListData_t
{
    QString name;
    QString method;
    QString result;
};

class ResultListData : public QObject
{
    Q_OBJECT
public:
    explicit ResultListData(QObject *parent = nullptr);

    QVector<ResultListData_t>* data() const;
    bool loadResult(const QString& path);
    bool saveResult(const QString& path);
    int size();

signals:
    void preResultAppend();
    void postResultAppend();
    void preResultRemoved(int index);
    void postResultRemoved();

public slots:
    void addResult();
    void removeResult(int id);
private:
    QVector<ResultListData_t> mItems;
    int index;
};




#endif
