#include "monitor.h"
#include <QDateTime>
#include <QThread>

Monitor::Monitor()
{
    _run = false;

    pDate = new QDate;
    pTime = new QTime;

    myCallback.monitor = this;
    camera = new Camera();
    camera->registerSceneCallback(&myCallback);
}

void Monitor::runDetection(const cv::Mat& mat)
{ 
    std::vector<ncnn::Object> objects;

    cv::Mat dst;
    cv::resize(mat, dst, cv::Size(mat.cols,mat.rows), cv::INTER_LINEAR);
    mNcnn.detect(dst,objects);

    std::vector<std::string> className;

    for (int i = 0; i < 100; i++)
    {
        className.push_back(std::to_string(i));
    }


    mNcnn.drawObjects(dst, dst, objects, className);

    mutex.lock();
    _img = QImage(dst.data, dst.cols, dst.rows, QImage::Format_BGR888);
    mutex.unlock(); 

    emit imgChanged();
    QThread::msleep(50);
}

void Monitor::setCurrentTask(int i)
{
    _currentTask = i;
}

int Monitor::currentTask()
{
    return _currentTask;
}

void Monitor::setLocalImgPath(QString path)
{
    _localImgPath = path;
}

QString Monitor::localImgPath()
{
    return _localImgPath;
}

QStringList Monitor::log()
{
    return _log;
}

QStringList Monitor::taskList()
{
    QStringList list;
    QVector<TaskListData_t>* pData = pTaskListData->data();
    for (int i = 0; i < pData->size(); i++)
    {
        list.push_back((pData->data()[i].title));
    }
    return list;
}

void Monitor::setTaskListData(TaskListData* ptr)
{
    pTaskListData = ptr;
    connect(pTaskListData, &TaskListData::sizeChanged, this, [this](){ emit taskListChanged();});
}

void Monitor::setResultListData(ResultListData* ptr)
{
    pResultListData = ptr;
}

bool Monitor::run()
{
    return _run;
}

void Monitor::runButton()
{
    if (_run)
    {
        _run = false;
        camera->stop();
    }
    else
    {
        _run = true;
        //append result list
        ResultListData_t _result;

        _result.date = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
        _result.name = QDateTime::currentDateTime().toString("MMddhhmmss");
        _result.method = "NCNN";

        pResultListData->addResult(_result);
        std::string paramPath = "/home/lochcliff/ProgramFiles/Roads-Damages-Detector/bin/best.param";
        std::string modelPath = "/home/lochcliff/ProgramFiles/Roads-Damages-Detector/bin/best.bin";

        mNcnn.loadParam(paramPath);
        mNcnn.loadModel(modelPath);

        camera->start();
    }
    emit runChanged();
}

QImage Monitor::img()
{
    QImage img;
    mutex.lock();
    img = _img;
    mutex.unlock();
    return img;
}

