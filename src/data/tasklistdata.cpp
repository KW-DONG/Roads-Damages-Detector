#include "tasklistdata.h"
#include <iostream>

TaskListData::TaskListData(QObject *parent)
    : QObject{parent}
{

}

QVector<TaskListData_t>* TaskListData::data() const
{
    return (QVector<TaskListData_t>*)&mItems;
}

bool TaskListData::loadConfig(const QString& path)
{
    return true;
}

bool TaskListData::saveConfig(const QString& path)
{
    return true;
}

void TaskListData::refresh()
{
    emit titleChanged();
    emit modelPathChanged();
    emit weightPathChanged();
    emit classPathChanged();
    emit confidenceChanged();
    emit thresholdChanged();
    emit algorithmChanged();
    emit modelTypeChanged();
    std::cout << "refresh" << std::endl;
}

void TaskListData::addTask()
{
    emit preTaskAppend();
    TaskListData_t task;
    task.title = "Undefined";
    task.title += std::to_string(cnt).c_str();
    cnt++;
    task.algorithm = 0;
    task.classPath = "null";
    task.modelPath = "null";
    task.weightPath = "null";
    task.confidence = 0.5;
    task.modelType = 0;
    task.threshold = 50;
    mItems.push_back(task);
    emit postTaskAppend();
    emit sizeChanged();
    if (mItems.size() == 0)
        setIndex(0);
}

void TaskListData::removeTask(int id)
{
    emit preTaskRemoved(id);

    if ((_index == mItems.size() - 1 && mItems.size() > 1) || id < _index)
        setIndex(_index - 1);

    mItems.removeAt(id);
    emit postTaskRemoved();
    emit sizeChanged();
    refresh();
}

//qproperties
int TaskListData::size()
{
    return mItems.size();
}
void TaskListData::setIndex(int value)
{
    if (mItems.size() > value)
    {
        _index = value;
        emit indexChanged();
        refresh();
    }
    std::cout << "current index: " << _index << std::endl;
}

int TaskListData::index()
{
    if (mItems.size() > _index)
        return _index;
    return 0;
}

void TaskListData::setTitle(QString& value)
{
    if (mItems.size() > _index)
    {
        mItems[_index].title = value;
        emit titleChanged();
    }
}

QString TaskListData::title()
{
    if (mItems.size() > _index)
        return mItems[_index].title;
    return "null";
}

void TaskListData::setModelPath(QString& value)
{
    if (mItems.size() > _index)
    {
        mItems[_index].modelPath = value;
        emit modelPathChanged();
    }
}

QString TaskListData::modelPath()
{
    if (mItems.size() > _index)
        return mItems[_index].modelPath;
    return "null";
}

void TaskListData::setWeightPath(QString& value)
{
    if (mItems.size() > _index)
    {
        mItems[_index].weightPath = value;
        emit weightPathChanged();
    }
}

QString TaskListData::weightPath()
{
    if (mItems.size() > _index)
        return mItems[_index].weightPath;
    return "null";
}

void TaskListData::setClassPath(QString& value)
{
    if (mItems.size() > _index)
    {
        mItems[_index].classPath = value;
        emit classPathChanged();
    }
}

QString TaskListData::classPath()
{
    if (mItems.size() > _index)
        return mItems[_index].classPath;
    return "null";
}

void TaskListData::setConfidence(double value)
{
    if (mItems.size() > _index)
    {
        mItems[_index].confidence = value;
        emit confidenceChanged();
    }
}

double TaskListData::confidence()
{
    if (mItems.size() > _index)
        return mItems[_index].confidence;
    return 0.0;
}

void TaskListData::setThreshold(double value)
{
    if (mItems.size() > _index)
    {
        mItems[_index].threshold = value;
        emit thresholdChanged();
    }
}

double TaskListData::threshold()
{
    if (mItems.size() > _index)
        return mItems[_index].threshold;
    return 0.0;
}

void TaskListData::setAlgorithm(int value)
{
    if (mItems.size() > _index)
    {
        mItems[_index].algorithm = value;
        emit algorithmChanged();
    }
}

int TaskListData::algorithm()
{
    if (mItems.size() > _index)
        return mItems[_index].algorithm;
    return 0;
}

void TaskListData::setModelType(int value)
{
    if (mItems.size() > _index)
    {
        mItems[_index].modelType = value;
        emit modelTypeChanged();
    }
}

int TaskListData::modelType()
{
    if (mItems.size() > _index)
        return mItems[_index].modelType;
    return 0;
}
