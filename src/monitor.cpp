#include "monitor.h"
#include <QDateTime>
#include <QThread>

Monitor::Monitor()
{
    pTaskListData = nullptr;
    pResultListData = nullptr;
    mCurrentTask = 0;
    mCurrentResult = 0;
    mRun = false;
    mCurrentLatitude = 0.0;
    mCurrentLongitude = 0.0;
    mCurrentConfidence = 0.0;
    mCurrentClassification = 0;

    mRun = false;
    pDate = new QDate;
    pTime = new QTime;
    myCameraCallback.monitor = this;
    pCamera = new Camera();
    pCamera->registerSceneCallback(&myCameraCallback);

    myGNSSCallback.monitor = this;
    pGNSS = new GTU7();
    pGNSS->registerSerialCallback(&myGNSSCallback);
}

void Monitor::runDetection(const cv::Mat& mat)
{ 
    std::vector<ncnn::Object> objects;

    cv::Mat dst = mat.clone();
    cv::resize(mat, dst, cv::Size(mat.cols,mat.rows), cv::INTER_LINEAR);
    mNcnn.detect(dst,objects);

    std::vector<std::string> className;

    for (int i = 0; i < 10; i++)
    {
        className.push_back(std::to_string(i));
    }

    mNcnn.drawObjects(dst, dst, objects, className);

    //save results

    //save image when some things is detected

    ResultListData_t* pResult = &(*pResultListData->data())[pResultListData->size() - 1];

    if (objects.size() > 0)
    {
        setCurrentClassification(objects[0].label);
        pResult->label.push_back(mCurrentClassification);

        setCurrentConfidence(objects[0].prob);
        pResult->confidence.push_back(mCurrentConfidence);

        pResult->latitude.push_back(mCurrentLatitude);
        pResult->longitude.push_back(mCurrentLongitude);

        QRect roiRect(objects[0].rect.x,
                      objects[0].rect.y,
                      objects[0].rect.width,
                      objects[0].rect.height);

        pResult->roi.push_back(roiRect);

        QString imgName = QString::number(pResult->imgName.size()) + ".jpg";
        pResult->imgName.push_back(imgName);
        QString imgPath = pResultListData->getResultFolderPath() + "/" +
                        pResult->date + "/" +
                        imgName;
        std::cout << imgPath.toStdString() << std::endl;
        cv::imwrite(imgPath.toStdString(), mat);
    }

    mutex.lock();
    cv::Mat display = dst.clone();
    mImg = QImage(display.data, display.cols, display.rows, QImage::Format_BGR888);
    mutex.unlock();

    emit imgChanged();
    QThread::msleep(50);
}

void Monitor::setCurrentTask(int i)
{
    mCurrentTask = i;
}

int Monitor::currentTask()
{
    return mCurrentTask;
}

void Monitor::setCurrentGNSS(double lat, double log)
{
    std::cout << "setCurrentGNSS" << std::endl;
    mCurrentLatitude = lat;
    mCurrentLongitude = log;
    emit currentGNSSStrChanged();
}

QString Monitor::currentGNSSStr()
{
    if (!mRun)
        return "--";

    QString str = QString::number(mCurrentLatitude) + "," +
            QString::number(mCurrentLongitude);
    return str;
}

void Monitor::setCurrentConfidence(double value)
{
    mCurrentConfidence = value;
    emit currentConfidenceStrChanged();
}

QString Monitor::currentConfidenceStr()
{
    if (!mRun)
        return "--";

    QString str = QString::number(mCurrentConfidence);
    return str;
}

void Monitor::setCurrentClassification(int value)
{
    mCurrentClassification = value;
    emit currentClassificationStrChanged();
}

QString Monitor::currentClassificationStr()
{
    if (!mRun)
        return "--";

    QString str = QString::number(mCurrentClassification);
    return str;
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
    return mRun;
}

void Monitor::runButton()
{
    if (mRun)
    {
        mRun = false;
        pCamera->stop();
        pGNSS->stop();
        QImage image(640,480, QImage::Format_BGR888);
        mImg = image;
        emit imgChanged();
        pResultListData->save();
    }
    else
    {
        mRun = true;
        //append result list
        ResultListData_t _result;

        _result.date = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
        _result.name = QDateTime::currentDateTime().toString("MMddhhmmss");
        _result.method = "NCNN";

        pResultListData->addResult(_result);
        mNcnn.loadParam((*pTaskListData->data())[mCurrentTask].weightPath.toStdString());
        mNcnn.loadModel((*pTaskListData->data())[mCurrentTask].modelPath.toStdString());

        QList<QSerialPortInfo> serialPortList = QSerialPortInfo::availablePorts();
        if (serialPortList.size() > 0)
        {
            std::string portName = serialPortList[0].portName().toStdString();
            pGNSS->start(portName);
        }
        pCamera->start();
    }
    emit runChanged();
}

QImage Monitor::img()
{
    QImage img;
    mutex.lock();
    img = mImg;
    mutex.unlock();
    return img;
}

