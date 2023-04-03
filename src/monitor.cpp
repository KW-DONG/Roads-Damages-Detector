#include "monitor.h"
#include <QDateTime>
#include <QThread>

Monitor::Monitor()
{
    mRun = false;

    pDate = new QDate;
    pTime = new QTime;

    myCameraCallback.monitor = this;
    camera = new Camera();
    camera->registerSceneCallback(&myCameraCallback);
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
    //cv::waitKey(50);
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
        camera->stop();
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
        //std::string paramPath = "/home/lochcliff/ProgramFiles/Roads-Damages-Detector/bin/best.param";
        //std::string modelPath = "/home/lochcliff/ProgramFiles/Roads-Damages-Detector/bin/best.bin";
        std::string paramPath = "C:/Users/Kaiwen Dong/Blackboard/UofG/Real Time Embedded Programming/Roads-Damages-Detector/bin/best.param";
        std::string modelPath = "C:/Users/Kaiwen Dong/Blackboard/UofG/Real Time Embedded Programming/Roads-Damages-Detector/bin/best.bin";

        //(*pTaskListData->data())[_currentTask].weightPath
        mNcnn.loadParam((*pTaskListData->data())[mCurrentTask].weightPath.toStdString());
        mNcnn.loadModel((*pTaskListData->data())[mCurrentTask].modelPath.toStdString());

        camera->start();
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

