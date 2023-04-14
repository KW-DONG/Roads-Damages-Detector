#ifndef GTEST_CUSNCNN_H
#define GTEST_CUSNCNN_H
#include <gtest/gtest.h>
#include "cusncnn.h"

class Test_CusNCNN
{
public:
    bool checkNcnn()
    {
        std::vector<ncnn::Object> objects;
        cv::Mat src = cv::imread("./bin/001.jpg");
        ncnn::CusNCNN mNcnn;
        mNcnn.loadModel("./bin/best.bin");
        mNcnn.loadParam("./bin/best.param");
        mNcnn.detect(src, objects );
        if(objects.size()==1)
        {
            if(objects[0].label == 1)
                return true;
        }
        return false;

    }

};

TEST(ncnn_test, checkNcnn)
{
    Test_CusNCNN test;
    EXPECT_EQ(test.checkNcnn(), true);
}

#endif



