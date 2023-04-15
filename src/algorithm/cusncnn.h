#ifndef CUSNCNN_H
#define CUSNCNN_H

#include "layer.h"
#include "net.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "imgrecog.h"


class CusNCNN : public ImgRecog
{
public:
    virtual void setPath(const std::vector<std::string>& paths) override;
    virtual int detect(const cv::Mat& bgr, std::vector<Object>& object) override;
    virtual void drawObjects(const cv::Mat& src, cv::Mat& dst, const std::vector<Object>& objects, std::vector<std::string>& classNames) override;
private:
    float intersectionArea(const Object& a, const Object& b);
    void qsortDescentInplace(std::vector<Object>& faceobjects, int left, int right);
    void qsortDescentInplace(std::vector<Object>& faceobjects);
    void nmsSortedBboxes(const std::vector<Object>& faceobjects, std::vector<int>& picked, float nms_threshold, bool agnostic = false);
    float sigmoid(float x);
    void generateProposals(const ncnn::Mat& anchors, int stride, const ncnn::Mat& in_pad, const ncnn::Mat& feat_blob, float prob_threshold, std::vector<Object>& objects);

    std::string mParamPath;
    std::string mModelPath;
#ifdef UNIT_TEST
    friend class Test_CusNCNN;
#endif
};
#endif
