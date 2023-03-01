#include "resultlistdata.h"

ResultListData::ResultListData(QObject *parent)
    : QObject{parent}
{

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

void ResultListData::addResult()
{


}

void ResultListData::removeResult(int id)
{


}





