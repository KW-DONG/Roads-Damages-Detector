#include "resultlistdata.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDir>
#include <QTextStream>
#include <QCoreApplication>
#include <QPainter>
#include <QRect>

#define SAVE_PATH "./result.xml"

ResultListData::ResultListData(QObject *parent)
    : QObject{parent}
{
    rootPath = QCoreApplication::applicationDirPath();
    resultFolderPath = rootPath + "/result";
    QDir dir(resultFolderPath);
    if (!dir.exists())
        dir.mkdir(resultFolderPath);

    readSave();
}

ResultListData::~ResultListData()
{
    save();
}

QVector<ResultListData_t>* ResultListData::data() const
{
    return (QVector<ResultListData_t>*)&mItems;
}

int ResultListData::size()
{
    return mItems.size();
}

void ResultListData::addResult(ResultListData_t value)
{
    //create result folder
    QString _resultPath = resultFolderPath + "/" +
            value.date;

    QDir dir(_resultPath);
    if (!dir.exists())
        dir.mkdir(_resultPath);

    emit preResultAppend();
    mItems.push_back(value);
    emit postResultAppend();
}

void ResultListData::removeResult(int id)
{
    emit preResultRemoved(id);
    mItems.removeAt(id);
    emit postResultRemoved();
}

void ResultListData::setIndex(int value)
{
    currentResult = value;
    setImgIdx(0);
    imgNumChanged();
}

int ResultListData::index()
{
    return currentResult;
}

QImage ResultListData::img()
{
    //read image
    if (mItems.size() == 0)
        return QImage();

    std::cout << "mItems size: " << mItems.size() << std::endl;
    QString _imgPath = resultFolderPath + "/" +
            mItems[currentResult].date + "/" +
            mItems[currentResult].imgName[currentImg];
    std::cout << "_img: " << _imgPath.toStdString() << std::endl;
    QImage _img(_imgPath);


    //draw rectangle
    QPainter painter(&_img);
    painter.setPen(QPen(Qt::blue,4,Qt::SolidLine));
    QRect rect = mItems[currentResult].roi[currentImg];

    painter.drawRect(rect);
    QPoint point(rect.x(), rect.y() - 20);
    painter.drawText(point, QString::number(mItems[currentResult].confidence[currentImg]));
    QPoint point1(rect.x(), rect.y() - 10);
    painter.drawText(point1, QString::number(mItems[currentResult].label[currentImg]));

    return _img;
}

int ResultListData::imgNum()
{
    return mItems[currentResult].imgName.size();
}

void ResultListData::setImgIdx(int value)
{
    currentImg = value;
    emit imgIdxChanged();
    emit imgChanged();
    emit imgNameChanged();
    emit imgShowIdxChanged();
}

int ResultListData::imgIdx()
{
    return currentImg;
}

QString ResultListData::imgName()
{
    if (mItems.size() == 0)
        return "No result";
    else if (mItems[currentResult].imgName.size() == 0)
        return "No Images";
    else
        return mItems[currentResult].imgName[currentImg];
}

QString ResultListData::imgShowIdx()
{
    if (mItems.size() == 0)
        return "0 / 0";

    QString str = QString::number(currentImg) + " / " +
            QString::number(mItems[currentResult].imgName.size()-1);
    return str;
}

QString ResultListData::getResultFolderPath()
{
    return resultFolderPath;
}

void ResultListData::readSave()
{
    QFile file(SAVE_PATH);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        save();
        return;
    }

    QXmlStreamReader xml(&file);

    if (xml.readNextStartElement())
    {
        while (xml.readNextStartElement())
        {
            if (xml.name() == QLatin1String("task"))
            {
                ResultListData_t _result;
                while (xml.readNextStartElement())
                {
                    if (xml.name() == QLatin1String("title"))
                        _result.name = xml.readElementText();
                    else if (xml.name() == QLatin1String("date"))
                        _result.date = xml.readElementText();
                    else if (xml.name() == QLatin1String("algorithm"))
                        _result.method = xml.readElementText();
                    else if (xml.name() == QLatin1String("data"))
                    {
                        QString elementText = xml.readElementText();

                        QString currentResultPath = resultFolderPath + "/" +
                                                    elementText + "/" +
                                                    elementText + ".csv";

                        std::cout << currentResultPath.toStdString() << std::endl;
                        QFile csvFile(currentResultPath);
                        csvFile.open(QIODevice::ReadOnly | QIODevice::Text);
                        QTextStream in(&csvFile);
                        int i = 0;
                        QStringList list;
                        while (!in.atEnd())
                        {
                            QString fileLine = in.readLine();
                            if (i!= 0)
                            {
                                list = fileLine.split(",", QString::SkipEmptyParts);
                                _result.imgName.push_back(list[1]);
                                std::cout << list[1].toStdString() << std::endl;
                                _result.longitude.push_back(list[2].toDouble());
                                _result.latitude.push_back(list[3].toDouble());
                                _result.label.push_back(list[4].toInt());
                                _result.confidence.push_back(list[5].toDouble());
                                QRect roi(list[6].toInt(),list[7].toInt(),list[8].toInt(),list[9].toInt());
                                _result.roi.push_back(roi);
                            }
                            i++;
                        }
                    }
                }
                mItems.append(_result);
            }
        }
    }
}

void ResultListData::save()
{
    QFile file(SAVE_PATH);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QXmlStreamWriter xml(&file);
        xml.setAutoFormatting(true);
        xml.writeStartDocument();
        xml.writeStartElement("document");

        for (int i = 0; i < mItems.size(); i++)
        {
            xml.writeStartElement("task");
            xml.writeTextElement("title", mItems[i].name);
            xml.writeTextElement("date", mItems[i].date);
            xml.writeTextElement("algorithm", mItems[i].method);
            QString csvName = mItems[i].date;
            xml.writeTextElement("data", csvName);
            xml.writeEndElement();

            QString resultSubFolderPath = resultFolderPath + "/" + csvName;

            QDir resultDir(resultSubFolderPath);
            if (!resultDir.exists())
            {
                resultDir.mkdir(resultSubFolderPath);
            }

            resultSubFolderPath = resultSubFolderPath + "/" + csvName + ".csv";

            QFile csvFile(resultSubFolderPath);
            csvFile.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&csvFile);
            out << tr("index,image,logitude,latitude,label,confidence,x,y,w,h\n");
            for (int j = 0; j < mItems[i].label.size(); j++)
            {
                out << j << ","
                    << mItems[i].imgName[j] << ","
                    << mItems[i].longitude[j] << ","
                    << mItems[i].latitude[j] << ","
                    << mItems[i].label[j] << ","
                    << mItems[i].confidence[j] << ","
                    << mItems[i].roi[j].x() << ","
                    << mItems[i].roi[j].y() << ","
                    << mItems[i].roi[j].width() << ","
                    << mItems[i].roi[j].height() << ",\n";
            }
            csvFile.close();
        }

        xml.writeEndElement();
        xml.writeEndDocument();
        file.close();
    }
}


