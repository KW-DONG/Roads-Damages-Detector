#ifndef GTEST_RESULTLISTDATA_H
#define GTEST_RESULTLISTDATA_H
#include <gtest/gtest.h>
#include "resultlistdata.h"


class Test_ResultListData : public QObject
{
public:
        //增删改查读写
        //增：查长度
        //删：删掉的ID，遍历后还有没有这个值
        //task改&查：setindex,加一项，再查，看看还在不在
    bool checkIsAdd()
    {
        ResultListData* pData = new ResultListData(this);
        ResultListData_t item;
        item.name = "name";

        pData->addResult(item);
        return pData->mItems.size() == 1;
        return (pData->name() == "name");
    }    
    bool checkIsRemove()
    {
        ResultListData* pData = new ResultListData(this);
        ResultListData_t item;
        item.name = "name";
        pData->removeResult(0);
        return pData->mItems.size() == 0;
    }
    
    bool checkIsFind()
    {
        ResultListData* pData = new ResultListData(this);
        ResultListData_t item;

        item.name = "name";
        pData->mItems.push_back(item);
        pData->setIndex(0);
        return (pData->mItem[0].name() == "name");
    }

    bool chackIsSave()
    {
        ResultListData* pData = new ResultListData(this);
        ResultListData_t item;
        item.name = "name";
        pData->mItems.push_back(item);
        pData->save();

        pData->mItems.clear();
        pData->readSave();
        return (pData->mItems[0].name == "name");
    }


    ResultListData mData;
}


TEST(resultlistdata_test, checkIsAdd)
{
    Test_ResultListData test;
    EXPECT_EQ(test.checkIsAdd(),true);

}

TEST(resultlistdata_test, checkIsRemove)
{
    Test_ResultListData test;
    EXPECT_EQ(test.checkIsRemove(),true);

}


TEST(resultlistdata_test, checkIsFind)
{
    Result_ResultListData test;
    EXPECT_EQ(test.checkIsFind(),true);

}

TEST(resultlistdata_test, checkIsSave)
{
    Test_ResultkListData test;
    EXPECT_EQ(test.checkIsSave(),true);

}



#endif