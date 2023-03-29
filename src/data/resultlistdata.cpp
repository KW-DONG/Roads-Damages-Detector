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

bool ResultListData::loadResult(const QString& path)
{
    return true;
}

bool ResultListData::saveResult(const QString& path)
{
    return true;
}

int ResultListData::size()
{
    return mItems.size();
}

void ResultListData::addResult(ResultListData_t value)
{
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
}

int ResultListData::index()
{
    return currentResult;
}

QImage ResultListData::img()
{
    //read image
    QString _imgPath = resultFolderPath + "/" +
            mItems[currentResult].date + "/" +
            mItems[currentResult].imgName[currentImg];
    QImage _img(_imgPath);

    //draw rectangle
    QPainter painter(&_img);
    painter.setPen(QPen(Qt::blue,4,Qt::SolidLine));
    QRect rect = mItems[currentResult].roi[currentImg];

    painter.drawRect(rect);
    QPoint point(rect.x(), rect.y() - 20);
    painter.drawText(point, QString::number(mItems[currentResult].confidence[currentImg]));
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
            QString::number(mItems[currentResult].imgName.size());
    return str;
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
                        QFile csvFile(xml.readElementText());
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
                                _result.imgName.append(list[1]);
                                _result.longitude.append(list[2].toDouble());
                                _result.latitude.append(list[3].toDouble());
                                _result.label.append(list[4].toInt());
                                _result.confidence.append(list[5].toDouble());
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
            out << tr("index,image,logitude,latitude,label,confidence,\n");
            for (int j = 0; j < mItems[i].label.size(); j++)
            {
                out << j << ","
                    << mItems[i].imgName[j] << ","
                    << mItems[i].longitude[j] << ","
                    << mItems[i].latitude[j] << ","
                    << mItems[i].label[j] << ","
                    << mItems[i].confidence[j] << ",\n";
            }
            csvFile.close();
        }

        xml.writeEndElement();
        xml.writeEndDocument();
        file.close();
    }
}


