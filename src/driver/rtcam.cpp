#include "rtcam.h"

void RtCam::readLoop()
{
    while(mRun)
    {
        getFrame();
    }
}

void RtCam::capLoop()
{
    while(mRun)
    {
        cv::Mat mat;
        cap.read(mat);
        if (!mat.empty())
        {
            if (mtx.try_lock())
            {
                if (imgBuf.size() > 0)
                    imgBuf.pop();
                imgBuf.push(mat);
                mtx.unlock();
            }
        }
    }
}

void RtCam::getFrame()
{
    if(sceneCallback == nullptr) return;
    if (imgBuf.size() > 0)
    {
        mtx.lock();
        cv::Mat mat = imgBuf.front();
        sceneCallback->nextScene(mat);
        imgBuf.pop();
        mtx.unlock();
    }
}

bool RtCam::start(int deviceID, int apiID)
{
    if (!mRun)
    {
        if (cap.open(deviceID))
        {
            capThread = std::thread(&RtCam::capLoop, this);
            readThread = std::thread(&RtCam::readLoop, this);
            mRun = true;
            return true;
        }
    }
    return false;
}

bool RtCam::stop()
{
    if (mRun)
    {
        mRun=false;
        cap.release();
        capThread.join();
        readThread.join();
        return true;
    }
    return false;
}
