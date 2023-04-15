#ifndef IMGRECOG_H
#define IMGRECOG_H
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class ImgRecog
{
public:
    struct Object
    {
        cv::Rect_<float> rect;
        int label;
        float prob;
    };

    ImgRecog() = default;

    virtual void setPath(const std::vector<std::string>& paths) = 0;
    virtual int detect(const cv::Mat& bgr, std::vector<Object>& object) = 0;
    virtual void drawObjects(const cv::Mat& src, cv::Mat& dst, const std::vector<Object>& objects, std::vector<std::string>& classNames) = 0;
};

#endif
