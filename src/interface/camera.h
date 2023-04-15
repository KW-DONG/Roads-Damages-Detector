#ifndef CAMERA_H
#define CAMERA_H
#include <opencv2/opencv.hpp>

class Camera
{
public:
    struct SceneCallback {
        virtual void nextScene(const cv::Mat &mat) = 0;
    };

    Camera() = default;
    virtual bool start(int deviceID = 0, int apiID = 0) = 0;
    virtual bool stop() = 0;
    virtual void registerSceneCallback(SceneCallback* sc) = 0;
};


#endif
