#ifndef RESULTLISTDATA_H
#define RESULTLISTDATA_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QImage>

struct ResultListData_t
{
    QString name;
    QString date;
    QString method;
    QVector<double> confidence;
    QVector<int> label;
    QVector<double> longitude;
    QVector<double> latitude;
    QVector<QRect> roi;
    QVector<QString> imgName;
};

class ResultListData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(QImage img READ img NOTIFY imgChanged)
    Q_PROPERTY(int imgNum READ imgNum NOTIFY imgNumChanged)
    Q_PROPERTY(int imgIdx READ imgIdx WRITE setImgIdx NOTIFY imgIdxChanged)
    Q_PROPERTY(QString imgName READ imgName NOTIFY imgNameChanged)
    Q_PROPERTY(QString imgShowIdx READ imgShowIdx NOTIFY imgShowIdxChanged)

public:
    explicit ResultListData(QObject *parent = nullptr);
    ~ResultListData();

    QVector<ResultListData_t>* data() const;
    int size();

signals:
    void preResultAppend();
    void postResultAppend();
    void preResultRemoved(int index);
    void postResultRemoved();

    void indexChanged();
    void imgChanged();
    void imgNumChanged();
    void imgIdxChanged();
    void imgNameChanged();
    void imgShowIdxChanged();

public slots:
    void addResult(ResultListData_t value);
    void removeResult(int id);

    //qproperties
    void setIndex(int value);
    int index();

    QImage img();
    int imgNum();

    void setImgIdx(int value);
    int imgIdx();

    QString imgName();
    QString imgShowIdx();
    QString getResultFolderPath();

    void readSave();
    void save();

private:
    QVector<ResultListData_t> mItems;
    int currentResult = 0;
    int currentImg = 0;
    QString rootPath;
    QString resultFolderPath;

};

#endif
