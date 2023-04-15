#ifndef RTCAM_H
#define RTCAM_H
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <queue>
#include "interface/camera.h"

class RtCam : public Camera
{
public:
    virtual bool start(int deviceID = 0, int apiID = 0);
    virtual bool stop();
    virtual void registerSceneCallback(SceneCallback* sc) {
		sceneCallback = sc;
	}
    
private:
    void getFrame();

    //this loop runs with callbacks and always provide latest capture
    void readLoop();

    //this loop runs in full speed to capture images
    void capLoop();

    cv::VideoCapture cap;
    std::thread readThread;
    std::thread capThread;
    bool mRun = false;
	SceneCallback* sceneCallback = nullptr;
    std::queue<cv::Mat> imgBuf;

#ifdef UNIT_TEST
friend class Test_RtCam;
#endif
};

#endif
