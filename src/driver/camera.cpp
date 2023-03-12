#include "camera.h"

void Camera::threadLoop(){
    while(run){
        getFrame();
    }
}

void Camera::getFrame(){
    if(sceneCallback == nullptr) return;
    cv::Mat mat;
    cap >> mat;

    if (mat.empty()) {
        std::cerr << "ERROR! blank frame grabbed\n";
        return;
    }
    sceneCallback->nextScene(mat);
}

void Camera::start(int deviceID, int apiID){ 
    if (cap.open(deviceID))
    {
        cameraThread = std::thread(&Camera::threadLoop, this);
        run = true;
    }
}

void Camera::stop(){  
    cameraThread.detach();
    run=false;
}
