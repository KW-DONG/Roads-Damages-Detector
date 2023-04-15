#ifndef GTEST_CAMERA_H
#define GTEST_CAMERA_H
#include <gtest/gtest.h>
#include "rtcam.h"

class Test_RtCam
{
public:
    bool checkIsStart(int id)
    {
        mCam.start(id);
        bool result = mCam.mRun == true;
        mCam.stop();
        return result;
    }
    bool checkIsStop(int id)
    {
        mCam.start(id);
        mCam.stop();
        return mCam.mRun == false;
    }
    RtCam mCam;
};

TEST(camera_test, checkIsStart)
{
    Test_RtCam test;
    EXPECT_EQ(test.checkIsStart(0), true);
}

TEST(camera_test, checkIsStop)
{
    Test_RtCam test;
    EXPECT_EQ(test.checkIsStop(0), true);
}

#endif
