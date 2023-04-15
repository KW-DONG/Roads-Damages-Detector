#ifndef GNSS_H
#define GNSS_H
#include <string>

class GNSS
{
public:
    GNSS() = default;
    struct Callback {
        virtual void next(double lat, double lon) = 0;
    };

    virtual bool start(std::string& param) = 0;
    virtual bool stop() = 0;
    virtual void registerCallback(Callback* cb) = 0;
};

#endif
