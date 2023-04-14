#include "camera.h"

void Camera::threadLoop()
{
    while(mRun){
        getFrame();
    }
}

void Camera::getFrame()
{
    if(sceneCallback == nullptr) return;
    cv::Mat mat;
    cap >> mat;

    if (mat.empty())
    {
        std::cerr << "ERROR! blank frame grabbed\n";
        return;
    }
    sceneCallback->nextScene(mat);
}

bool Camera::start(int deviceID, int apiID)
{
    if (!mRun)
    {
        if (cap.open(deviceID))
        {
            cameraThread = std::thread(&Camera::threadLoop, this);
            mRun = true;
            return true;
        }
    }
    return false;
}

bool Camera::stop()
{
    if (mRun)
    {
        mRun=false;
        cap.release();
        cameraThread.join();
        return true;
    }
    return false;
}
