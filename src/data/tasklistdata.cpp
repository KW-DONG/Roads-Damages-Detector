#include "tasklistdata.h"
#include <iostream>
#include <QFile>

#define CONFIG_PATH "./task.xml"

TaskListData::TaskListData(QObject *parent)
    : QObject{parent}
{
    std::cout << "read config" << std::endl;
    readConfig();
    refresh();
}

TaskListData::~TaskListData()
{
    saveConfig();
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
    emit labelsChanged();
    emit thresholdChanged();
    emit algorithmChanged();
    emit modelTypeChanged();
}

void TaskListData::addTask()
{
    emit preTaskAppend();
    TaskListData_t task;
    task.title = "Untitled";
    task.title += std::to_string(cnt).c_str();
    cnt++;
    task.algorithm = 0;
    task.modelPath = "null";
    task.weightPath = "null";
    task.labels = 10;
    task.modelType = 0;
    task.threshold = 0.5;
    mItems.push_back(task);
    emit postTaskAppend();

    if (mItems.size() == 0 || mItems.size() == 1)
        setIndex(0);
    emit sizeChanged();
    emit titleChanged();
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
#ifdef WIN32
        mItems[_index].modelPath = value.toStdString().substr(8, value.size()).c_str();
#else
        mItems[_index].modelPath = value.toStdString().substr(7, value.size()).c_str();
#endif
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
#ifdef WIN32
        mItems[_index].weightPath = value.toStdString().substr(8, value.size()).c_str();
#else
        mItems[_index].weightPath = value.toStdString().substr(7, value.size()).c_str();
#endif
        emit weightPathChanged();
    }
}

QString TaskListData::weightPath()
{
    if (mItems.size() > _index)
        return mItems[_index].weightPath;
    return "null";
}

void TaskListData::setLabels(int value)
{
    if (mItems.size() > _index)
    {
        std::cout << "set label: " << value << std::endl;
        mItems[_index].labels = value;
        emit labelsChanged();
    }
}

int TaskListData::labels()
{

    if (mItems.size() > _index)
    {
        std::cout << "read labels: " << mItems[_index].labels << std::endl;
        return mItems[_index].labels;
    }

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

void TaskListData::readConfig()
{
    QFile file(CONFIG_PATH);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        saveConfig();
        return;
    }

    QXmlStreamReader xml(&file);

    if (xml.readNextStartElement())
    {
        while (xml.readNextStartElement())
        {
            if (xml.name() == QLatin1String("task"))
            {
                TaskListData_t _task;
                while (xml.readNextStartElement())
                {
                    if (xml.name() == QLatin1String("title"))
                        _task.title = xml.readElementText();
                    else if (xml.name() == QLatin1String("modelpath"))
                        _task.modelPath = xml.readElementText();
                    else if (xml.name() == QLatin1String("weightpath"))
                        _task.weightPath = xml.readElementText();
                    else if (xml.name() == QLatin1String("labels"))
                        _task.labels = xml.readElementText().toInt();
                    else if (xml.name() == QLatin1String("threshold"))
                        _task.threshold = xml.readElementText().toDouble();
                    else if (xml.name() == QLatin1String("algorithm"))
                        _task.algorithm = xml.readElementText().toInt();
                    else if (xml.name() == QLatin1String("model"))
                        _task.modelType = xml.readElementText().toInt();
                }
                mItems.append(_task);
            }
        }
    }

    file.close();
}

void TaskListData::saveConfig()
{
    QFile file(CONFIG_PATH);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QXmlStreamWriter xml(&file);
        xml.setAutoFormatting(true);
        xml.writeStartDocument();
        xml.writeStartElement("document");

        for (int i = 0; i < mItems.size(); i++)
        {
            xml.writeStartElement("task");
            xml.writeTextElement("title", mItems[i].title);
            xml.writeTextElement("modelpath", mItems[i].modelPath);
            xml.writeTextElement("weightpath", mItems[i].weightPath);
            xml.writeTextElement("labels", QString::number(mItems[i].labels));
            xml.writeTextElement("threshold", QString::number(mItems[i].threshold));
            xml.writeTextElement("algorithm", QString::number(mItems[i].algorithm));
            xml.writeTextElement("model", QString::number(mItems[i].modelType));
            xml.writeEndElement();
        }

        xml.writeEndElement();
        xml.writeEndDocument();
        file.close();
    }
}

