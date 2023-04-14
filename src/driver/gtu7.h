#ifndef GTU7_H
#define GTU7_H

#include <thread>
#include "serial.h"
#include "gnss.h"

class GTU7 : public SerialPort, public GNSS
{
public:
    GTU7() = default;

    virtual bool start(std::string& portName);
    virtual bool stop();
    virtual void registerCallback(Callback* sc) {
        mSerialCallback = sc;
    }

private:
    void getMessage();
    void threadLoop();
    std::thread mThread;
    bool mRun = false;
    Callback* mSerialCallback = nullptr;

#ifdef UNIT_TEST
friend class Test_GTU7;
#endif
};

#endif
