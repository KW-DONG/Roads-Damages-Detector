#include "monitor.h"
#include <QDateTime>

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
}

void Monitor::runDetection(const cv::Mat& mat)
{ 
    std::vector<ImgRecog::Object> objects;

    cv::Mat dst = mat.clone();
    cv::resize(mat, dst, cv::Size(mat.cols,mat.rows), cv::INTER_LINEAR);
    pImgRecog->detect(dst,objects);

    std::vector<std::string> className;

    for (int i = 0; i < (*pTaskListData->data())[mCurrentTask].labels; i++)
    {
        className.push_back(std::to_string(i));
    }

    if (objects.size() > 0)
    {
        double prob = objects[0].prob;
        if (prob >= (*pTaskListData->data())[mCurrentTask].threshold)
        {
            pImgRecog->drawObjects(dst, dst, objects, className);

            //save image when some things is detected
            ResultListData_t* pResult = &(*pResultListData->data())[pResultListData->size() - 1];

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
            cv::imwrite(imgPath.toStdString(), mat);
        }
    }

    cv::Mat display = dst.clone();
    cv::cvtColor(display, display, cv::COLOR_BGR2RGB);
    QImage _img = QImage(display.data, display.cols, display.rows, QImage::Format_RGB888);

    mImg = _img.copy();
    emit imgChanged();
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

void Monitor::registerTaskListData(TaskListData* ptr)
{
    pTaskListData = ptr;
    connect(pTaskListData, &TaskListData::sizeChanged, this, [this](){ emit taskListChanged();});
    connect(pTaskListData, &TaskListData::titleChanged, this, [this](){ emit taskListChanged();});
}

void Monitor::registerResultListData(ResultListData* ptr)
{
    pResultListData = ptr;
}

void Monitor::registerImgRecog(ImgRecog* ptr)
{
    pImgRecog = ptr;
}

void Monitor::registerGNSS(GNSS* ptr)
{
    pGNSS = ptr;
    myGNSSCallback.monitor = this;
    pGNSS->registerCallback(&myGNSSCallback);
}

void Monitor::registerCamera(Camera* ptr)
{
    pCamera = ptr;
    myCameraCallback.monitor = this;
    pCamera->registerSceneCallback(&myCameraCallback);
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
        QImage image(640,480, QImage::Format_RGB888);
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

        std::vector<std::string> _paths;
        _paths.push_back((*pTaskListData->data())[mCurrentTask].modelPath.toStdString());
        _paths.push_back((*pTaskListData->data())[mCurrentTask].weightPath.toStdString());

        pImgRecog->setPath(_paths);

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
    return mImg;
}
