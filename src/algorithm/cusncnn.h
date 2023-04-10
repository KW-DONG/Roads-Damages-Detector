#include "layer.h"
#include "net.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

namespace ncnn
{

struct Object
{
    cv::Rect_<float> rect;
    int label;
    float prob;
};

class CusNCNN
{
public:
    void loadParam(const std::string& str);
    void loadModel(const std::string& str);
    int detect(const cv::Mat& bgr, std::vector<Object>& object);
    void drawObjects(const cv::Mat& src, cv::Mat& dst, const std::vector<Object>& objects, std::vector<std::string>& classNames);
private:
    float intersectionArea(const Object& a, const Object& b);
    void qsortDescentInplace(std::vector<Object>& faceobjects, int left, int right);
    void qsortDescentInplace(std::vector<Object>& faceobjects);
    void nmsSortedBboxes(const std::vector<Object>& faceobjects, std::vector<int>& picked, float nms_threshold, bool agnostic = false);
    float sigmoid(float x);
    void generateProposals(const ncnn::Mat& anchors, int stride, const ncnn::Mat& in_pad, const ncnn::Mat& feat_blob, float prob_threshold, std::vector<Object>& objects);

    std::string mParamPath;
    std::string mModelPath;
};
}
