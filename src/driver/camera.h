#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <thread>

class Camera {
public:
	struct SceneCallback {
		virtual void nextScene(const cv::Mat &mat) = 0;
        //virtual void beforeStop() = 0;
	};

	Camera() = default;

	void start(int deviceID = 0, int apiID = 0);
	void stop();
	void registerSceneCallback(SceneCallback* sc) {
		sceneCallback = sc;
	}
    
private:
    void getFrame();
	void threadLoop();
    cv::VideoCapture cap;
	std::thread cameraThread;
    bool run = false;
	SceneCallback* sceneCallback = nullptr;

#ifdef UNIT_TEST
friend class Test_Camera;
#endif
};
