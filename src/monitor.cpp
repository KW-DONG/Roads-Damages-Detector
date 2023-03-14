#include "monitor.h"

Monitor::Monitor()
{
    _run = false;
    myCallback.monitor = this;
    camera = new Camera();
    camera->registerSceneCallback(&myCallback);
}

void Monitor::runDetection(const cv::Mat& mat)
{
    mutex.lock();
    _img = QImage(mat.data, mat.cols, mat.rows, QImage::Format_BGR888);
    mutex.unlock();
    cv::waitKey(50);
    emit imgChanged();
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

