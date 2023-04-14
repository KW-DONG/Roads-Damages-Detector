#ifndef _GTU7_H
#define _GTU7_H

#include <thread>
#include "serial.h"

class GTU7 : public SerialPort
{
public:
    struct SerialCallback {
        virtual void next(double lat, double lon) = 0;
    };

    GTU7() = default;

    void start(std::string& portName);
    void stop();
    void registerSerialCallback(SerialCallback* sc) {
        mSerialCallback = sc;
    }

private:
    void getMessage();
    void threadLoop();
    std::thread mThread;
    bool mRun = false;
    SerialCallback* mSerialCallback = nullptr;

#ifdef UNIT_TEST
friend class Test_GTU7;
#endif
};

#endif
