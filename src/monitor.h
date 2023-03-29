#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>
#include <QStringList>
#include <QImage>
#include <QMutex>
#include <QDate>
#include <QTime>
#include "resultlistdata.h"
#include "tasklistdata.h"
#include "camera.h"

class Monitor : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentTask READ currentTask WRITE setCurrentTask NOTIFY currentTaskChanged)
    Q_PROPERTY(QStringList taskList READ taskList NOTIFY taskListChanged)
    Q_PROPERTY(QImage img READ img NOTIFY imgChanged)
    Q_PROPERTY(bool run READ run NOTIFY runChanged)

public:
    Monitor();

    void runDetection(const cv::Mat& mat);

    struct MyCallback : Camera::SceneCallback {
        Monitor* monitor = nullptr;
        virtual void nextScene(const cv::Mat &mat) {
                    if (nullptr != monitor) {
                        monitor->runDetection(mat);
                    }
                }
    };

signals:
    void currentTaskChanged();
    void localImgPathChanged();
    void logChanged();
    void taskListChanged();
    void runChanged();

    void imgChanged();

public slots:
    void setCurrentTask(int i);
    int currentTask();

    void setLocalImgPath(QString path);
    QString localImgPath();

    QStringList log();
    QStringList taskList();

    bool run();
    void runButton();

    void setTaskListData(TaskListData* ptr);
    void setResultListData(ResultListData* ptr);

    QImage img();

private:
    Camera* camera;
    TaskListData* pTaskListData;
    ResultListData* pResultListData;

    //properties
    int _currentTask;
    int _currentResult;
    bool _run;
    QString _localImgPath;
    QStringList _log;
    QMutex mutex;
    QImage _img;
    QDate* pDate;
    QTime* pTime;

    MyCallback myCallback;

};

#endif
