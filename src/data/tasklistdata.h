#ifndef TASKLISTDATA_H
#define TASKLISTDATA_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

struct TaskListData_t
{
    QString modelPath;
    QString weightPath;
    QString title;
    QString description;
    double confidence;
    double threshold;
    int algorithm;
    int modelType;
};

class TaskListData : public QObject
{
    Q_OBJECT
public:
    explicit TaskListData(QObject *parent = nullptr);
    ~TaskListData();
    Q_PROPERTY(QString modelPath READ modelPath WRITE setModelPath NOTIFY modelPathChanged);
    Q_PROPERTY(QString weightPath READ weightPath WRITE setWeightPath NOTIFY weightPathChanged);
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged);
    Q_PROPERTY(double confidence READ confidence WRITE setConfidence NOTIFY confidenceChanged);
    Q_PROPERTY(double threshold READ threshold WRITE setThreshold NOTIFY thresholdChanged);
    Q_PROPERTY(int algorithm READ algorithm WRITE setAlgorithm NOTIFY algorithmChanged);
    Q_PROPERTY(int modelType READ modelType WRITE setModelType NOTIFY modelTypeChanged);
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

    QVector<TaskListData_t>* data() const;
    bool loadConfig(const QString& path);
    bool saveConfig(const QString& path);

    Q_INVOKABLE void refresh();

signals:
    void preTaskAppend();
    void postTaskAppend();
    void preTaskRemoved(int index);
    void postTaskRemoved();

    //qproperties
    void modelPathChanged();
    void weightPathChanged();
    void classPathChanged();
    void titleChanged();
    void confidenceChanged();
    void thresholdChanged();
    void algorithmChanged();
    void modelTypeChanged();
    void indexChanged();
    void sizeChanged();

public slots:
    void addTask();
    void removeTask(int id);

    void setIndex(int value);
    int index();

    void setTitle(QString& value);
    QString title();

    void setModelPath(QString& value);
    QString modelPath();

    void setWeightPath(QString& value);
    QString weightPath();

    void setConfidence(double value);
    double confidence();

    void setThreshold(double value);
    double threshold();

    void setAlgorithm(int value);
    int algorithm();

    void setModelType(int value);
    int modelType();

    int size();

private:
    void readConfig();
    void saveConfig();

private:
    QVector<TaskListData_t> mItems;
    int _index = 0;
    int cnt = 0;

#ifdef UNIT_TEST
friend class Test_TaskListData;
#endif
};

#endif // TASKLISTDATA_H
