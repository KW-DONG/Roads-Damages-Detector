#ifndef GTEST_TASKLISTDATA_H
#define GTEST_TASKLISTDATA_H
#include <gtest/gtest.h>
#include "tasklistdata.h"

class Test_TaskListData : public QObject
{
public:
    bool checkIsAdd()
    {
        TaskListData* pData = new TaskListData(this);
        pData->addTask();
        return pData->mItems.size() == 1;
    }    
    bool checkIsRemove()
    {
        TaskListData* pData = new TaskListData(this);
        pData->addTask();
        pData->removeTask(0);
        return pData->mItems.size() == 0;
    }
    bool checkIsEdit()
    {
        TaskListData* pData = new TaskListData(this);
        pData->addTask();
        pData->setIndex(0);       
        pData->setTitle("title");
        return pData->mItems[0].title == "title";
    }
    bool checkIsFind()
    {
        TaskListData* pData = new TaskListData(this);
        TaskListData_t item;
        item.title = "title";
        pData->mItems.push_back(item);
        pData->setIndex(0);
        return (pData->title() == "title");
    }
    bool chackIsSave()
    {
        TaskListData* pData = new TaskListData(this);
        TaskListData_t item;
        item.title = "title";
        pData->mItems.push_back(item);
        pData->saveConfig();

        pData->mItems.clear();
        pData->readConfig();
        return (pData->mItems[0].title == "title")
    }
}

TEST(tasklistdata_test, checkIsAdd)
{
    Test_TaskListData test;
    EXPECT_EQ(test.checkIsAdd(),true);

}







#endif