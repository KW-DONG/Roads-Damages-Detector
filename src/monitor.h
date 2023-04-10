#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>
#include <QStringList>
#include <QImage>
#include <QMutex>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "resultlistdata.h"
#include "tasklistdata.h"
#include "camera.h"
#include "cusncnn.h"
#include "gtu7.h"

class Monitor : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentTask READ currentTask WRITE setCurrentTask NOTIFY currentTaskChanged)
    Q_PROPERTY(QStringList taskList READ taskList NOTIFY taskListChanged)
    Q_PROPERTY(QImage img READ img NOTIFY imgChanged)
    Q_PROPERTY(bool run READ run NOTIFY runChanged)
    Q_PROPERTY(QString currentGNSSStr READ currentGNSSStr NOTIFY currentGNSSStrChanged)
    Q_PROPERTY(QString currentConfidenceStr READ currentConfidenceStr NOTIFY currentConfidenceStrChanged)
    Q_PROPERTY(QString currentClassificationStr READ currentClassificationStr NOTIFY currentClassificationStrChanged)

public:
    Monitor();

    void runDetection(const cv::Mat& mat);

    struct MyCameraCallback : Camera::SceneCallback {
        Monitor* monitor = nullptr;
        virtual void nextScene(const cv::Mat &mat) {
                    if (nullptr != monitor) {
                        monitor->runDetection(mat);
                    }
                }
    };

    struct MyGNSSCallback : GTU7::SerialCallback {
        Monitor* monitor = nullptr;
        virtual void next(double lat, double lon) {
            if (nullptr != monitor) {
                monitor->setCurrentGNSS(lat, lon);
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
    void currentGNSSStrChanged();
    void currentConfidenceStrChanged();
    void currentClassificationStrChanged();

public slots:
    void setCurrentTask(int i);
    int currentTask();

    void setCurrentGNSS(double lat, double log);
    QString currentGNSSStr();

    void setCurrentConfidence(double value);
    QString currentConfidenceStr();

    void setCurrentClassification(int value);
    QString currentClassificationStr();

    QStringList taskList();

    bool run();
    void runButton();

    void setTaskListData(TaskListData* ptr);
    void setResultListData(ResultListData* ptr);

    QImage img();

private:
    Camera* pCamera;
    GTU7* pGNSS;
    TaskListData* pTaskListData;
    ResultListData* pResultListData;

    //properties
    int mCurrentTask;
    int mCurrentResult;
    bool mRun;
    QMutex mutex;
    QImage mImg;
    QDate* pDate;
    QTime* pTime;
    QTimer* pTimer;

    MyCameraCallback myCameraCallback;
    MyGNSSCallback myGNSSCallback;

    ncnn::CusNCNN mNcnn;

    double mCurrentLatitude;
    double mCurrentLongitude;
    double mCurrentConfidence;
    int mCurrentClassification;

    bool timeOut;
};

#endif
